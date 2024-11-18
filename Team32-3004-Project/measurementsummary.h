#ifndef MEASUREMENTSUMMARY_H
#define MEASUREMENTSUMMARY_H

#include <vector>
#include <QObject>
#include "measurement.h"

using namespace std;

/// @brief An object holding the necessary information for the vitals summary section.
class MeasurementSummary: public QObject {
    Q_OBJECT
    
    private:
        /// @brief A collection of measurements taken by the user.
        vector<Measurement> measurements;
        
        /// @brief The average vital value.
        double average;
    
    public:
        MeasurementSummary(QObject* parent, vector<Measurement>& src);
        
        double findAverage();
        
        /// @todo Add more functions for calculating algorithms here if needed...
};

#endif // MEASUREMENTSUMMARY_H
