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

/// @brief This window provides an alternative way to view the user's measurement information.
class SummaryWindow : public QWidget {
    Q_OBJECT
    
    private:
        Ui::SummaryWindow* ui;
        Profile* profile;
        
    public:
        explicit SummaryWindow(Profile* profile = nullptr, QWidget *parent = nullptr);
        void setUserId();
        ~SummaryWindow();
};



#endif // SUMMARYWINDOW_H
