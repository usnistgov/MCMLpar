#include "setParameters.h"

/* Written by Richelle Streater, May 2017. */

/* SetParameters sets user-defined values from an input file. It is called by main.
SetParameters defines a stringstream to control which lines to include and which to
ignore. SetParameters ignores everything after a tab or a #, and completely ignores
contents of empty lines and lines that start with a #. This allows commenting
in the input file. For now, the material is considered to be single-layer.
SetParameters returns TRUE if there is no file error and FALSE if there is,
so that the program will close if there is a problem. */

/* Variables:
    numParticles: number of particles or photons for simulation
    numDiv: The number of points to score in the ARS vector
    numProc: Number of processors to use (parallelization)
    layerVec: The vector of layers for the entire medium.
    numLayers: Number of layers in the material
    nVal, gVal, zMax, muaVal, musVal: Parameters of the medium
    radius: Radius of detector (in experiment)
*/

/******************************************************************************/

bool setParameters( vector<Layer>& layerVec, unsigned int& numParticles,
     unsigned int& numDiv, unsigned int& numProc, int& seedIn, double& radius ){

    ifstream paramFile( "dataIn/input.txt" );
    unsigned int numLayers;
    double nVal, gVal, t, muaVal, musVal;
    string line;
    stringstream l;

/*********************  Read file to stringstream  ****************************/

    if ( paramFile.is_open() ) {
        while( getline( paramFile, line ) ){

            /* Ignore lines that start with # or that have no contents */
                /* Ignore all line contents beyond tab or # */
            if ( ( line[0] != '#' ) && ( line.size()>0 ) ) {
                for (int i=0; i<line.size(); i++) {
                    if ( ( line[i] == '\t' ) || ( line[i] == '#' ) ) {
                        line.resize(i);
                        break;
                    }
                }
                l << line;
                l << '\n';
            }
        }

/*****************  End of reading file to stringstream  **********************/

/******************* Read stringstream to parameters  *************************/

        /* Read in all values from stringstream in order */
        l >> numParticles;
        l >> numDiv;
        l >> numProc;
        l >> seedIn;
        l >> radius;
        l >> numLayers;

        layerVec.resize(numLayers);
        for ( unsigned int i = 0; i < numLayers; i++ ) {
            l >> nVal;
            l >> gVal;
            l >> t;
            l >> muaVal;
            l >> musVal;
            layerVec.at(i) = Layer( nVal, musVal, muaVal, gVal, t );
            layerVec.at(i).setLayerNum(i);
            if ( i > 0 ) {
                layerVec.at(i).setZMin( layerVec.at(i-1).getZMax() );
                layerVec.at(i).setZMax( layerVec.at(i).getZMin() + t );
            }
        }
    }

/***************  End of reading stringstream to parameters  ******************/

    else {
        cerr << "Error: File did not open (in setParameters.cpp)." << endl;
        return false;
    }

    paramFile.close();
    /* numProc is not defined when the file does not read properly */
    if ( numProc > 5000 ) {
        cerr << "File reading error (in setParameters.cpp)." << endl;
        return false;
    }
    return true;
}
