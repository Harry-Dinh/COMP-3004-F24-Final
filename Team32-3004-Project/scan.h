#ifndef SCAN_H
#define SCAN_H

#include <iostream>
#include <vector>
#include <QDateTime>

using namespace std;

/// @brief An object representing one full scan with 24 measurements.
/// @todo Create a vector of `Scan` object somewhere to hold things for the history
class Scan {
    private:
        /// @brief The ID associated with the user profile that took this scan.
        int userID;
        
        /// @brief A collection of measurement values that are recorded each time the device is pressed against the body. There should be 24 of these values.
        vector<double> measurements;
        
        /// @brief The time that the scan was recorded in string form.
        QString timeRecorded;
    
    public:
        Scan(int userID, QDateTime& timeRecorded);
        
        // GETTERS AND SETTERS
        
        int getUserID() const;
        double getMeasurement(int index) const;
        vector<double>& getMeasurements();
        QString& getTimeRecorded();
};

#endif // SCAN_H