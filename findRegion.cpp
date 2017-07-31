#include "findRegion.h"

/* Written by Richelle Streater, June 2017. */

/* FindRegion finds a rectangle of values on the likelihood grid where
the log likelihood value is within the chi-square limit specified by the
user. FindRegion assumes that the likelihood surface is smooth, so that
the values within the chi-square limit will be contiguous. It searches
boxes from left to right until it finds a chi-square value within the
limit. It does the same thing from top to bottom, right to left, and
bottom to top. */

/* Variables:
    iMin, jMin: Minimum bounding rectangle indices
    top, rightmost, bottom, leftmost: The original bounding box extrema
    i0, j0: The indices of the discrete maximum
    scale: Amount to limit region decrease by
*/

/******************************************************************************/

void findRegion( const vector<vector<double> >& likGrid, int& iMin,
    int& iMax, int& jMin, int& jMax, int i0, int j0 ){

    jMin = 0;
    iMin = 0;

    double scale = 2;

    int top = iMax;
    int rightmost = jMax;
    int bottom = 0;
    int leftmost = 0;

/**********************  Scan from left to right  *****************************/

    for ( int a = jMin+1; a <= jMax; a++ ) {

        //* Search a slice of the grid a from the left */
        if ( searchRegion( likGrid, top, a, bottom, a ) ) {
            jMin = a-1;
            break;
        }
        if ( a == jMax ) {
            cerr << "Error: could not decrease search region (from findRegion.cpp)" << endl;
            return;
        }
    }
/*******************  End of scan from left to right  *************************/

/**********************  Scan from right to left  *****************************/

    /* Scan from right to left */
    for ( int b = jMax-1; b >= jMin; b-- ) {

        /* Search a slice of the grid b from the right */
        if ( searchRegion( likGrid, top, b, bottom, b ) ) {
            jMax = b+1;
            break;
        }
        if ( b == jMin ) {
            cerr << "Error: could not decrease search region (from findRegion.cpp)" << endl;
            return;
        }
    }

/*******************  End of scan from right to left  *************************/

    /* Prevent region from getting too small (or it might lose the peak). Rescale
    the search region so that it will only be half of the original size */
    int currSize = jMax - jMin;
    if ( ( double( rightmost ) / ( currSize ) ) > scale ) {
        jMax = ceil( j0 + double( jMax - j0 ) * rightmost / ( currSize * scale ) );
        jMin = int( j0 - double( j0 - jMin ) * rightmost / ( currSize * scale ) );
    }

/**********************  Scan from bottom to top  *****************************/

    for ( int c = iMin+1; c <= iMax; c++ ) {

        /* Search a slice of the grid c from the bottom */
        if ( searchRegion( likGrid, c, rightmost, c, leftmost ) ) {
            iMin = c-1;
            break;
        }
        if (c == iMax) {
            cerr << "Error: could not decrease search region (from findRegion.cpp)" << endl;
            return;
        }
    }

/*******************  End of scan from bottom to top  *************************/

/**********************  Scan from top to bottom  *****************************/

    for ( int d = iMax-1; d >= iMin; d-- ) {

        /* Search a slice of the grid d from the top */
        if ( searchRegion( likGrid, d, rightmost, d, leftmost ) ) {
            iMax = d+1;
            break;
        }
        if ( d == iMin ) {
            cerr << "Error: could not decrease search region (from findRegion.cpp)" << endl;
            return;
        }
    }

/*******************  End of scan from top to bottom  *************************/

    /* Prevent region from getting too small (or it might lose the peak). Rescale
    the search region so that it will only be half of the original size */
    currSize = iMax-iMin;
    if ( ( double( top ) / ( currSize ) ) > scale ) {
        iMax = ceil( i0 + double( iMax - i0 ) * top / ( currSize * scale ) );
        iMin = int( i0 - double( i0 - iMin ) * top / ( currSize * scale ) );
    }
}
