#include "evalMaxGrid.h"

/* Written by Richelle Streater, June 2017. */

/* EvalMaxGrid copies the likelihood at the 9 points surrounding i0, j0 into a vector.

When f(i0, j0) = likelihood at (i0, j0) and i0 and j0 are the discrete maximum indices:

fitPoints =
    f(i0 - 1, j0 - 1)
    f(i0 - 1, j0)
    f(i0 - 1, j0 + 1)
    f(i0, j0 - 1)
    f(i0, j0)
    f(i0, j0 + 1)
    f(i0 + 1, j0 - 1)
    f(i0 + 1, j0)
    f(i0 + 1, j0 + 1)

 */

/******************************************************************************/

void evalMaxGrid( const vector<vector<double> >& likGrid, vector<double>&
    fitPoints, int& iMax, int& jMax ){

    /* Set the new matrix values. Unroll the 3x3 set of points into a 9x1 vector */
    for ( unsigned int k = 0; k < 3; k++ ) {
        for ( unsigned int q = 0; q < 3; q++ ) {
            fitPoints.at(3*k+q) = likGrid.at(k-1+iMax).at(q-1+jMax);
        }
    }
}
