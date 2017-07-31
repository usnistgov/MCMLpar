#include "HGDist.h"

/* Written by Richelle Streater, May 2017, edited by Anne-Michelle Lieberson, July 2017. */

/* HGDist outputs random variable from Henyey Greenstein distribution. Input "g"
is anisotropy. Output "mu" is the cosine of the polar scatter angle. */

/********************************************************************/

#ifdef SPRNGFIVE
double HGDist( double g, Sprng* sprngptr ) {
    double x = sprngptr->sprng();

#else
double HGDist(double g, int* sprngptr) {
    double x = sprng( sprngptr );
#endif

    double mu;
	if ( fabs(g) < .0000001 ) {
        mu = 2*x - 1;
	}
	else {
        mu = ( 1+g*g-pow( ( 1-g*g ) / ( 2*g*x+1-g ), 2 ) ) / ( 2*g );
	}
	return mu;
}
