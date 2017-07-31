#include "fileToVec.h"

/* Written by Richelle Streater, June 2017. */

/* FileToVec reads contents of file into a vector */

/********************************************************************/

void fileToVec( vector<double> &storageVec, const string& fileName ) {
    double currentVal;
    stringstream l;
    string line = "";
    ifstream inputFile( fileName );
    unsigned int n=0;

    /* Save all lines to a stringstream */
    if ( inputFile.is_open() ) {
        while ( getline(inputFile,line) ) {
            if ( line.size()>0 ) {
                n++;
                l << line;
                l << '\n';
            }
        }
    }

    else {
        cerr << "Error: File did not open (in fileToVec.cpp)." << endl;
        return;
    }

    /* Input stringstream to vector */
    for ( unsigned int i = 0; i < n; i++ ) {
        l >> currentVal;
        storageVec.push_back( currentVal );
    }
}
