#include "history.h"
#include "defs.h"
const QString history::path = "radotech.db";

history::history()
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

history::~history()
{
    if (raDoTechDB.isOpen()){
        raDoTechDB.close();
        qDebug() << "Database: is closed.";
    }
}

bool history::createTables(){

    raDoTechDB.transaction();
    QSqlQuery query;

    //Make profile table
    query.exec("CREATE TABLE IF NOT EXISTS profiles(id integer primary key not null, firstName text NOT NULL, lastName text NOT NULL, weight integer NOT NULL, height integer NOT NULL,DOB text NOT NULL, country text NOT NULL, phone text NOT NULL, email text NOT NULL, password text NOT NULL, FOREIGN KEY(id) REFERENCES measurements(mId));");

    //Make data table
    query.exec("CREATE TABLE IF NOT EXISTS measurements(mId integer not null,date text NOT NULL,m_1 REAL NOT NULL,m_2 REAL NOT NULL,m_3 REAL NOT NULL,m_4 REAL NOT NULL,m_5 REAL NOT NULL,m_6 REAL NOT NULL,m_7 REAL NOT NULL,m_8 REAL NOT NULL,m_9 REAL NOT NULL,m_10 REAL NOT NULL,m_11 REAL NOT NULL,m_12 REAL NOT NULL,m_13 REAL NOT NULL,m_14 REAL NOT NULL,m_15 REAL NOT NULL, m_16 REAL NOT NULL,m_17 REAL NOT NULL,m_18 REAL NOT NULL, m_19 REAL NOT NULL, m_20 REAL NOT NULL, m_21 REAL NOT NULL,m_22 REAL NOT NULL,m_23 REAL NOT NULL,m_24 REAL NOT NULL );");

    return raDoTechDB.commit();
}

bool history::addProfile(int pid, const QString& fname, const QString& lname, int weight, int height, const QString& pDOB, const QString& pcountry, const QString& pphone, const QString& pemail, const QString& ppassword){
    raDoTechDB.transaction();
    QSqlQuery query;

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

bool history::deleteProfile(int pid){
    raDoTechDB.transaction();
    QSqlQuery query;
    //delete profile with this id
    query.prepare("DELETE FROM profiles WHERE id=?");
    query.addBindValue(pid);
    query.exec();

//    //delete all measurements associated with this id
    query.prepare("DELETE FROM measurements WHERE mId=?");
    query.addBindValue(pid);
    query.exec();
    return raDoTechDB.commit();
}

bool history::addHealth(Measurement*& measurement){
    raDoTechDB.transaction();
    vector<double>& measures = measurement->getValues(); //get list of measures from scan

    QSqlQuery query;
    //store left and right values from measures
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

Profile* history::getProfile(int id){
    raDoTechDB.transaction();
    QSqlQuery query;
    query.prepare("SELECT * FROM profiles WHERE id=:id");
    query.bindValue(":id", id);
    query.exec();

    if (!raDoTechDB.commit()) {
        qDebug() << "Error: Query failed to execute";
    }
    //QDate date = QDate::fromString(query.value(5).toString(), "yyyy-MM-dd");
    //if (!date.isValid()) {
    //    qDebug() << "Error: Invalid date format";
    //}
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

QVector<int> history::getAllProfileID(){
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

QVector<Measurement*> history::getHealth(int id){
    QSqlQuery query;
    QVector<Measurement*> healthHistory; //double check this one and how we are passign it.
    raDoTechDB.transaction();

    query.prepare("SELECT * FROM measurements WHERE mId=:mid");
    query.bindValue(":mid", id);
    query.exec();

    while(query.next()){ // go through each entry and add a scan object for each.
        QDateTime scanTime = QDateTime::fromString(query.value(1).toString(),"yyyy-MM-dd hh:mm");
        Measurement *scan = new Measurement(query.value(0).toInt(), scanTime); //scan object


        /*
        Measurement m1 = Measurement(intToMeridian(1), query.value(2).toDouble(), query.value(3).toDouble());
        Measurement m2 = Measurement(intToMeridian(2), query.value(4).toDouble(), query.value(5).toDouble());
        Measurement m3 = Measurement(intToMeridian(3), query.value(6).toDouble(), query.value(7).toDouble());
        Measurement m4 = Measurement(intToMeridian(4), query.value(8).toDouble(), query.value(9).toDouble());
        Measurement m5 = Measurement(intToMeridian(5), query.value(10).toDouble(), query.value(11).toDouble());
        Measurement m6 = Measurement(intToMeridian(6), query.value(12).toDouble(), query.value(13).toDouble());
        Measurement m7 = Measurement(intToMeridian(7), query.value(14).toDouble(), query.value(15).toDouble());
        Measurement m8 = Measurement(intToMeridian(8), query.value(16).toDouble(), query.value(17).toDouble());
        Measurement m9 = Measurement(intToMeridian(9), query.value(18).toDouble(), query.value(19).toDouble());
        Measurement m10 = Measurement(intToMeridian(10), query.value(20).toDouble(), query.value(21).toDouble());
        Measurement m11 = Measurement(intToMeridian(11), query.value(22).toDouble(), query.value(23).toDouble());
        Measurement m12 = Measurement(intToMeridian(12), query.value(24).toDouble(), query.value(25).toDouble());
        */


        for(int i = 2; i<26; i++){ // assign values to measurements and add them to the scan object
            scan->addExistingValue(query.value(i).toDouble());
        }

        healthHistory.push_back( scan );//add scan object to vector.
    }

    return healthHistory;
}

