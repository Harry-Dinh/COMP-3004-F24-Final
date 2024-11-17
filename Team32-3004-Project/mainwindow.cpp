#include <iostream>
#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "defs.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    // Initialize all member variables
    ui->setupUi(this);
    this->batteryTimer = new QTimer();
    this->batteryPercentage = STARTING_BATTERY_LEVEL;
    
    // Connect the battery timer to the appropriate function
    connect(this->batteryTimer, &QTimer::timeout, this, QOverload<>::of(&MainWindow::drainBattery));
    
    // Connect the power button to its respective function
    connect(ui->powerButton, &QPushButton::clicked, this, &MainWindow::powerButtonPressed);
    
    // Set the initial display value for the battery indicator
    ui->batteryIndicator->display(STARTING_BATTERY_LEVEL);
}

MainWindow::~MainWindow() {
    delete ui;
    delete this->batteryTimer;

    //delete all profiles
    while(!profiles.empty()){
        delete profiles.back();
        profiles.pop_back();
    }
}

void MainWindow::drainBattery() {
    cout << "drainBattery() called" << endl;
    if (batteryPercentage > 0) {
        --batteryPercentage;
        ui->batteryIndicator->display(batteryPercentage);
    } else {
        batteryTimer->stop();       // Stop the timer when the battery level drops to 0
    }
}

void MainWindow::powerButtonPressed() {
    if (!ui->powerButton->isDefault()) {
        ui->powerButton->setDefault(true);
        ui->powerButton->setText("Power Off");
        batteryTimer->start(2000);      // Drain the battery 1% every 2 seconds
    } else {
        ui->powerButton->setDefault(false);
        ui->powerButton->setText("Power On");
        batteryTimer->stop();           // Simulate the action of turning off the device when the power button is pressed again
    }
}

void MainWindow::addProfile(int id, const QString &firstName, const QString &lastName,
                            int weight, int height, const QString &DOB, const QString &country,
                            const QString &phone, const QString &email, const QString &password){

    Profile *p = new Profile(id, firstName, lastName, weight, height, DOB, country, phone, email, password);
    profiles.append(p);
    qInfo() << "profile added";
}

void MainWindow::deleteProfile(int id){
    delete profiles[id];//deallocate profile with id
    profiles.erase(profiles.begin()+id);//delete profile at id;
}
