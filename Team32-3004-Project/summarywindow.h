#ifndef SUMMARYWINDOW_H
#define SUMMARYWINDOW_H

#include <QWidget>
#include <QDebug>
#include <QLabel>
#include "profile.h"
#include "ui_summarywindow.h"

namespace Ui {
    class SummaryWindow;
}
    
class SummaryWindow : public QWidget {
    Q_OBJECT
        
    public:
        explicit SummaryWindow(Profile* profile = nullptr, QWidget *parent = nullptr);
        void setUserId();
        ~SummaryWindow();
        
    private:
        Ui::SummaryWindow* ui;
        Profile* profile;
};



#endif // SUMMARYWINDOW_H
