#include "checkEigenVals.h"
#include "constructA.h"
#include "evalMaxGrid.h"
#include "findRegion.h"
#include "leastSquares.h"
#include "solveForMax.h"
#include <vector>
#include <iostream>

using namespace std;

#pragma once

bool contour( const vector<vector<double> >&, vector<double>&,
    vector<double>&, vector<double>&, int, int );
