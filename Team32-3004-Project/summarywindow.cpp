#include <QDebug>
#include <QVBoxLayout>
#include <QPushButton>
#include <QScrollArea>
#include "summarywindow.h"

SummaryWindow::SummaryWindow(Profile* profile, QWidget *parent) : QWidget(parent), ui(new Ui::SummaryWindow) {
    ui->setupUi(this);
    this->profile = profile;

    setWindowTitle("Summary Window");
    ui->userId->setText(profile->getFirstName());

    for(int i=0;i<profile->getNumMeasurements();i++){
        ui->userId->setText("Test");//);
    }

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setGeometry(10, 10, 300, 200);


    QWidget *contentWidget = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(contentWidget);

    for (int i = 1; i <= 100; ++i) {
        QPushButton *button = new QPushButton(QString("Measurement %1").arg(i), contentWidget);
        button->setMinimumSize(200, 50);
        layout->addWidget(button);
        connect(button, &QPushButton::clicked, this, [button]() { button->setText("Test"); });
    }

    contentWidget->setLayout(layout);

    scrollArea->setWidget(contentWidget);
    scrollArea->setWidgetResizable(true);

    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    contentWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

SummaryWindow::~SummaryWindow() {
    delete ui;
}

void SummaryWindow::setUserId() {
    ui->userId->setText(profile->getFirstName());
}
