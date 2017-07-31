#include "likelihood.h"

/* Written by Richelle Streater, June 2017. */

/* Likelihood calculates the negative log-likelihood of the forward MC simulation
ARS curve matching the experimental ARS curve. Formula derived by Adam Pintar.
The constants were not included, since the subFromMax function would eliminate them
anyway. Likelihood is called by scoreParam.

    log-likelihood = -N/2 log(1/N (sum to N) (obs - pred)^2 + log(2pi) + 1 */

/******************************************************************************/

double likelihood( const vector<double>& vec1, const vector<double>& vec2 ){
    double sumStore = 0;
    unsigned int N = vec1.size();

    if ( N != vec2.size() ) {
        cerr << "Error: vectors not the same size (from likelihood.cpp)." << endl;
        return numeric_limits<double>::quiet_NaN();
    }

    for ( unsigned int i = 0; i < N; i++ ) {
        sumStore += pow( vec1.at(i) - vec2.at(i), 2 );
    }

    return N/2.0 * log( sumStore / double( N ) );
}
