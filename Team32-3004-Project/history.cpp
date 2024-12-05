#include "history.h"
#include "defs.h"
const QString History::path = "radotech.db";

History::History()
{
    raDoTechDB = QSqlDatabase::addDatabase("QSQLITE");
    raDoTechDB.setDatabaseName(path);

    if (!raDoTechDB.open()) {
        qDebug() << "Error: connection with database fail";
    } else {
        qDebug() << "Database: connection ok";
    }

    if (!createTables()) {
        qDebug() << "Error: Couldn't create tables";
    }
}

History::~History()
{
    if (raDoTechDB.isOpen()){
        raDoTechDB.close();
        qDebug() << "Database: is closed.";
    }
}

bool History::createTables(){

    raDoTechDB.transaction();
    QSqlQuery query;

    //Make profile table
    query.exec("CREATE TABLE IF NOT EXISTS profiles(id integer primary key not null, firstName text NOT NULL, lastName text NOT NULL, weight integer NOT NULL, height integer NOT NULL,DOB text NOT NULL, country text NOT NULL, phone text NOT NULL, email text NOT NULL, password text NOT NULL, FOREIGN KEY(id) REFERENCES measurements(mId));");

    //Make data table
    query.exec("CREATE TABLE IF NOT EXISTS measurements(mId integer not null,date text NOT NULL,m_1 REAL NOT NULL,m_2 REAL NOT NULL,m_3 REAL NOT NULL,m_4 REAL NOT NULL,m_5 REAL NOT NULL,m_6 REAL NOT NULL,m_7 REAL NOT NULL,m_8 REAL NOT NULL,m_9 REAL NOT NULL,m_10 REAL NOT NULL,m_11 REAL NOT NULL,m_12 REAL NOT NULL,m_13 REAL NOT NULL,m_14 REAL NOT NULL,m_15 REAL NOT NULL, m_16 REAL NOT NULL,m_17 REAL NOT NULL,m_18 REAL NOT NULL, m_19 REAL NOT NULL, m_20 REAL NOT NULL, m_21 REAL NOT NULL,m_22 REAL NOT NULL,m_23 REAL NOT NULL,m_24 REAL NOT NULL );");

    return raDoTechDB.commit();
}

bool History::addProfile(int pid, const QString& fname, const QString& lname, int weight, int height, const QString& pDOB, const QString& pcountry, const QString& pphone, const QString& pemail, const QString& ppassword){
    raDoTechDB.transaction();
    QSqlQuery query;
    //take data from profile object and insert into database
    query.prepare("INSERT OR IGNORE INTO profiles (id, firstName, lastName, weight, height, DOB, country, phone, email, password) VALUES (:id, :firstName, :lastName, :weight, :height, :DOB, :country, :phone, :email, :password);");
    query.bindValue(":id", pid);
    query.bindValue(":firstName", fname);
    query.bindValue(":lastName", lname);
    query.bindValue(":weight", weight);
    query.bindValue(":height", height);
    query.bindValue(":DOB", pDOB);
    query.bindValue(":country", pcountry);
    query.bindValue(":phone", pphone);
    query.bindValue(":email", pemail);
    query.bindValue(":password", ppassword);

    query.exec();

    return raDoTechDB.commit();
}

bool History::deleteProfile(int pid){
    raDoTechDB.transaction();
    QSqlQuery query;
    //delete profile with this id
    query.prepare("DELETE FROM profiles WHERE id=?");
    query.addBindValue(pid);
    query.exec();

    //delete all measurements associated with this id
    query.prepare("DELETE FROM measurements WHERE mId=?");
    query.addBindValue(pid);
    query.exec();
    return raDoTechDB.commit();
}

