#include <math.h>
#include<vector>

using namespace std;

#pragma once

class Weight {
    public:
    Weight();
    Weight(vector<double>&, vector<double>&);
    double wScale;
    vector<double> weightEtaa;
    vector<double> weightMut;
    vector<vector<double> > weightMatrix;
    vector<double> mutVec;
    vector<double> etaaVec;
    void reset( double );
    void updateWeightEtaa( double );
    void updateWeightMut( double, double );
    void updateWtBound( double, double );
    void updateMatrix();
};
