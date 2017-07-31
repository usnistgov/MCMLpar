#include "medInterface.h"

/* Written by Richelle Streater, May 2017. */

/* MedInterface is called by the boundary. MedInterface calculates
the Fresnel Coefficients for the boundary. It generates a uniformly distributed
random number between zero and one, and compares the number to the Fresnel
coefficients to determine whether to reflect or transmit. The output of medInterface
is TRUE if the particle escaped the layer and FALSE if the particle did not. MedInterface
assumes a non-magnetic medium. */

/* Variables:
    layPotential- layer that the particle would transmit to if it escaped its layer
    kz1, kz2: z-component of direction vector originally and if transmitted
    n1, n2: indices of refraction of current layer and layB
    x: random number between zero and one (uniform)
    Rp: reflectance for P-polarized light
    Rs: reflectance for S-polarized light
    R: reflectance for unpolarized light */

/********************************************************************/

#ifdef SPRNGFIVE
bool medInterface( Particle &par, Layer &layPotential, Sprng* sprngptr ) {

#else
bool medInterface( Particle &par, Layer &layPotential, int* sprngptr ) {
#endif

    /* Set up variables to reduce # of calculations */
	double kz1, n1, n2, storeCalc, kz2, x, Rp, Rs, R;
	kz1 = par.dir.at(2);
	n1 = par.lay.getN();
	n2 = layPotential.getN();

/*******************  Find Fresnel Coefficients *********************/

	/* Non-TIR case: set up Fresnel Coefficients. Use Snell's law to find kz2. */
	storeCalc = n1*n1 * ( 1-kz1*kz1 ) / ( n2*n2 );
	if ( storeCalc <= 1 ) {

        /* If-else statement makes sure that kz1 & kz2 have the same sign */
        if ( kz1 > 0 ) {
            kz2 = sqrt(1-storeCalc);
        }
        else {
            kz2 = -sqrt(1-storeCalc);
        }

        /* Fresnel's equations */
        Rs = pow( ( ( n1*kz1 - n2*kz2 ) / ( n1*kz1 + n2*kz2 ) ), 2 );
        Rp = pow( ( ( n2*kz1 - n1*kz2 ) / ( n2*kz1 + n1*kz2 ) ), 2 );
        R = ( 1.0/2.0 ) * ( Rp + Rs );
	}

	/* TIR case- particle must reflect */
	else {
        kz2 = -kz1;
        R = 1;
	}

/*************  End of finding Fresnel Coefficients  ****************/

/****************  Determine whether to transmit  *******************/

    /* x is a number between 0 and 1 to determine transmission vs reflection */
    #ifdef SPRNGFIVE
    x = sprngptr->sprng();

    #else
    x = sprng( par.sprngptr );
    #endif

	if ( x <= R ) {
        /* particle is reflected */
		par.dir.at(2) = -kz1;
	}

	else {
        /* particle is transmitted */

		/* n1/n2 scaling factor can be derived from wave numbers or from Snell's law */
		par.dir.at(0) *= n1/n2;
		par.dir.at(1) *= n1/n2;
		par.dir.at(2) = kz2;

		/* Particle is now in the new layer */
		par.lay = layPotential;
		return true;
	}
	return false;
}

/*************  End of determining whether to transmit  *************/
