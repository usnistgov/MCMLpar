#include "layer.h"
#include "particle.h"
#include "sprng.h"
#include <math.h>
#include <vector>

using namespace std;

#pragma once

#ifdef SPRNGFIVE
bool medInterface( Particle&, Layer&, Sprng* );

#else
bool medInterface( Particle&, Layer&, int* );
#endif
