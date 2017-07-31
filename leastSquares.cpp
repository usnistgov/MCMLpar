#include "leastSquares.h"
/* Written by Richelle Streater, June 2017. */

/* LeastSquares finds the least squares solution of a matrix equation Ax = b. It
converts vectors to matrices in the following way:

For a 3 by 3 matrix:
A =
    A.at(0).at(0)       A.at(0).at(1)       A.at(0).at(2)
    A.at(1).at(0)       A.at(1).at(1)       A.at(1).at(2)
    A.at(2).at(0)       A.at(2).at(1)       A.at(2).at(2)

For a 3 by 1 vector:
b =
    b.at(0)
    b.at(1)
    b.at(2)
*/

/******************************************************************************/

void leastSquares( const vector<vector<double> >& A, const vector<double>& b,
    vector<double>& x ) {

    /* Convert element-wise from C++ vectors to Eigen matrix and vector objects */
    MatrixXd Amat( b.size(), x.size() );
    VectorXd bVec( b.size() );
    for ( unsigned int i = 0; i < b.size(); i++ ) {
        bVec(i) = b.at(i);
        for ( unsigned int j = 0; j < x.size(); j++ ) {
            Amat(i, j) = A.at(i).at(j);
        }
    }

    VectorXd xVec = Amat.jacobiSvd(ComputeThinU | ComputeThinV).solve(bVec);

    /* Convert element-wise from Eigen vector object to C++ vector */
    for ( unsigned int k = 0; k < x.size(); k++ ) {
        x.at(k) = xVec(k);
    }
}
