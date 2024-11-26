#include "summary.h"

Summary::Summary(Scan* scan) : scan(scan) {

}

int Summary::getUserID() const {
    return scan->getUserID();
}

QString& Summary::getTimeRecorded() {
    return scan->getTimeRecorded();
}

int Summary::getAmountOfMeasurements() {
    return scan->getMeasurements().size();
}

double Summary::getBaseline() {
    return scan->calculateBaseline();
}
