#include "measurement.h"

Measurement::Measurement() {
    this->dataType = UNKNOWN;
    this->value = 0.0;
}

Measurement::Measurement(DataType dataType, double value) {
    this->dataType = dataType;
    this->value = value;
}

DataType Measurement::getDataType() {
    return this->dataType;
}

double Measurement::getValue() {
    return this->value;
}

void Measurement::setDataType(DataType dataType) {
    this->dataType = dataType;
}

void Measurement::setValue(double value) {
    this->value = value;
}