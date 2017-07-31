#include "initSPRNG.h"

/* Written by Richelle Streater, June 2017. */

/* initSPRNG initializes and seeds the parallel random number generator.
initSPRNG returns false if the streams have not been spawned and true if
they have. */

/********************************************************************/

#ifdef SPRNGFIVE
bool initSPRNG( unsigned int numProc, Sprng*** sprngptrarr, int time_0 ) {
    /* Seed the RNG, check to see if processors spawned */
unsigned int numSpawned;
#else
bool initSPRNG( unsigned int numProc, int ***sprngptrarr, int time_0 ) {
    int *stream;
    stream = init_sprng( SPRNG_LCG64, 0, 1, time_0, SPRNG_DEFAULT );

    unsigned int numSpawned = spawn_sprng( stream, numProc, sprngptrarr );

    stream = NULL;
#endif
    if ( numSpawned != numProc ) {
        cerr <<  "Error: " << numSpawned << " actual out of " << numProc;
        cerr << " wanted streams spawned! (from main.cpp)" << endl;
        return false;
    }
    return true;
}
