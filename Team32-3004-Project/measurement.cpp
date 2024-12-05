#include <iostream>
#include <random>
#include "defs.h"
#include "measurement.h"

Measurement::Measurement(int userID, QDateTime& timeRecorded) {
    this->userID = userID;
    this->timeRecorded = timeRecorded.toString();
}

Measurement::Measurement(int userID, QDateTime& timeRecorded, QVector<double> meridianValues) {
    this->userID = userID;
    this->timeRecorded = timeRecorded.toString();
    this->meridianValues = meridianValues;
}

int Measurement::getUserID() const {
    return this->userID;
}

QString Measurement::getTimeRecorded() {
    return this->timeRecorded;
}

QVector<double> Measurement::getValues() {
    return this->meridianValues;
}

double Measurement::getValue(int index) const {
    if (index < 0 || index > int(meridianValues.size()) - 1 || meridianValues.empty()) {
        cout << "Index out of bounds or array is empty" << endl;
        return -1;
    }
    return meridianValues[index];
}

void Measurement::setUserID(int userID) {
    this->userID = userID;
}

void Measurement::setTimeRecorded(QDateTime& timeRecorded) {
    this->timeRecorded = timeRecorded.toString();
}

void Measurement::setArray(QVector<double> src) {
    this->meridianValues = src;
}

void Measurement::addValue(double value) {
    this->meridianValues.push_back(value);
}

string Measurement::interpretValue(double value) {
    if (value < HEALTHY_LOWER_BOUND) return "Hypoactive";
    else if (value > HEALTHY_UPPER_BOUND) return "Hyperactive";
    return "Balanced";
}
