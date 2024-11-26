#ifndef SUMMARY_H
#define SUMMARY_H

#include <QObject>
#include "Measurement.h"

class Summary : public QObject{
    Q_OBJECT
    public:
        Summary(Measurement* scan);

        int getUserID() const;
        QString getTimeRecorded();
        int getAmountOfMeasurements();
    private:
        Measurement* scan;

};

#endif // SUMMARY_H
