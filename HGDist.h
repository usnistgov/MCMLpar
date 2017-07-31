#include "sprng.h"
#include <math.h>
#include <iostream>

using namespace std;

#pragma once

#ifdef SPRNGFIVE
double HGDist( double, Sprng* );
#else
double HGDist( double, int* );
#endif
