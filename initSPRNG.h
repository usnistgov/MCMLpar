#include "sprng.h"
#include <iostream>

using namespace std;

#pragma once

#ifdef SPRNGFIVE
#include "sprng_cpp.h"
bool initSPRNG( unsigned int, Sprng***, int );
#else
bool initSPRNG( unsigned int, int***, int );
#endif
