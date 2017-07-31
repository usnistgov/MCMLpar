#include "contour.h"

/* Written by Richelle Streater, July 2017. */

/* Contour outputs the contour parameters for the output and Mathematica file.
It is called by updateInterval in the last iteration of updating the search box.
It fits the 9 points around the discrete likelihood maximum to a paraboloid and
solves for the discrete maximum. Contour will return FALSE if there is no true
maximum (due to a minimum or saddle point) and TRUE if there is a maximum. */

/* Variables:
    dmut, detaa: The difference between each entry in the mut and etaa vectors
    etaaMle, mutMle: Maximum likelihood estimate for etaa and mut
    gridEval: The 9 likelihood values to fit the paraboloid to
    A: Each variable term of the paraboloid to be fit for all 9 gridEval points
    coeffs: The least squares solution, or coefficients of the paraboloid
    storeParab: The non-linear coefficients of the paraboloid and the MLE values
*/

/******************************************************************************/

bool contour( const vector<vector<double> >& likGrid, vector<double>& storeParab,
    vector<double>& etaaVec, vector<double>& mutVec, int i0, int j0 ) {

    /* Initialize variables and vectors */
    double dmut, detaa;
    double etaaMle = 0, mutMle = 0;
    dmut = ( mutVec.back() - mutVec.front() ) / ( mutVec.size() - 1 );
    detaa = ( etaaVec.back() - etaaVec.front() ) / ( etaaVec.size() - 1 );
    vector<double> gridEval(9);
    vector<double> coeffs(6);
    vector<vector<double> > A( 9, vector<double>( 6, 0 ) );

    /* Fit a paraboloid around the discrete maximum by solving the least squares equation */
    evalMaxGrid( likGrid, gridEval, i0, j0 );
    constructA( A, dmut, detaa );
    leastSquares( A, gridEval, coeffs );

    /* These first three entries in storeParab are also the entries of the Hessian matrix */
    storeParab.at(0) = coeffs.at(4);
    storeParab.at(1) = coeffs.at(3);
    storeParab.at(2) = coeffs.at(5);

    /* Check if there is really a maximum, not a saddle point or a minimum */
    if ( !checkEigenVals( storeParab ) ) {
        return false;
    }

    /* Find the maximum of the paraboloidal fit */
    solveForMax( coeffs, etaaMle, mutMle );
    etaaMle += etaaVec.front() + j0*detaa;
    mutMle += mutVec.front() + i0*dmut;
    storeParab.at(3) = etaaMle;
    storeParab.at(4) = mutMle;
    cout << "eta_a = " << etaaMle << endl;
    cout << "mu_t = " << mutMle << endl << endl;
    return true;
}

