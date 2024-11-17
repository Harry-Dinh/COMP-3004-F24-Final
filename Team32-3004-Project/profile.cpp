#include "profile.h"

Profile::Profile(int id, const QString &firstName, const QString &lastName,
                 int weight, int height, const QDate &DOB, QString &country,
                 QString &phone, QString &email, QString &password){
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
