#include "dataOut.h"

/* Written by Richelle Streater, June 2017. */

/* DataOut creates the output file for the program. It creates a
file with the time elapsed and the ARS curve. */

/* 20170923. Revision Zachary Levine
 *  write angle in degrees at mid-point in addition to value
 *     uniform steps in (0,180), e.g.,   30 90 150 if nAngle==3
 *  writes endl for all lines
*/

/******************************************************************************/

void dataOut( const vector<double>& dataList, unsigned int timeCount ) {
    string fnFolder = "dataOut/MCMLparOutput.csv";

    /* Set up file to save to. */
    ofstream saveData;
    saveData.open( fnFolder.c_str() );

#if 0
 OLD CODE ... DELETE SOON
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
#endif

    unsigned int nAngle = dataList.size();
    /* Check for opening error and save file */
    if ( saveData.is_open() ) {
        saveData << "Time elapsed: " << timeCount << " s" << endl;
        saveData << "Angle Resolved Scattering Values: " << endl;
        for ( unsigned int i = 0; i < dataList.size(); i++ ) {
            double thetaDeg = (i+0.5) * 180. / nAngle;
            saveData << thetaDeg << " " << dataList.at(i) << endl;
        }
    }
    else {
        cerr << "File did not open (from dataOut.cpp)." << endl;
    }
}
