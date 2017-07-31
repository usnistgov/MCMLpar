#include "likelihood.h"
#include <vector>

using namespace std;

#pragma once

bool scoreParam( const vector<vector<vector<double> > >&,
    vector<vector<double> >&, const vector<double>&, unsigned int, unsigned int );
