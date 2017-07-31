#include "discMax.h"

/* Written by Richelle Streater, June 2017. */

/* DiscMax finds the location of the discrete maximum of a grid of values. DiscMax
returns false if the maximum falls on an edge. */

/******************************************************************************/

bool discMax( const vector<vector<double> >& grid, int& iMax, int& jMax,
    unsigned int mutSize, unsigned int etaaSize ) {

    double maxVal = grid.at(0).at(0);

    /* Iterate through matrix to find position of max value, save position */
    for ( unsigned int i = 0; i < mutSize; i++ ) {
        for ( unsigned int j = 0; j < etaaSize; j++ ) {
            if ( grid.at(i).at(j) > maxVal ) {
                maxVal = grid.at(i).at(j);
                iMax = i;
                jMax = j;
            }
        }
    }

    /* Check to see if there is a real maximum, or if it is on the edges */
    if ( (iMax < 1) || (jMax < 1) || (iMax > mutSize-2) || (jMax > etaaSize-2) ) {
        cerr << "Error: Maximum out of bounds (from discMax.cpp)" << endl;
        return false;
    }
    return true;
}
