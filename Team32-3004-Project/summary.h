#ifndef SUMMARY_H
#define SUMMARY_H

#include <QObject>
#include "measurement.h"

class Summary : public QObject{
    Q_OBJECT
    public:
        Summary(Measurement* measurement);

        int getUserID() const;
        QString getTimeRecorded();
        int getAmountOfMeasurements();
    private:
        Measurement* measurement;

};

#endif // SUMMARY_H
