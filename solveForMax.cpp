#include "solveForMax.h"

/* Written by Richelle Streater, June 2017. */

/* Given six paraboloid coefficients, solveForMax finds the maximum
point by setting the partial derivative to zero.

Coeffs = (a00, a10, a01, a11, a20/2, a02/2)
Paraboloid = a00 + a10x + a01y + a11xy + a20x^2/2 + a02y^2/2 */

/******************************************************************************/

void solveForMax( const vector<double>& coeffs, double& x, double& y ) {

    /* Reduce computation time and avoid values over zero */
    double storeDenom = coeffs.at(3)*coeffs.at(3) - coeffs.at(5)*coeffs.at(4);

    if ( fabs( storeDenom ) > 0.0001 ) {

        /* x = (B F-C D)/(D^2-E F) */
        x = ( coeffs.at(5)*coeffs.at(1) - coeffs.at(2)*coeffs.at(3) ) / storeDenom;

        /* y = (C E-B D)/(D^2-E F) */
        y = ( coeffs.at(2)*coeffs.at(4) - coeffs.at(1)*coeffs.at(3) ) / storeDenom;
    }
    else {

        /* Alert the user of a denominator at zero. */
        cerr << "Error: Zero denominator (from solveForMax.cpp)." << endl;
        x = numeric_limits<double>::quiet_NaN();
        y = numeric_limits<double>::quiet_NaN();
    }
    return;
}
