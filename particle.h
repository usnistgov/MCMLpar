#include "layer.h"
#include <vector>

#ifdef SPRNGFIVE
#include "sprng_cpp.h"
#endif

using namespace std;

#pragma once

class Particle {
    public:
    #ifdef SPRNGFIVE
	Particle( double, Sprng* );
    Sprng* sprngptr;

    #else
    Particle( double, int* );
    int* sprngptr;
    #endif

	Particle();
	void reset( double );
	void updatePosition( double );
	vector<double> rVec;
	vector<double> dir;
    Layer lay;
    double weight;
};
