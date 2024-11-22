#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include "defs.h"

class Measurement {
    private:
        Meridian meridian;
        double leftValue;
        double rightValue;
        double avgValue;
        
    public:
        Measurement(Meridian meridian);
        Measurement(Meridian meridian, double left, double right);
        
        Meridian getMeridian();
        double getAvgValue() const;
        double getLValue() const;
        double getRValue() const;
};

#endif // MEASUREMENT_H
