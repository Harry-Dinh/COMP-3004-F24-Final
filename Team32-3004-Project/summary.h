#ifndef SUMMARY_H
#define SUMMARY_H

#include <QObject>
#include "scan.h"

class Summary : public QObject{
    Q_OBJECT
    public:
        Summary(Scan* scan);

        int getUserID() const;
        QString& getTimeRecorded();
        int getAmountOfMeasurements();
        double getBaseline();
    private:
        Scan* scan;

};

#endif // SUMMARY_H
