#include "summarywindow.h"

SummaryWindow::SummaryWindow(Scan* scan, QWidget *parent) : QWidget(parent), scan(scan) {
    ui.setupUi(this);
    setWindowTitle("Summary Window");
}
