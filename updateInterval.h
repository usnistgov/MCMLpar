#include "contour.h"
#include "discMax.h"
#include "findRegion.h"
#include <vector>
#include <iostream>

using namespace std;

#pragma once

bool updateInterval( const vector<vector<double> >&, vector<double>&, vector<double>&,
    vector<double>&, bool );
