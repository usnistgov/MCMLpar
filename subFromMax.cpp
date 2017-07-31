#include "subFromMax.h"

/* Written by Richelle Streater, June 2017. */

/* SubFromMax subtracts a grid of likelihood values by its maximum so that the maxiumum
is zero and all other values are negative. The likelihood surface must be in this form
in order to generate correct confidence regions. */

/******************************************************************************/

void subFromMax( vector<vector<double> >& toSub, unsigned int m, unsigned int n ) {
    double maxValue = toSub.at(0).at(0);

    /* Find the maximum likelihood value by iterating through each element */
    for ( unsigned int i = 0; i < m; i++ ) {
        for ( unsigned int j = 0; j < n; j++ ) {
            if ( maxValue > toSub.at(i).at(j) ) {
                maxValue = toSub.at(i).at(j);
            }
        }
    }

    /* Subtract max value from each element and multiply by (-1) */
    for ( unsigned int i = 0; i < m; i++ ) {
        for ( unsigned int j = 0; j < n; j++ ) {
            toSub.at(i).at(j) = maxValue - toSub.at(i).at(j);
        }
    }
}
