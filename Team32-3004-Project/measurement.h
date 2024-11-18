#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include "defs.h"

/// @brief A class that represent a measurement that the user take with the RaDoTech device.
class Measurement {
    private:
        /// @brief The data type that the measurement is for (i.e. energy level, metabolism...)
        DataType dataType;
        
        /// @brief The value (in millivolt) associated with the measurement.
        double value;
    
    public:
        Measurement();
        Measurement(DataType dataType, double value);
        
        DataType getDataType();
        double getValue();
        
        void setDataType(DataType dataType);
        void setValue(double value);
};

#endif // MEASUREMENT_H