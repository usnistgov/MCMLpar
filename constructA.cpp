#include "constructA.h"
/* Written by Richelle Streater, June 2017. */

/* ConstructA constructs matrix A, which is each term of a paraboloid
evaluated at each etaa and mut value. The paraboloid has the following form:

    P(x,y) = a + bx + cy + dxy + ex^2/2 + fy^2/2
    or
    P(x,y) = aA(0) + bA(1) + cA(2) + dA(3) + eA(4) + fA(5)
*/

/******************************************************************************/

void constructA( vector<vector<double> >& A, double dmut, double detaa ) {
    for ( int i = 0; i < 3; i++ ) {
        for ( int j = 0; j < 3; j++ ) {
            A.at(3*i + j) = {1, detaa*(j-1), dmut*(i-1), dmut*detaa*(i-1)*(j-1),
                detaa*detaa*(j-1)*(j-1)/2.0, dmut*dmut*(i-1)*(i-1)/2.0};
        }
    }
}
