#include "summary.h"

Summary::Summary(Measurement* measurement) : measurement(measurement) {

}

int Summary::getUserID() const {
    return measurement->getUserID();
}

QString Summary::getTimeRecorded() {
    return measurement->getTimeRecorded();
}

int Summary::getAmountOfMeasurements() {
    return measurement->getValues().size();
}