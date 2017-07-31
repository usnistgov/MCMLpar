#include "newSegSize.h"

/* Written by Richelle Streater, June 2017. */

/* newSegSize outputs a exponentially distributed random variable */

/********************************************************************/

#ifdef SPRNGFIVE
double newSegSize( Sprng * sprngptr ) {
    double x = sprngptr->sprng();

#else
double newSegSize( int* sprngptr ) {
    double x = sprng( sprngptr );
#endif

	return ( -log( 1-x ) );
}
