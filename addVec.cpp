#include "addVec.h"

/* Written by Anne-Michelle Lieberson, July 2017. */

/* AddVec adds two 1D vectors element-wise and saves the contents to the first vector. Main calls
addVec to add the ARS results from each processor together. */

/******************************************************************************/

void addVec( vector<double> &v1, const vector<double> &v2 ) {
    for ( unsigned int k = 0; k < v1.size(); k++ ) {
        v1.at(k)+=v2.at(k);
    }
}
