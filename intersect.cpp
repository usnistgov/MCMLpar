#include "intersect.h"

/* Written by Richelle Streater, May 2017. */

/* Intersect solves for the polar angle on the detection sphere, accounting
for finite radius. If intersect did not account for finite radius,
it would only need to return arccos(par.rVec.at(2)). Intersect is called by
detect. */

/******************************************************************************/

double intersect( double R, Particle &par ) {

    /* Set the z component to zero because we assume that the center of the detection sphere
    is at this z-position, and we only are accounting for x and y position. */
    par.rVec.at(2) = 0;

	/* Find alpha, the distance that the particle will travel until it intersects with the
	sphere. The final position when the particle intersects is rVec = alpha*dir + rVec0. */
	double alpha, x, rSquared = 0, theta;
	x = dotProd( par.rVec, par.dir );

	/* Find the square of the magnitude of rVec */
	for( unsigned int i=0; i<par.rVec.size(); i++ ) {
		rSquared += par.rVec.at(i) * par.rVec.at(i);
	}
	alpha = -x + sqrt( x*x + R*R - rSquared );

    /* Update position so that particle is on the detector sphere */
    for ( unsigned int i = 0; i < par.rVec.size(); i++ ) {
        par.rVec.at(i) += alpha * par.dir.at(i);
    }

	/* Obtain point of intersection: atan2(rho, z), since x^2+y^2 = rho */
	theta = atan2( sqrt( par.rVec.at(0)*par.rVec.at(0)
           + par.rVec.at(1)*par.rVec.at(1) ), par.rVec.at(2) );

	return theta;
}
