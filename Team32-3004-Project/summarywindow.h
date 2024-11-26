#ifndef SUMMARYWINDOW_H
#define SUMMARYWINDOW_H

#include <QWidget>
#include "measurement.h"
#include "ui_summarywindow.h"

namespace Ui {
    class SummaryWindow;
}
    
class SummaryWindow : public QWidget {
    Q_OBJECT
        
    public:
        explicit SummaryWindow(Measurement* measurement = nullptr, QWidget *parent = nullptr);
        ~SummaryWindow();
        
    private:
        Ui::SummaryWindow* ui;
        Measurement* measurement;
};

#endif // SUMMARYWINDOW_H
