#include "dotProd.h"

/* Written by Richelle Streater, May 2017. */

/* DotProd computes the dot product between two input vectors. */

/******************************************************************************/

double dotProd( const vector<double> &v1, const vector<double> &v2 ) {
	double total = 0;
	for( unsigned int i = 0; i < v1.size(); i++ ) {
		total += v1.at(i)*v2.at(i);
	}
	return total;
}
