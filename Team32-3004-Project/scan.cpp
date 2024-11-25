#include "scan.h"
#include "defs.h"

Scan::Scan(Measurement* measurement) {
    this->measurement = measurement;
}

int Scan::healthChecking(double valueToCheck) {
    if (valueToCheck < HEALTHY_LOWER_BOUND) {
        return -1;
    } else if (valueToCheck > HEALTHY_UPPER_BOUND) {
        return 1;
    } else {
        return 0;
    }
}