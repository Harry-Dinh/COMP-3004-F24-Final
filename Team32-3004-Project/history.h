#ifndef HISTORY_H
#define HISTORY_H
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include "profile.h"

//db class for project, will keep historical health data for each profile, to access for trend analysis.
//vision for db
// | key - id/name | time | point1 | point2 | ... | point24 |
// use id/name to retrieve and store each user's data.
class history
{
public:
    static const QString path;
    history();
    ~history();
    bool addHealth(int mid, const QDateTime& time, QVector<int> healthData);
    bool addProfile(int pid, const QString& fname, const QString& lname, int weight, int height, const QString& pDOB, const QString& pcountry, const QString& pphone, const QString& pemail, const QString& ppassword);
    void getProfile(int pid); //Profile return when implemented.
    QVector<QString> getHealth(int mid); //placeholder QString can be swapped for Harry's class.
private:
    QSqlDatabase raDoTechDB;
    bool createTables();
};

#endif // HISTORY_H
