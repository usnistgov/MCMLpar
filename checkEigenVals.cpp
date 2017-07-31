#include "checkEigenVals.h"

/* Written by Richelle Streater, June 2017. */

/* CheckEigenVals calculates the Hessian eigenvalues to ensure that we have
found a maximum on the likelihood surface, not a saddle point or a minimum.
Both eigenvalues should be negative. CheckEigenVals returns FALSE if there
is not a maximum and TRUE if there is. */

/* Variables:
    D: Determinate of Hessian
    T: Trace of Hessian
    lambda1, lambda2: Eigenvalues of Hessian
*/

/******************************************************************************/

bool checkEigenVals( const vector<double>& hessian ) {
    double D = hessian.at(0)*hessian.at(2) - hessian.at(1)*hessian.at(1);
    double T = hessian.at(0) + hessian.at(2);

    /* This condition will lead to a negative under a square root when finding the eigenvalues. */
    if ( T*T/4 < D ) {
        cerr << "Error: unreal eigenvalues (from checkEigenVals.cpp)" << endl;
        return false;
    }

    double lambda1 = T/2 + sqrt(T*T/4 - D);
    double lambda2 = T/2 - sqrt(T*T/4 - D);

    /* Now that we know the eigenvalues are real, they can both be negative, be one
    of each, or both be positive. */
    if ( lambda1 >= 0 ) {
        if ( lambda2 < 0 ) {
            cerr << "Error: saddle point (from checkEigenVals.cpp)" << endl;
            return false;
        }
        else {
            cerr << "Error: minimum (from checkEigenVals.cpp)" << endl;
            return false;
        }
    }

    else {
        if ( lambda2 > 0 ) {
            cerr << "Error: saddle point (from checkEigenVals.cpp)" << endl;
            return false;
        }
        else return true;
    }
}
