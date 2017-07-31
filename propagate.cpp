#include "propagate.h"

/* Written by Richelle Streater, May 2017. */

/* Propagate moves a particle by one step. Propagate first calls newSegSize.h
to determine a distance d for the step size. It calculates the z-component of
position that this distance would send the particle to. If this z is out of
bounds, sends the particle just up to the boundary and returns 3 to call
boundary in main. Otherwise, propagates returns 1 to call scatter in main. */

/* Variables:
    d- the randomly generated distance of travel.
    kz- the z-component of the particle's direction vector (to reduce computation).
    z- the z-component of position that d will propagate the particle to.
    minZ, maxZ- the boundaries of the current layer (to reduce computation). */

int propagate( Particle &par ) {

/************************  Initialize Variables  ******************************/

	double d, kz, z, minZ, maxZ;
	int state;

	/* Set d by exponential distribution */
	d = newSegSize( par.sprngptr ) / ( par.lay.getMut() );
	kz = par.dir.at(2);
	z = par.rVec.at(2) + kz*d;

	/* Define max and min Z */
    minZ = par.lay.getZMin();
    maxZ = par.lay.getZMax();

/*****************  End of initializing Variables  ****************************/

/*************  Check if particle will be out of bounds  **********************/

    /* If z is out of layer bounds */
    if ( ( z > maxZ ) || ( z < minZ ) ) {

        /* Forward case */
        if( ( kz > 0 ) && ( z > maxZ ) ) {

            /* Update step size */
            d = ( maxZ - par.rVec.at(2) ) / kz;
        }

        /* Backwards case */
        else if( ( kz < 0 ) && ( z < minZ ) ) {

        /* Update step size */
            d = ( minZ - par.rVec.at(2) ) / kz;

        }

        /* Check for an error in position- particle should not be
        below minZ going up or above maxZ going down. */
        else {
            cerr << "error: particle out of bounds (did not escape). From"
            << " boundary program" << endl;
            return 0; /* Escape to prevent further problems */
        }

        /* Call boundary in main. */
        state = 3;
	}

/***********  End of checking if particle will be out of bounds  **************/

    else {

        /* Call scatter in main. */
        state = 1;
    }
    par.updatePosition(d);
    return state;
}
