#include "roulette.h"

/* Rewritten by Richelle Streater (from MCML) June 2017. */

/* Roulette properly disposes of particles that have a small scalar
weight (a high probability of attenuation). Roulette gives these
particles a chance to attenuate, and accounts for all attenuated particles
by increasing the weight of particles that have not attenuated. This
function greatly reduces computation time in cases where mu_a and medium
thickness are both high. Roulette returns TRUE when the particle attenuates
and FALSE when it does not. */

/******************************************************************************/

#ifdef SPRNGFIVE
bool roulette( Particle& par, Sprng* sprngptr ) {

    /* Define m, where particle has m chance of surviving */
    const double m = 0.1;
    double x;

    /* Make random number between 0 and 1 */
    x = sprngptr->sprng();

#else
bool roulette( Particle& par, int* sprngptr ) {

    /* Define m, where particle has m chance of surviving */
    const double m = 0.1;
    double x;

    /* Make random number between 0 and 1 */
    x = sprng( par.sprngptr );
#endif

    /* Decide if particle survives */
    if ( x <= m ) {
        par.weight /= m;
        return false;
    }

    else {
        par.weight = 0;
        return true;
    }
}
