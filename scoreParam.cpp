#include "scoreParam.h"

/* Written by Richelle Streater, June 2017. */

/* ScoreParam calculates likelihood function to store a score for each combination of
eta_a and mu_t on the parameter grid and store them all in fitMatrix. If likelihood
has returned an error, scoreParam will return FALSE to main, and the program will stop
running. Otherwise, scoreParam will return TRUE. */

/******************************************************************************/

bool scoreParam( const vector<vector<vector<double> > >& arsStore,
    vector<vector<double> >& fitMatrix, const vector<double>& expData,
    unsigned int m, unsigned int n ) {
    double l;

    /* Iterate over the dimensions of arsStore to evaluate likelihood
    at each element */
    for ( unsigned int i = 0; i < m; i++ ){
        for ( unsigned int j = 0; j < n; j++ ) {

            /* Store likelihood in l so that it only evaluates once */
            l = likelihood( arsStore.at(i).at(j), expData );

            /* Likelihood will return nan if there is an error. l!=l catches nan's. */
            if ( l != l ) {
                return false;
            }
            fitMatrix.at(i).at(j) = l;
        }
    }

    return true;
}
