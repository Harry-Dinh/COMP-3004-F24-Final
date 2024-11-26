#ifndef SUMMARYWINDOW_H
#define SUMMARYWINDOW_H

#include <QWidget>
#include "scan.h"
#include "ui_summarywindow.h"

class SummaryWindow : public QWidget {
    Q_OBJECT

public:
    explicit SummaryWindow(Scan* scan, QWidget *parent = nullptr);

private:
    Ui::SummaryWindow ui;
    Scan* scan;
};

#endif // SUMMARYWINDOW_H
