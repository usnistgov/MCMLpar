#include "specularR.h"

/* Written by Richelle Streater, June 2017. */

/* SpecularR determines initial specular reflection value based on index of refraction. */

/********************************************************************/

double specularR( Layer& lay ) {
    double n = lay.getN();
    return ( ( 1 - n ) * ( 1 - n ) ) / ( ( 1 + n ) * ( 1 + n ) );
}
