#include "summary.h"

Summary::Summary(Measurement* scan) : scan(scan) {

}

int Summary::getUserID() const {
    return scan->getUserID();
}

QString Summary::getTimeRecorded() {
    return scan->getTimeRecorded();
}

int Summary::getAmountOfMeasurements() {
    return scan->getValues().size();
}