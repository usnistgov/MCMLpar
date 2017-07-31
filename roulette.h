#include "particle.h"
#include "sprng.h"

using namespace std;

#pragma once

#ifdef SPRNGFIVE
bool roulette( Particle&, Sprng* );

#else
bool roulette( Particle&, int* );
#endif
