#include "detect.h"

/* Written by Richelle Streater, June 2017. */

/* Detect finds the particle's position when it intercepts with
the detector and assigns the particle's weight to the ARS vector.
Detect calls intersect to determine the polar angle at which the particle
hits the detector sphere and converts this to a position in the ARS
vector. It adds the particle's weight to the ARS vector at this position. */

/* Variables:
    theta- the angle on the detector sphere where the particle intercepts it
    ind- the index in ARS corresponding to theta */

/******************************************************************************/

int detect( Particle &par, double radius, unsigned int angleDiv, vector<double> &ars ) {
	const double PI = 3.14159265358979323846;
    double theta;
    unsigned int ind;

    theta = intersect( radius, par );

    /* Scale and round down the angle to put it into the ARS vector at the correct position */
    ind = int( angleDiv * theta / PI );

    /* Avoid out of range problems */
    while ( ind >= angleDiv ) {
        ind -= 1;
    }

    /* Add the weight to the ARS vector at the position ind */
    ars.at(ind) += par.weight;

    /* Done with this particle */
    return 0;
}
