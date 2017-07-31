#include "searchRegion.h"

/* Written by Richelle Streater, June 2017. */

/* SearchRegion searches through a part of the eta_a and mu_t parameter space.
Given minimum and maximum values in the eta_a and mu_t direction, it returns
TRUE if any likelihood value in that region is beyond the chi-square limit and
FALSE if all likelihood values are beyond the chi-square limit.  */

/******************************************************************************/

bool searchRegion( const vector<vector<double> >& likGrid, unsigned int top,
    unsigned int rightmost, unsigned int bottom, unsigned int leftmost ){

    /* This corresponds to a confidence interval. The choice of this makes very
    little difference to the program, so it was left out of the input file for now. */
    double chiSquareVal = 13.816;

    for ( unsigned int i = bottom; i <= top; i++) {
        for ( unsigned int j = leftmost; j <= rightmost; j++) {
            if ( likGrid.at(i).at(j) > -chiSquareVal ) {
                return true;
            }
        }
    }
    return false;
}
