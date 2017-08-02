#include "detect.h"

/* Written by Richelle Streater, June 2017. */

/* Detect finds the particle's position when it intercepts with
the detector and assigns the particle's weight to the ARS vector.
Detect calls intersect to determine the polar angle at which the particle
hits the detector sphere and converts this to a position in the ARS
vector. It adds the particle's weight to the ARS vector at this position. */

/* Variables:
    theta- the angle on the detector sphere where the particle intercepts it
    j- the index in ARS corresponding to theta */

/******************************************************************************/

int detect( Particle &par, double radius, unsigned int angleDiv, vector<double>& ars ) {
	const double PI = 3.141;
	unsigned int j;
    double theta;

    theta = intersect( radius, par );

    /* Scale and round down the angle to put it into the ARS vector at the correct position */
    j = int( angleDiv * theta / PI );
    if ( j >= angleDiv ) {
        j = angleDiv - 1;
        cerr << "Warning: Particle detected parallel to layer surface (from detect.cpp)" << endl;
    }

    ars.at(j) += par.weight;

    /* Done with this particle */
    return 0;
}
