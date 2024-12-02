#ifndef HISTORY_H
#define HISTORY_H
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include "profile.h"
#include "measurement.h"

/**
 * @brief A class that is responsible for storing the profile data and measurement data for viewing history and future device login.
 */
class History
{
public:
    static const QString path;
    History();
    ~History();
    /**
     * @brief adds a measurement object to the sqlite database
     * @param measurement the measurement object to be stored in the sqlite database
     * @return
     * true if successfully added measurement to raDoTech.db
     * false if failed to add measurement to raDoTech.db
     */
    bool addHealth(Measurement*& measurement);
    /**
     * @brief adds a profile object to the sqlite database
     * @param pid, fname, lname, weight, height, pDOB, pcountry, pphone, pemail, ppassword
     * @return
     * true if successfully added profile to raDoTech.db
     * false if failed to add profile to raDoTech.db
     */
    bool addProfile(int pid, const QString& fname, const QString& lname, int weight, int height, const QString& pDOB, const QString& pcountry, const QString& pphone, const QString& pemail, const QString& ppassword);
    /**
     * @brief removes a profile object and it's corresponding measurements from the sqlite database
     * @param pid the id of the profile
     * @return
     * true if successfully removed profile + measurements from raDoTech.db
     * false if failed to remove profile + measurements from raDoTech.db
     */
    bool deleteProfile(int pid);//delete profile from DB and all associated measurements
    /**
     * @brief returns a profile that was stored in the database.
     * @param pid the id of the profile
     * @return Profile* if found or nullptr if not found
     */
    Profile* getProfile(int pid); //Profile return when implemented.
    /**
     * @brief return the IDs that exist in the profiles table
     * @return
     * QVector<int> of profile id's
     */
    QVector<int> getAllProfileID();//return the IDs that exist in the table
    /**
     * @brief return the measurements assoiciated with the profile id
     * @param pid the id of the current profile
     * @return
     * QVector<Measurement*> of measurements for current profile
     */
    QVector<Measurement*> getHealth(int mid);
private:
    ///@brief the database
    QSqlDatabase raDoTechDB;
    /**
     * @brief creates database and tables if they don't already exist.
     */
    bool createTables();
};

#endif // HISTORY_H
