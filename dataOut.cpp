#include "dataOut.h"

/* Written by Richelle Streater, June 2017. */

/* DataOut creates the output file for the program. It creates a
file with the time elapsed and the ARS curve. */

/******************************************************************************/

void dataOut( const vector<double>& dataList, unsigned int timeCount ) {
    string fnFolder = "dataOut/MCMLparOutput.csv";

    /* Set up file to save to. */
    ofstream saveData;
    saveData.open( fnFolder.c_str() );

    /* Check for opening error and save file */
    if ( saveData.is_open() ) {
        saveData << "Seconds elapsed: " << timeCount << " s" << endl;
        saveData << "Angle Resolved Scattering Values: " << endl;
        for ( unsigned int i = 0; i < dataList.size()-1; i++ ) {
            saveData << dataList.at(i) << endl;
        }
        saveData << dataList.back();
    }
    else {
        cerr << "File did not open (from dataOut.cpp)." << endl;
    }
}