bool History::addHealth(Measurement*& measurement){
    raDoTechDB.transaction();
    QVector<double> measures = measurement->getValues(); //get list of measures from scan

    QSqlQuery query;
    //store all data included in a measurement, ie. userid, time of measurement, and 24 data points from electric current.
    query.prepare("INSERT INTO measurements (mId, date, m_1, m_2, m_3, m_4, m_5, m_6, m_7, m_8, m_9, m_10, m_11, m_12, m_13, m_14, m_15, m_16, m_17, m_18, m_19, m_20, m_21, m_22, m_23, m_24) VALUES (:mId, :date, :m_1, :m_2, :m_3, :m_4, :m_5, :m_6, :m_7, :m_8, :m_9, :m_10, :m_11, :m_12, :m_13, :m_14, :m_15, :m_16, :m_17, :m_18, :m_19, :m_20, :m_21, :m_22, :m_23, :m_24);");
    query.bindValue(":mId", measurement->getUserID());
    query.bindValue(":date", measurement->getTimeRecorded());
    query.bindValue(":m_1", measures[0]);
    query.bindValue(":m_2", measures[1]);
    query.bindValue(":m_3", measures[2]);
    query.bindValue(":m_4", measures[3]);
    query.bindValue(":m_5", measures[4]);
    query.bindValue(":m_6", measures[5]);
    query.bindValue(":m_7", measures[6]);
    query.bindValue(":m_8", measures[7]);
    query.bindValue(":m_9", measures[8]);
    query.bindValue(":m_10", measures[9]);
    query.bindValue(":m_11", measures[10]);
    query.bindValue(":m_12", measures[11]);
    query.bindValue(":m_13", measures[12]);
    query.bindValue(":m_14", measures[13]);
    query.bindValue(":m_15", measures[14]);
    query.bindValue(":m_16", measures[15]);
    query.bindValue(":m_17", measures[16]);
    query.bindValue(":m_18", measures[17]);
    query.bindValue(":m_19", measures[18]);
    query.bindValue(":m_20", measures[19]);
    query.bindValue(":m_21", measures[20]);
    query.bindValue(":m_22", measures[21]);
    query.bindValue(":m_23", measures[22]);
    query.bindValue(":m_24", measures[23]);

    query.exec();
    if(raDoTechDB.commit()){
        qDebug() << "Measurement added";
        return true;
    }else{
        qDebug() << "Measurement added";
        return false;
    }
}
//Finds profile in database based on it's id.
Profile* History::getProfile(int id){
    raDoTechDB.transaction();
    QSqlQuery query;
    query.prepare("SELECT * FROM profiles WHERE id=:id");
    query.bindValue(":id", id);
    query.exec();

    if (!raDoTechDB.commit()) {
        qDebug() << "Error: Query failed to execute";
    }

    int profileId = -1;
    QString fName;
    QString lName;
    int weight = -1;
    int height = -1;
    QString DOB;
    QString country;
    QString phone;
    QString email;
    QString password;
    while (query.next()){
        profileId = query.value(0).toInt();
        fName = query.value(1).toString();
        lName = query.value(2).toString();
        weight = query.value(3).toInt();
        height = query.value(4).toInt();
        DOB = query.value(5).toString();
        country = query.value(6).toString();
        phone = query.value(7).toString();
        email = query.value(8).toString();
        password = query.value(9).toString();
    }

    Profile *p = new Profile(profileId,fName,lName,weight,height,DOB,country,phone,email,password);
    return p;
}

QVector<int> History::getAllProfileID(){
    raDoTechDB.transaction();
    QSqlQuery query;
    QVector<int> ids;
    query.prepare("SELECT id FROM profiles");
    query.exec();
    while(query.next()){
        ids.push_back(query.value(0).toInt());
    }
    return ids;
}

QVector<Measurement*> History::getHealth(int id){
    QSqlQuery query;
    QVector<Measurement*> healthHistory;
    raDoTechDB.transaction();
    //query database for all measurements that shares user id.
    query.prepare("SELECT * FROM measurements WHERE mId=:mid");
    query.bindValue(":mid", id);
    query.exec();

    while(query.next()){ // go through each entry and add a measurement object for each.
        QDateTime scanTime = QDateTime::fromString(query.value(1).toString());
        Measurement *scan = new Measurement(query.value(0).toInt(), scanTime); //measurement object

        for(int i = 2; i<26; i++){ // assign values to measurements and add them to the scan object
            scan->addValue(query.value(i).toDouble());
        }

        healthHistory.push_back( scan );//add measurement object to vector.
    }

    return healthHistory;
}

