#include "summary.h"

Summary::Summary(Measurement* scan) : measurement(scan) {

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