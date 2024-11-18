#include "measurementsummary.h"

MeasurementSummary::MeasurementSummary(QObject* parent, vector<Measurement>& src): QObject(parent) {
    this->measurements = src;
    this->average = findAverage();
}

double MeasurementSummary::findAverage() {
    /// @note I'm returning the value of the energy level measurement because in the App Store screenshot, I noticed that the value of the measurement is identical to that of the energy level.
    for (Measurement measurement : measurements) {
        if (measurement.getDataType() == ENERGY_LVL) return measurement.getValue();
    }
    return 0.0;
}