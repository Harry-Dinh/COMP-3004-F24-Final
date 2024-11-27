#include "summarywindow.h"

SummaryWindow::SummaryWindow(Profile* profile, QWidget *parent) : QWidget(parent), ui(new Ui::SummaryWindow) {
    ui->setupUi(this);
    this->profile = profile;
    setWindowTitle("Summary Window");
}

SummaryWindow::~SummaryWindow() {
    delete ui;
}

void SummaryWindow::setUserId() {
    ui->userId->setText(profile->getFirstName());
}
