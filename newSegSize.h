#include "sprng.h"
#include <math.h>

using namespace std;

#pragma once

#ifdef SPRNGFIVE
double newSegSize( Sprng* );

#else
double newSegSize( int* );
#endif

