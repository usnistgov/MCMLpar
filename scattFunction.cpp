#include "scattFunction.h"

/* Written by Richelle Streater, May 2017. */

/* ScattFunction is called by scatter to change the particle's direction.
ScattFunction uses the two input angles to rotate the particle's direction
vector. To accomplish this, it essentially creates an orthogonal triad based on the
particles direction and multiplies the triad by the Euler rotation matrix.
This is all accomplished through the transformation functions under the switch
statement. */

/* Variables
    indexMin- index of minimum component of original direction vector
    xL- cosine of polar angle, theta
    phi- azimuthal angle
    v0, v1, v2- original direction vector components (to reduce computation)
    st, sp, cp- cosines and sines of angles (to reduce computation) */

/******************************************************************************/

void scattFunction( Particle &par, double xL, double phi ) {
    unsigned int indexMin = 0;

    /* There is an extra degree of freedom here due to phi independence. This gives us
    a choice between the three functions in the switch statement below. By finding the
    minimum direction component, we can choose the function that will give us the least
    error. We get less error this way because we avoid subtracting a value close to 1
    from 1 in the switch statement functions. */
	for( unsigned int i=1; i<par.dir.size(); i++ ) {
		if( fabs( par.dir.at(i) ) < fabs( par.dir.at(indexMin) ) ) {
			indexMin = i;
		}
	}

    /* Initialize variables */
    double x, y, z, st, sp, cp;
    x = par.dir.at(0);
    y = par.dir.at(1);
    z = par.dir.at(2);

    /* create sin(theta), sin(phi), cos(phi). Sin(theta) must be (+),
    so there is no need to worry about the (-) case.  */
    st = sqrt( fabs( 1.0 - xL*xL ) );
    cp = cos( phi );
    sp = sin( phi );

    /* All three functions are equivalent, except for possible round-off error.
    The functions are equivalent to creating an orthogonal triad and multiplying
    it by the Euler rotation matrix. */
    switch( indexMin ) {
    case 0:
        par.dir.at(0) = x*xL - sqrt( y*y + z*z ) * sp * st;
        par.dir.at(1) = y*xL + ( z*cp*st + x*y*sp*st ) / sqrt( y*y + z*z );
        par.dir.at(2) = z*xL + ( -y*cp*st + x*z*sp*st ) / sqrt( y*y + z*z );
        break;

    case 1:
        par.dir.at(0) = x*xL + ( -z*cp*st + x*y*sp*st ) / sqrt( x*x + z*z );
        par.dir.at(1) = y*xL - sqrt( x*x + z*z ) * sp * st;
        par.dir.at(2) = z*xL + ( x*cp*st + y*z*sp*st ) / sqrt( x*x + z*z );
        break;

    case 2:
        par.dir.at(0) = x*xL + ( y*cp*st + x*z*sp*st ) / sqrt( x*x + y*y );
        par.dir.at(1) = y*xL + ( -x*cp*st + y*z*sp*st ) / sqrt( x*x + y*y );
        par.dir.at(2) = z*xL - sqrt( x*x + y*y ) * sp * st;
        break;

    default:
        break;
    }
}
