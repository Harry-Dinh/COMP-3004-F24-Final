#include "scan.h"

Scan::Scan(int userID, QDateTime& timeRecorded) {
    this->userID = userID;
    this->timeRecorded = timeRecorded.toString();
}

int Scan::getUserID() const {
    return this->userID;
}

double Scan::getMeasurement(int index) const {
    if (index < 0 || index > measurements.size() || measurements.empty()) return -1;
    return measurements[index];
}

vector<double>& Scan::getMeasurements() {
    return this->measurements;
}

QString& Scan::getTimeRecorded() {
    return this->timeRecorded;
}