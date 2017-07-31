#include "boundary.h"

/* Written by Richelle Streater, June 2017. */

/* Boundary is called by main when a particle is at a boundary between layers.
It first checks whether the particle is in the first or last layer of a
medium and is moving in the right direction to escape it. It calls medInterface
to use the Fresnel coefficients and determine whether the particle should switch
layers. If the particles escapes the medium, boundary returns 4 to call detect
in main. Otherwise it returns 2 to propagate again. */

/******************************************************************************/

int boundary( Particle& par, Layer& airLayer, vector<Layer>& layerVec ) {

        double kz = par.dir.at(2);

        /* Let particle escape medium entirely. If the particle wants to move beneath the
        first layer, or above the last layer, it could escape.  */
        if ( ( ( par.lay.getLayerNum() == 0 ) && ( kz < 0 ) ) ||
        ( ( par.lay.getLayerNum() == layerVec.size() - 1 ) && ( kz > 0 ) ) ) {

            /* Return 4 if the particle has escaped medium */
            if ( medInterface( par, airLayer, par.sprngptr ) ) {

                /* Call detect in main. */
                return 4;
            }
        }

        /* Case where particle moves from one material to another in medium */
        else {
            if ( kz > 0 ) {
                medInterface( par, layerVec.at( par.lay.getLayerNum() + 1 ), par.sprngptr );
            }

            else {
                medInterface( par, layerVec.at( par.lay.getLayerNum() - 1 ), par.sprngptr );
            }
        }

        /* Call propagate in main */
        return 2;
}
