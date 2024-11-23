#ifndef SCAN_H
#define SCAN_H

#include "measurement.h"

/**
 * @brief A class that is responsible for checking if its measurement object is within the 50-70 bound.
 * @todo Since this class only houses a function, it might not worth keeping around. I'm still going to leave it here because of the function implementation. However, Asaad, since you're doing the data visualization, you should incorporate this function of mine into your Summary class then dispose of this Scan class.
 */
class Scan {
    private:
        Measurement* measurement;
        
    public:
        Scan(Measurement* measurement);
        
        /**
         * @brief Check if the provided value is within the pre-defined bound (check in defs.h)
         * @param valueToCheck the value to check for
         * @return
         * -1 if lower than pre-defined bound
         * 0 if within the pre-defined bound
         * 1 if higher than the pre-defined bound
         */
        int healthChecking(double valueToCheck);
};

#endif // SCAN_H