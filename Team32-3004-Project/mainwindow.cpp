#include <iostream>
#include <QDebug>
#include <QComboBox>
#include <QLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QDateEdit>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "defs.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    // Initialize all member variables
    ui->setupUi(this);
    this->batteryTimer = new QTimer();
    this->batteryPercentage = STARTING_BATTERY_LEVEL;
    this->selectedProfile = -1;
    this->numProfiles = 0;
    
    // Connect the battery timer to the appropriate function
    connect(this->batteryTimer, &QTimer::timeout, this, QOverload<>::of(&MainWindow::drainBattery));
    
    // Connect the power button to its respective function
    connect(ui->powerButton, &QPushButton::clicked, this, &MainWindow::powerButtonPressed);
    
    // Set the initial display value for the battery indicator
    ui->batteryIndicator->display(STARTING_BATTERY_LEVEL);




    connect(ui->backButton, &QPushButton::clicked, this, &MainWindow::backButtonPressed);
    connect(ui->createProfileButton, &QPushButton::clicked, this, &MainWindow::createProfile);

    //create menus

    addMenu("Profile Menu", nullptr, 0);
    connect(ui->addProfileButton, &QPushButton::clicked, this, &MainWindow::createProfilePagePressed);
    connect(ui->deleteProfileButton, &QPushButton::clicked, this, &MainWindow::deleteProfilePressed);
    connect(ui->loginButton, &QPushButton::clicked, this, &MainWindow::loginProfilePressed);

    addMenu("Create Profile", menus[0], 1);
    menus[0]->addSubMenu(menus[1]);


    currMenu = menus[0];

    ui->MenuWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow() {
    delete ui;
    delete this->batteryTimer;

    //delete all profiles
    while(!profiles.empty()){
        delete profiles.back();
        profiles.pop_back();
    }

    //delete all menus
    while(!menus.empty()){
        delete menus.back();
        menus.pop_back();
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

void MainWindow::backButtonPressed(){
    if(currMenu->getParent() != nullptr){
        ui->MenuWidget->setCurrentIndex(currMenu->getParent()->getIndex());
        currMenu = menus[currMenu->getParent()->getIndex()];
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

void MainWindow::addMenu(const QString &name, Menu* parent, int index){
    Menu *m = new Menu(name, parent);
    m->setIndex(index);
    menus.append(m);//add this pointer to the menus list
}

void MainWindow::createProfilePagePressed(){
    qInfo() << "handle profile creation screen";
    ui->MenuWidget->setCurrentIndex(1);
    currMenu = menus[1];
}

void MainWindow::deleteProfilePressed(){
    qInfo() << "handle deleting profile";
}

void MainWindow::loginProfilePressed(){
    qInfo() << "handle moving to app main menu";
}

void MainWindow::createProfile(){
    qInfo() << "Create new profile";

    if(numProfiles < 5){
        QString firstName = ui->fNameTextBox->toPlainText();
        QString lastName = ui->lNameTextBox->toPlainText();
        int weight = ui->weightSpinBox->value();
        int height = ui->heightSpinBox->value();
        QString dob = ui->dobDateEdit->date().toString("dd/MM/yyyy");
        QString country = ui->countryTextBox->toPlainText();
        QString phone = ui->phoneTextBox->toPlainText();
        QString email = ui->emailTextBox->toPlainText();
        QString password = ui->passwordTextBox->toPlainText();//dont store passwords in plaintext
        addProfile(numProfiles,firstName,lastName,weight,height,dob,country,phone,email,password);
        ui->profileComboBox->addItem(firstName);
        numProfiles++;
    }
    //return to profiles page
    ui->MenuWidget->setCurrentIndex(0);
    currMenu = menus[0];

}
