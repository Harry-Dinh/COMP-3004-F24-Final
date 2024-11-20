#include "history.h"

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
    query.exec("CREATE TABLE IF NOT EXISTS measurements(mId integer primary key not null,date text NOT NULL,m_1 integer NOT NULL,m_2 integer NOT NULL,m_3 integer NOT NULL,m_4 integer NOT NULL,m_5 integer NOT NULL,m_6 integer NOT NULL,m_7 integer NOT NULL,m_8 integer NOT NULL,m_9 integer NOT NULL,m_10 integer NOT NULL,m_11 integer NOT NULL,m_12 integer NOT NULL,m_13 integer NOT NULL,m_14 integer NOT NULL,m_15 integer NOT NULL, m_16 integer NOT NULL,m_17 integer NOT NULL,m_18 integer NOT NULL, m_19 integer NOT NULL, m_20 integer NOT NULL, m_21 integer NOT NULL,m_22 integer NOT NULL,m_23 integer NOT NULL,m_24 integer NOT NULL );");

    return raDoTechDB.commit();
}

bool history::addProfile(int pid, const QString& fname, const QString& lname, int weight, int height, const QString& pDOB, const QString& pcountry, const QString& pphone, const QString& pemail, const QString& ppassword){
    raDoTechDB.transaction();
    QSqlQuery query;

    query.prepare("INSERT INTO profiles (id, firstName, lastName, weight, height, DOB, country, phone, email, password) VALUES (:id, :firstName, :lastName, :weight, :height, :DOB, :country, :phone, :email, :password);");
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

bool history::addHealth(int mid, const QDateTime& time, QVector<int> healthData){
    raDoTechDB.transaction();
    QSqlQuery query;

    query.prepare("INSERT INTO measurements (mId, date, m_1, m_2, m_3, m_4, m_5, m_6, m_7, m_8, m_9, m_10, m_11, m_12, m_13, m_14, m_15, m_16, m_17, m_18, m_19, m_20, m_21, m_22, m_23, m_24) VALUES (:mId, :date, :m_1, :m_2, :m_3, :m_4, :m_5, :m_6, :m_7, :m_8, :m_9, :m_10, :m_11, :m_12, :m_13, :m_14, :m_15, :m_16, :m_17, :m_18, :m_19, :m_20, :m_21, :m_22, :m_23, :m_24);");
    query.bindValue(":mId", mid);
    query.bindValue(":date", time.toString("yyyy-MM-dd hh:mm"));
    query.bindValue(":m_1", healthData[0]);
    query.bindValue(":m_2", healthData[1]);
    query.bindValue(":m_3", healthData[2]);
    query.bindValue(":m_4", healthData[3]);
    query.bindValue(":m_5", healthData[4]);
    query.bindValue(":m_6", healthData[5]);
    query.bindValue(":m_7", healthData[6]);
    query.bindValue(":m_8", healthData[7]);
    query.bindValue(":m_9", healthData[8]);
    query.bindValue(":m_10", healthData[9]);
    query.bindValue(":m_11", healthData[10]);
    query.bindValue(":m_12", healthData[11]);
    query.bindValue(":m_13", healthData[12]);
    query.bindValue(":m_14", healthData[13]);
    query.bindValue(":m_15", healthData[14]);
    query.bindValue(":m_16", healthData[15]);
    query.bindValue(":m_17", healthData[16]);
    query.bindValue(":m_18", healthData[17]);
    query.bindValue(":m_19", healthData[18]);
    query.bindValue(":m_20", healthData[19]);
    query.bindValue(":m_21", healthData[20]);
    query.bindValue(":m_22", healthData[21]);
    query.bindValue(":m_23", healthData[22]);
    query.bindValue(":m_24", healthData[23]);

    query.exec();
    return raDoTechDB.commit();
}

void history::getProfile(int id){
    raDoTechDB.transaction();
    QSqlQuery query;
    query.prepare("SELECT * FROM profiles WHERE id=:id");
    query.bindValue(":id", id);
    query.exec();

    if (!raDoTechDB.commit()) {
        qDebug() << "Error: Query failed to execute";
    }
    QDate date = QDate::fromString(query.value(5).toString(), "yyyy-MM-dd");
    if (!date.isValid()) {
        qDebug() << "Error: Invalid date format";
    }
    //return Profile(query.value(0).toInt(), query.value(1).toString(), query.value(2).toString(), query.value(3).toInt(), query.value(4).toInt(), date, query.value(6).toString(), query.value(7).toString(), query.value(8).toString(), query.value(9).toString());

}

QVector<QString> history::getHealth(int id){
    QSqlQuery query;
    QVector<QString> healthHistory;
    raDoTechDB.transaction();

    query.prepare("SELECT * FROM measurements WHERE mId=:mid");
    query.bindValue(":mid", id);
    query.exec();

    while(query.next()){
        int mId;
        mId = query.value(0).toInt();
        QDateTime scanTime = QDateTime::fromString(query.value(1).toString(),"yyyy-MM-dd hh:mm");
        //get all 24 measures below.

        //QVector measures;
        //for(int i=2; i<27; i++){measures.push_back(query.value(i)); }

        //Scan healthScan = Scan(mId, scanTime, measures);
        //healthHistory.push_back(healthScan);
    }

    return healthHistory;
}

