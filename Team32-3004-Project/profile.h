#ifndef PROFILE_H
#define PROFILE_H

#include <QObject>
#include <QString>
#include <QDate>
#include <QVector>

class Profile : public QObject{
    Q_OBJECT
    public:
        Profile(int id, const QString &firstName, const QString &lastName, int weight, int height, const QDate &DOB,const QString &country,const QString &phone,const QString &email,const QString &password);
    private:
        int id;//user's id
        QString firstName;//stores first name of user
        QString lastName;//stores last name of user
        int weight;//stores weight of user in kg
        int height;//stores height of user in cm
        QDate DOB;//stores user's date of birth
        QString country;//stores user's country
        QString phone;//stores user's phone number
        QString email;//stores user's email
        QString password;//stores user's password
//        QVector<> historicalData;//stores historical data
    signals:

};

#endif // PROFILE_H
