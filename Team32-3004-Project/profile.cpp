#include "profile.h"

Profile::Profile(int id, const QString &firstName, const QString &lastName,
                 int weight, int height, const QString &DOB, const QString &country,
                 const QString &phone, const QString &email, const QString &password){
    this->id = id;
    this->firstName = firstName;
    this->lastName = lastName;
    this->weight = weight;
    this->height = height;
    this->DOB = DOB;
    this->country = country;
    this->phone = phone;
    this->email = email;
    this->password = password;
}


Profile::Profile(const Profile &p){
    this->id = p.id;
    this->firstName = p.firstName;
    this->lastName = p.lastName;
    this->weight = p.weight;
    this->height = p.height;
    this->DOB = p.DOB;
    this->country = p.country;
    this->phone = p.phone;
    this->email = p.email;
    this->password = p.password;
}

Profile::~Profile(){
    //delete all measurements
    while(!measurements.empty()){
        delete measurements.back();
        measurements.pop_back();
    }
}

void Profile::addMeasurement(Measurement *m){
    this->measurements.append(m);
}
