#include "weight.h"

/* Weight is an object that contains all information about a particle's weight and the
Importance sampling weighting functions. It is a member of the Particle class. */

/* Members:
    wScale: Scalar weight, to account for attenuation efficiently. Updated in scatter.
    weightEtaa, weight mut: Vectors holding the importance sampling weight for each etaa and mut
    weightMatrix: 2D vector that holds the total weight over the entire grid of etaa, mut combos
    etaaVec, mutVec: Vectors of etaa and mut values to search through (inverse problem)
*/

/******************************************************************************/

/* Default constructor: sets etaa to 10, mut to 100, and all weights to 1. */
Weight::Weight() {
    vector<double> storeVec( 5, 1 );
    mutVec = storeVec;
    etaaVec = storeVec;
    fill(mutVec.begin(), mutVec.end(), 1.0);
    fill(etaaVec.begin(), etaaVec.end(), 0.1);
    weightEtaa = storeVec;
    weightMut = storeVec;
    vector<vector<double> > storeMatrix(weightMut.size(),vector<double> (weightEtaa.size(), 0));
    weightMatrix = storeMatrix;
    wScale = 1;
}

/* Overload constructor: sets etaa and mut from inputs, sets all weights to 1. */
Weight::Weight(vector<double>& mutV, vector<double>& etaaV) {
    mutVec = mutV;
    etaaVec = etaaV;
    weightMut = mutVec;
    weightEtaa = etaaVec;
    vector<vector<double> > storeMatrix(weightMut.size(),vector<double> (weightEtaa.size(), 0));
    weightMatrix = storeMatrix;
    fill(weightEtaa.begin(),weightEtaa.end(),1);
    fill(weightMut.begin(),weightMut.end(),1);
    wScale = 1;
}

/* Resets all weights to 1. */
void Weight::reset(double T) {
    fill(weightEtaa.begin(),weightEtaa.end(),1);
    fill(weightMut.begin(),weightMut.end(),1);
    wScale = T;
}

/* Updates vector of adjusted etaa weights */
void Weight::updateWeightEtaa( double divVal ) {
    for( unsigned int j = 0; j < weightEtaa.size(); j++ ) {
        weightEtaa.at(j) *= (1 - etaaVec.at(j)) * divVal;
    }
}

/* Updates vector of mut weights in the case where the particle does not hit a
boundary. */
void Weight::updateWeightMut( double mut0, double t ) {
    for( unsigned int k = 0; k < weightMut.size(); k++ ) {
        weightMut.at(k) *= ( mutVec.at(k) / mut0 * exp( t * (mut0 - mutVec.at(k)) ) );
    }
}

/* Updates vector of mut weights in boundary case. On the probability distribution,
the boundary case represents a delta function scaled by the integral from position
d to infinity of the exponential distribution (because all values beyond d are relocated
into d). This integral is equal to exp( - t*mut ). */
void Weight::updateWtBound( double mut0, double t ) {
    for( unsigned int k = 0; k < weightMut.size(); k++ ) {
        weightMut.at(k) *= ( exp( t * (mut0 - mutVec.at(k)) ) );
    }
}

/* Updates weightMatrix by taking the outer product of weightEtaa and weightMut and
multiplying elementwise by scalar wScale. */
void Weight::updateMatrix() {
    for( unsigned int i = 0; i < weightMut.size(); i++ ) {
        for ( unsigned int j = 0; j < weightEtaa.size(); j++ ) {
            weightMatrix.at(i).at(j) = weightMut.at(i)*weightEtaa.at(j)*wScale;
        }
    }
}
