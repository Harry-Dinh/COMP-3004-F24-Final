#include <iostream>
#include <random>
#include "measurement.h"

using namespace std;

Measurement::Measurement(Meridian meridian) {
    this->meridian = meridian;
    
    // Set up the random number generator (got this from a random stackoverflow forum)
    random_device rand;  // Obtain the random number from the hardware
    mt19937 gen(rand());  // Seed the generator
    uniform_int_distribution<> distr(RYODORAKU_MIN_BOUND, RYODORAKU_MAX_BOUND);  // Define the range
    
    // Assign the value for the left and right sides
    this->leftValue = distr(gen);
    this->rightValue = distr(gen);
    
    // Calculate the average value
    this->avgValue = (double) ((leftValue + rightValue) / 2);
}

Meridian Measurement::getMeridian() {
    return this->meridian;
}

double Measurement::getAvgValue() const {
    return this->avgValue;
}

double Measurement::getLValue() const {
    return this->leftValue;
}

double Measurement::getRValue() const {
    return this->rightValue;
}