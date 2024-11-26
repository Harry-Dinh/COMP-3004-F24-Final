#include "summarywindow.h"

SummaryWindow::SummaryWindow(Measurement* measurement, QWidget *parent) : QWidget(parent), ui(new Ui::SummaryWindow) {
    ui->setupUi(this);
    this->measurement = measurement;
    setWindowTitle("Summary Window");
}

SummaryWindow::~SummaryWindow() {
    delete ui;
}