#include "scan.h"

Scan::Scan(int userID, QDateTime& timeRecorded) {
    this->userID = userID;
    this->timeRecorded = timeRecorded.toString();
    this->measurementBaseline = 0;
}

int Scan::getUserID() const {
    return this->userID;
}

Measurement* Scan::getMeasurement(int index) const {
    if (index < 0 || index > measurements.size() - 1 || measurements.empty()) return nullptr;
    return measurements[index];
}

vector<Measurement*>& Scan::getMeasurements() {
    return this->measurements;
}

QString& Scan::getTimeRecorded() {
    return this->timeRecorded;
}

double Scan::calculateBaseline() {
    if (measurements.empty()) return -1;
    double sum = 0;
    for (Measurement* measurement : measurements) {
        sum += measurement->getAvgValue();
    }
    return (double) (sum / 2);
}

/// @note Call this method when all you already have 12 measurements to assign the member baseline variable!
void Scan::initBaseline() {
    this->measurementBaseline = calculateBaseline();
}

void Scan::addMeasurement(Measurement* measurement) {
    if (measurement == nullptr) {
        cout << "Provided measurement argument is null! Unable to add." << endl;
        return;
    }
    measurements.push_back(measurement);
}

Measurement* Scan::getMeasurementWith(Meridian meridian) {
    if (meridian == UNKNOWN_T) return nullptr;
    
    for (Measurement* measurement : measurements) {
        if (measurement->getMeridian() == meridian) return measurement;
    }
    return nullptr;
}

void Scan::initHealthCategoriesData() {
    // Must have enough 12 measurements in order to calculate
    if (measurements.size() != MEASUREMENT_COUNT) {
        cout << "Not enough measurements, unable to calculate data for health categories!" << endl;
        return;
    }
    
    double averageValue;
    
    // Energy level (same as baseline)
    healthCategoriesData.push_back(calculateBaseline());
    
    // Immune system (lung, large intestine)
    Measurement* lungM = getMeasurementWith(LUNG);
    Measurement* lIntestineM = getMeasurementWith(LARGE_INTESTINE);
    averageValue = (double) ((lungM->getAvgValue() + lIntestineM->getAvgValue()) / 2);
    healthCategoriesData.push_back(averageValue);
    
    // Metabolism (spleen, stomach, kindey)
    Measurement* spleenM = getMeasurementWith(SPLEEN);
    Measurement* stomachM = getMeasurementWith(STOMACH);
    Measurement* kidneyM = getMeasurementWith(KIDNEY);
    averageValue = (double) ((spleenM->getAvgValue() + stomachM->getAvgValue() + kidneyM->getAvgValue()) / 3);
    healthCategoriesData.push_back(averageValue);
    
    // Psycho-emotional state (heart, liver, heart constrictor)
    Measurement* heartM = getMeasurementWith(HEART);
    Measurement* liverM = getMeasurementWith(LIVER);
    Measurement* constrictorM = getMeasurementWith(HEART_CONSTRICTOR);
    averageValue = (double) ((heartM->getAvgValue() + liverM->getAvgValue() + constrictorM->getAvgValue()) / 3);
    healthCategoriesData.push_back(averageValue);
    
    // Musculoskeletal system (bladder, gallbladder, stomach, liver, triple heater)
    Measurement* bladderM = getMeasurementWith(BLADDER);
    Measurement* gallBladderM = getMeasurementWith(GALLBLADDER);
    Measurement* tripleHeaterM = getMeasurementWith(TRIPLE_HEATER);
    averageValue = (double) ((bladderM->getAvgValue() + gallBladderM->getAvgValue() + stomachM->getAvgValue() + liverM->getAvgValue() + tripleHeaterM->getAvgValue()) / 5);
    healthCategoriesData.push_back(averageValue);
}