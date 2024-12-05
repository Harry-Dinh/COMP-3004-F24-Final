#ifndef PROFILE_H
#define PROFILE_H

#include <QObject>
#include <QString>
#include <QDate>
#include <QVector>
#include "measurement.h"

class Profile {
    private:
        int id;//user's id
        QString firstName;//stores first name of user
        QString lastName;//stores last name of user
        int weight;//stores weight of user in kg
        int height;//stores height of user in cm
        QString DOB;//stores user's date of birth
        QString country;//stores user's country
        QString phone;//stores user's phone number
        QString email;//stores user's email
        QString password;//stores user's password
        QVector<Measurement*> measurements;//stores measurements
    
    public:
        Profile(int id, const QString &firstName, const QString &lastName,
                int weight, int height, const QString &DOB, const QString &country,
                const QString &phone, const QString &email, const QString &password);
        Profile(const Profile &p);
        ~Profile();

        void addMeasurement(Measurement *m);//add Measurement to the end of this profile's measurements vector
        int getNumMeasurements();//returns the number of measurements this profile has stored
        int getID();//returns the ID
        QString getFirstName();//returns the profile's first name
        Measurement* getMeasurement(int index);//returns a measurement at a certain index
        QVector<Measurement*> getAllMeasurements();//returns a QVector of Measurement*
};

#endif // PROFILE_H
