#include <QDebug>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QScrollArea>
#include "summarywindow.h"
#include "measurement.h"

SummaryWindow::SummaryWindow(Profile* profile, QWidget *parent) : QWidget(parent), ui(new Ui::SummaryWindow) {
    ui->setupUi(this);
    this->profile = profile;

    setWindowTitle("Summary Window");
    ui->userId->setText(profile->getFirstName());

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setGeometry(10, 75, 300, 350);

    // Setting up the first summary window (i.e. the window that has the user's name and list of past measurements)
    QWidget *contentWidget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(contentWidget);

    for (int i = 0; i < profile->getAllMeasurements().size(); ++i) {
        QPushButton *button = new QPushButton(QString(), contentWidget);
        button->setMinimumSize(200, 50);
        button->setText(profile->getMeasurement(i)->getTimeRecorded());
        layout->addWidget(button);
        connect(button, &QPushButton::clicked, this, [profile, i]() {
            //QDateTime currentDateTime = QDateTime::currentDateTime();
            //QVector<double> meridianValues = {1.2, 3.4, 5.6, 7.8, 1.2, 3.4, 5.6, 7.8, 1.2, 3.4, 5.6, 7.8, 1.2, 3.4, 5.6, 7.8, 1.2, 3.4, 5.6, 7.8, 1.2, 3.4, 5.6, 7.8, 1.2, 3.4, 5.6, 7.8, 1.2, 3.4, 5.6, 7.8, 1.2, 3.4, 5.6, 7.8, 1.2, 3.4, 5.6, 7.8, 1.2, 3.4, 5.6, 7.8};
            Measurement* measurement = profile->getMeasurement(i); // new Measurement(123, currentDateTime, meridianValues);
            QVector<double> meridianValues = measurement->getValues();

            QWidget *measurementWidget = new QWidget();
            QVBoxLayout *measurementLayout = new QVBoxLayout(measurementWidget);

            QLabel *profileLabel = new QLabel();
            profileLabel->setText(profile->getFirstName());
            profileLabel->setMinimumSize(200, 50);
            measurementLayout->addWidget(profileLabel);

            QLabel *timeStamp = new QLabel();
            timeStamp->setText(measurement->getTimeRecorded());
            timeStamp->setMinimumSize(200, 50);
            measurementLayout->addWidget(timeStamp);
            
            // Setting up the labels in the individual measurement window
            for (std::size_t index = 0; index < meridianValues.size(); ++index) {
                QLabel *label = new QLabel();
                QString valueInterpretation = QString::fromUtf8(measurement->interpretValue(measurement->getValue(index)).c_str());
                label->setText(QString("Measurement %1: %2 (%3)").arg(index).arg(meridianValues[index]).arg(valueInterpretation));
                label->setMinimumSize(350, 25);
                measurementLayout->addWidget(label);
            }
            
            // Scroll area for the individual measurement window
            QScrollArea *scrollArea = new QScrollArea();
            scrollArea->setWidget(measurementWidget);
            scrollArea->setWidgetResizable(true);
            measurementWidget->setParent(scrollArea);

            scrollArea->show();
        });

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
