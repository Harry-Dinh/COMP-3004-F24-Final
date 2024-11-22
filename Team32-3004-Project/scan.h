#ifndef SCAN_H
#define SCAN_H

#include <iostream>
#include <vector>
#include <QDateTime>
#include "measurement.h"

using namespace std;

/// @brief An object representing one full scan with 24 measurements.
/// @todo Create a vector of `Scan` object somewhere to hold things for the history
class Scan {
    private:
        /// @brief The ID associated with the user profile that took this scan.
        int userID;
        
        /// @brief A collection of measurement values that are recorded each time the device is pressed against the body. There should be 24 of these values.
        vector<Measurement*> measurements;
        
        /// @brief The baseline/average value of the measurements
        double measurementBaseline;
        
        /// @brief The time that the scan was recorded in string form.
        QString timeRecorded;
        
        /**
         * @brief The data that represent each of the health category (energy level, metabolism, immume system, psycho-emotional state and musculoskeletal system)
         * The following are the associated meridian points to each health category
         * - [0] Energy level: same as baseline value
         * - [1] Metabolism: spleen, stomach, kidney
         * - [2] Immune system: lung, large intestine
         * - [3] Psyco-emotional state: heart, liver, heart constrictor
         * - [4] Musculoskeletal system: bladder, gallbladder, stomach, liver, triple heater
         */
        vector<double> healthCategoriesData;
    
    public:
        Scan(int userID, QDateTime& timeRecorded);
        
        // GETTERS AND SETTERS
        
        int getUserID() const;
        Measurement* getMeasurement(int index) const;
        vector<Measurement*>& getMeasurements();
        QString& getTimeRecorded();
        
        // SCAN CLASS OPERATIONS
        
        double calculateBaseline();
        void initBaseline();
        Measurement* getMeasurementWith(Meridian meridian);
        void addMeasurement(Measurement* measurement);
        void initHealthCategoriesData();
};

#endif // SCAN_H