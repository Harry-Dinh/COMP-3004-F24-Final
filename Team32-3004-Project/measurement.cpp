#include <iostream>
#include <random>
#include "defs.h"
#include "measurement.h"

Measurement::Measurement(int userID, QDateTime& timeRecorded) {
    this->userID = userID;
    this->timeRecorded = timeRecorded.toString();
}

Measurement::Measurement(int userID, QDateTime& timeRecorded, vector<double>& meridianValues) {
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

vector<double>& Measurement::getValues() {
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

void Measurement::setArray(vector<double>& src) {
    this->meridianValues = src;
}

void Measurement::addExistingValue(double existingValue) {
    this->meridianValues.push_back(existingValue);
}

void Measurement::generateValue() {
    // Set up the random number generator (got this from some random stackoverflow forum)
    random_device rand;
    mt19937 gen(rand());
    uniform_int_distribution<> distr(RYODORAKU_MIN_BOUND, RYODORAKU_MAX_BOUND); // Define the range (5, 160)

    // Generate the random value then add it to the back of the array
    double randValue = distr(gen);
    this->meridianValues.push_back(randValue);
}
