#include "scatter.h"

/* Written by Richelle Streater, June 2017. */

/* Scatter is called by main when a particle has completed a step. Scatter
samples a uniform random number to find phi, the azimuthal angle off of the
particle's direction vector. Scatter calls HGDist to find cos(theta) or xL,
where theta is the polar angle off of the particles direction vector. Scatter
calls the roulette function to destroy the particle if it has a low enough
scalar weight (high probability of attenuation). If the particle has not been
destroyed, scatter calls scattFunction to update the particle's direction with
phi and theta. Scatter will either output 0 if roulette kills the particle or 1
to call propagate in main. */

/* Variables:
    xL- the cosine of the particle's polar angle change, theta.
    phi- the particle's azimuthal angle change, phi.
    WTH- Threshold weight for calling roulette function. */

/******************************************************************************/

int scatter( Particle &par ) {

    /* Initialize variables */
    double xL, phi;
	const double TAU = 6.28318530717958647692;
	const double WTH = 0.0001;

    /* Update weight, since this counts as an event */
    par.weight *= par.lay.getMusDivMut();

    /* Call roulette if the weight is below the threshold. If roulette returns TRUE
    (particle to be destroyed), leave scatter and return 0 to let particle "escape"
    with no weight (this is equivalent to the particle being destroyed). */
	if ( ( par.weight < WTH ) ) {
        if ( roulette( par, par.sprngptr ) ) {
            return 0;
        }
	}

	/* Sample cos(theta) from HG distribution */
	xL = HGDist( par.lay.getG(), par.sprngptr );

	/* Arbitrarily select phi from uniform distribution (we have phi independence) */
    #ifdef SPRNGFIVE
    phi = par.sprngptr->sprng()*TAU;

    #else
    phi = sprng( par.sprngptr )*TAU;
    #endif

    /* Change particle direction */
    scattFunction( par, xL, phi );
    return 2;
}
