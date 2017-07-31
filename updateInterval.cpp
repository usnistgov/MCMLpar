#include "updateInterval.h"

/* Written by Richelle Streater, June 2017. */

/* UpdateInterval updates the mut and etaa vectors of parameters to test for the next
time around the control loop. UpdateInterval finds the discrete maximum of the
likelihood grid and fits a paraboloid around it on the last iteration. It
calls findRegion to obtain the new discrete bounds for the confidence interval.
Finally, it updates and prints the new range of eta_a and mu_t. */

/* Variables:
    dmut, detaa: The difference between each entry in the mut and etaa vectors
    i0, j0: The index of the discrete maximum in the mut and etaa vectors, respectively
    likGrid: The matrix of likelihood values over the grid of vectors mut and etaa
    storeParab: The non-linear coefficients of the paraboloid and the MLE values
*/

/******************************************************************************/

bool updateInterval( const vector<vector<double> >& likGrid, vector<double>& storeParab,
    vector<double>& mutVec, vector<double>& etaaVec, bool last ) {

    int mutSize = mutVec.size();
    int etaaSize = etaaVec.size();
    int i0 = 0, j0 = 0;
    int iMin, jMin;
    int iMax = mutSize-1, jMax = etaaSize-1;
    double dmut, detaa;

    dmut = ( mutVec.back() - mutVec.front() ) / ( mutSize - 1 );
    detaa = ( etaaVec.back() - etaaVec.front() ) / ( etaaSize - 1 );

    /* Find the discrete maximum of likGrid. Quit program if there is none. */
    if ( !discMax( likGrid, i0, j0, mutSize, etaaSize ) ) {
        return false;
    }

    /* On the last region, find the entire confidence paraboloid */
    if ( last ) {
        return contour( likGrid, storeParab, etaaVec, mutVec, i0, j0 );
    }

    findRegion( likGrid, iMin, iMax, jMin, jMax, i0, j0 );

    /* Update mut, etaa vectors */
    mutVec.at(0) = mutVec.at(i0) - dmut * ( i0 - iMin );
    etaaVec.at(0) = etaaVec.at(j0) - detaa * ( j0 - jMin );
    dmut *= double( iMax - iMin ) / ( mutSize - 1 );
    detaa *= double( jMax - jMin ) / ( etaaSize - 1 );

    for ( unsigned int i = 1; i < mutSize; i++ ) {
        mutVec.at(i) = mutVec.at(i-1) + dmut;
    }

    for ( unsigned int j = 1; j < etaaSize; j++ ) {
        etaaVec.at(j) = etaaVec.at(j-1) + detaa;
    }

    /* Print out new search interval */
    cout << "mu_t bounds: (" << mutVec.front() << ", " << mutVec.back()
        << ")" << endl;

    cout << "eta_a bounds: (" << etaaVec.front() << ", "
        << etaaVec.back() << ")" << endl << endl;

    return true;
}
