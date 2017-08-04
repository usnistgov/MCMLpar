#include "mainHeaders.h"

/******************************  MCMLpar  *************************************/

/*
Program written by Richelle Streater, Anne-Michelle Lieberson, and Zachary Levine
July 2017
National Institute of Standards and Technology
Physical Measurement Lab
Sensor Science Division
Remote Sensing Group

Main first initializes all variables, seeds the RNG, and reads the input files. It
declares functions within the parallel for loop to eliminate race conditions. Next, it runs
the forward MC simulation on all particles, cycling between four states: scatter, propagate,
boundary, and detect, until the particle escapes or vanishes in the material. */

/* Variables:
    numParticles: Number of particles to send through medium
    numDiv: Number of points or elements in ARS vector
    numProc: Number of processors to use (parallelization)
    seedIn, seed:  seed for random number generator.  If seedIn==0, the time is used.
    radius: Radius of detector
    layerVec: Vector holding parameters for all layers in the material
    T: Specular transmission, particles that initially make it into the medium
    ars, arsProc: Store the angle resolved scattering results
 */

int main() {

/**********************  Inputs and Initialization  ***************************/
    /* Read in experimental data, set parameters from file. */
    int time0 = time( NULL ), seedIn, seed;
    unsigned int numParticles, numProc, numDiv, timeCount;
    double radius;
    vector<Layer> layerVec;
    Layer layAir;

    /* Quit the program if there is an input error. */
    if ( !setParameters( layerVec, numParticles, numDiv, numProc, seedIn, radius ) ) {
        return 1;
    }

    numDiv *= 2;
    if ( seedIn == 0 ) {
       seed = time0;
    }
    else {
       seed = seedIn;
    }

    /* Seed the random number generator, depending on which version of
    SPRNG is present. */
#ifdef SPRNGFIVE
    int gtype = 2;
    /* Seed the RNG */
    Sprng *stream, **sprngptrarr;
    stream = SelectType(gtype);
    stream->init_sprng(0, 1, seed, SPRNG_DEFAULT);

    unsigned int nspawned = stream->spawn_sprng(numProc,&sprngptrarr);

    if ( nspawned != numProc ) {
        cout <<  "Error: " << nspawned << " actual out of " << numProc << " wanted streams spawned! " << endl;
        return 1;
    }

#else
    int **sprngptrarr;
    if ( !initSPRNG( numProc, &sprngptrarr, seed ) ) {
        return 1;
    }
#endif

    /* Initialize variables */

    double T = 1 - specularR( layerVec.at(0) );

    /* Initialize vectors that need earlier information */
    omp_set_num_threads( numProc );
    vector<double> ars( numDiv, 0 );
    vector<vector<double> > arsProc( numProc, vector<double>( numDiv, 0 ) ) ;

    Layer *layPtr;
    layPtr = &layerVec.at(0);

/*********************  End of inputs and initialization  *********************/

/*********************  Forward Monte Carlo Simulation  ***********************/

    #pragma omp parallel for
    for ( unsigned int n = 0; n < numProc; n++ ) {

        /* Safe initializations within the parallel loop to eliminate race conditions */
        Particle par( T, sprngptrarr[n] );
        int state;
        int propagate( Particle& );
        int detect( Particle&, double, unsigned int, vector<double>& );
        int scatter( Particle& );
        int boundary( Particle&, Layer&, vector<Layer>& );

        /* Send particle through the material */
        for ( unsigned int i = 0; i < numParticles/numProc; i++ ) {

            /* Reset particle weight/position and put the particle in the first layer */
            par.reset( T );
            par.lay = *layPtr;
            state = 2;

            /* Loop through states 1-4 until state is zero (AKA particle has escaped) */
            while ( state ) {
                switch( state ) {
                case 1:
                    state = scatter( par );
                    break;

                case 2:
                    state = propagate( par );
                    break;

                case 3:
                    state = boundary( par, layAir, layerVec );
                    break;

                case 4:
                    state = detect( par, radius, numDiv, arsProc.at(n) );
                    break;
            }
            }
        }
    }

    /* Add together parallel solutions to attain total ARS */
    for ( unsigned int p = 0; p < numProc; p++ ) {
        addVec( ars, arsProc.at(p) );
    }

    /* Match ars format to experimental data, which shifts by half of an angle division. */
    fixARS( ars, numParticles );

/******************  End of forward Monte Carlo simulation  *******************/

    timeCount = time(0) - time0;
    dataOut( ars, timeCount );

    sprngptrarr = NULL;
    layPtr = NULL;

    return 0;
}
