#include "particle.h"

/* Particle is an object that represents a photon scattering in an optical medium. */

/* Members:
    rVec: (x,y,z) position coordinates
    dir: (kx,ky,kz) direction vector
    sprngptr: a pointer that eliminates race conditions in the parallel for loop
    layer: the layer that the particle is currently in
*/

/******************************************************************************/

#ifdef SPRNGFIVE
Particle::Particle ( double T, Sprng* sprngptrin ) {

#else
Particle::Particle ( double T, int* sprngptrin ) {
#endif

    /* Make a 3X1 position vector, filled with zeros */
    vector<double> positionVector( 3, 0 );

    /* Make 3X1 direction vector, point it down. */
    vector<double> dirVector( 3, 0 );
    dirVector.at( 2 ) = 1;

    rVec = positionVector;
    dir = dirVector;
    lay = Layer();
    sprngptr = sprngptrin;
    weight = T;
}

Particle::Particle () {
    /* Make a 3X1 position vector, filled with zeros */
    vector<double> positionVector( 3, 0 );

    /* Make 3X1 direction vector, point it down. */
    vector<double> dirVector( 3, 0 );
    dirVector.at( 2 ) = 1;

    rVec = positionVector;
    dir = dirVector;
    lay = Layer();
    weight = 1;
}

/* Reset function: creates new particle for beginning of main loop. */
void Particle::reset( double T ) {
    rVec = {0,0,0};
    dir = {0,0,1};
    weight = T;
}

/* Update position function- Uses an input distance and particle direction. */
void Particle::updatePosition( double d ) {
    for ( unsigned int j = 0; j < rVec.size(); j++ ) {
        rVec.at(j) += d * dir.at(j);
    }
}
