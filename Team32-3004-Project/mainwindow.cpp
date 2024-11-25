#include <iostream>
#include <QDebug>
#include <QComboBox>
#include <QLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QDateEdit>
#include <QDateTime>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "defs.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    // Initialize all member variables
    ui->setupUi(this);
    this->batteryTimer = new QTimer();
    this->batteryPercentage = STARTING_BATTERY_LEVEL;
    this->deviceOn = false;
    this->selectedProfile = -1;
    this->numProfiles = 0;
    this->measurePoint = 0;
    this->currMeasurement = nullptr;

    //setting ui element states
    ui->measurementHistory->setReadOnly(true);


    // Connect the battery timer to the appropriate function
    connect(this->batteryTimer, &QTimer::timeout, this, QOverload<>::of(&MainWindow::drainBattery));
    
    // Connect the power button to its respective function
    connect(ui->powerButton, &QPushButton::clicked, this, &MainWindow::powerButtonPressed);
    
    // Set the initial display value for the battery indicator
    ui->batteryIndicator->display(STARTING_BATTERY_LEVEL);

    //connect ui navigation buttons
    connect(ui->backButton, &QPushButton::clicked, this, &MainWindow::backButtonPressed);
    connect(ui->createProfileButton, &QPushButton::clicked, this, &MainWindow::createProfile);
    connect(ui->startMeasureButton, &QPushButton::clicked, this, &MainWindow::measureMenuPressed);
    connect(ui->historyButton, &QPushButton::clicked, this, &MainWindow::historyMenuPressed);

    connect(ui->probeButton, &QPushButton::clicked, this, &MainWindow::probePressed);

    //create profile menu, index 0
    addMenu("Profile Menu", nullptr, 0);
    connect(ui->addProfileButton, &QPushButton::clicked, this, &MainWindow::createProfilePagePressed);
    connect(ui->deleteProfileButton, &QPushButton::clicked, this, &MainWindow::deleteProfilePressed);
    connect(ui->loginButton, &QPushButton::clicked, this, &MainWindow::loginProfilePressed);

    //create profile creation menu, index 1
    addMenu("Create Profile", menus[0], 1);

    //create main menu, index 2
    addMenu("Main Menu", menus[0], 2);

    //create measurement menu, index 3
    addMenu("Measure", menus[2], 3);

    //create history menu, index 4
    addMenu("History", menus[2], 4);

    changePage(0);

    historydb = new history();
//     historydb->addProfile(1, "John", "Doe", 70, 175, "1990-01-01", "USA", "123-456-7890", "john.doe@example.com", "password123");
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
    delete historydb;
}

void MainWindow::drainBattery() {
    cout << "drainBattery() called" << endl;
    if (batteryPercentage > 0) {
        --batteryPercentage;
        ui->batteryIndicator->display(batteryPercentage);
    } else {
        batteryTimer->stop();       // Stop the timer when the battery level drops to 0
        deviceOn = false;

        //device battery ran out before finishing measurement
        if((batteryPercentage == 0 && beginMeasurement == true)){
            //delete measurement and reset measurement state
            qInfo() << "Battery died, ending measurement";
            if(currMeasurement != nullptr){
                delete currMeasurement;
            }
            beginMeasurement = false;
            currMeasurement = nullptr;
            measurePoint = 0;
            ui->measurementHistory->clear();
        }
    }
}

void MainWindow::powerButtonPressed() {
    if (!ui->powerButton->isDefault()) {
        ui->powerButton->setDefault(true);
        ui->powerButton->setText("Power Off");
        deviceOn = true;
        batteryTimer->start(2000);      // Drain the battery 1% every 2 seconds
    } else {
        ui->powerButton->setDefault(false);
        ui->powerButton->setText("Power On");
        batteryTimer->stop();           // Simulate the action of turning off the device when the power button is pressed again
    }
}

void MainWindow::backButtonPressed(){
    if(currMenu->getParent() != nullptr){
        if(currMenu->getIndex() == 3 ){//exit measurement menu
            qInfo() << "Exiting measurement";
            ui->measurementHistory->clear();


            if(beginMeasurement){//exited an ongoing measurement
                //delete measurement and reset measurement state

                if(currMeasurement != nullptr){
                    qInfo() << "Deleting this incomplete measurement";
                    delete currMeasurement;
                }
                beginMeasurement = false;
                currMeasurement = nullptr;
                measurePoint = 0;
            }
        }
        changePage(currMenu->getParent()->getIndex());
    }
}

void MainWindow::addProfile(int id, const QString &firstName, const QString &lastName,
                            int weight, int height, const QString &DOB, const QString &country,
                            const QString &phone, const QString &email, const QString &password){

    Profile *p = new Profile(id, firstName, lastName, weight, height, DOB, country, phone, email, password);
    profiles.append(p);
    qInfo() << "profile added";
}

void MainWindow::loadProfile(){
//    for(int i = 0; i < numProfiles; ++i){
//        addProfile(historydb->getProfile(i));
//    }
}

void MainWindow::deleteProfile(int id){
    delete profiles[id];//deallocate profile with id
    profiles.erase(profiles.begin()+id);//delete profile at id;
}

void MainWindow::addMenu(const QString &name, Menu* parent, int index){
    Menu *m = new Menu(name, parent);
    m->setIndex(index);
    menus.append(m);//add this pointer to the menus list
    if(parent != nullptr){
        parent->addSubMenu(m);
    }
}

void MainWindow::createProfilePagePressed(){
    qInfo() << "handle profile creation screen";
    changePage(1);
}

void MainWindow::deleteProfilePressed(){
    qInfo() << "handle deleting profile " << selectedProfile;
    if(profiles.size() != 0){
        profiles.erase(profiles.begin()+selectedProfile);
        ui->profileComboBox->removeItem(selectedProfile);
    }
}

void MainWindow::loginProfilePressed(){
    qInfo() << "handle moving to app main menu";
    if(selectedProfile != -1){//a profile is selected
        changePage(2);
    }
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
    changePage(0);

}

void MainWindow::measureMenuPressed(){
    changePage(3);
    beginMeasurement = true;

    QDateTime date = QDateTime::currentDateTime();
    Measurement *m = new Measurement(selectedProfile, date);
    qInfo() << "Created new Measurement object";
    currMeasurement = m;
    ui->measurePointLabel->setText("Measure point: 1");
}

void MainWindow::historyMenuPressed(){
    changePage(4);
}

void MainWindow::on_profileComboBox_currentIndexChanged(int index){
    qInfo() << "selected profile " << index;
    this->selectedProfile = index;
}

void MainWindow::changePage(int index){
    ui->MenuWidget->setCurrentIndex(index);
    currMenu = menus[index];
    ui->pageTitle->setText(menus[index]->getName());
}

void MainWindow::probePressed(){
    //make measurements if in the measurement window
    if(beginMeasurement == true && deviceOn){
        qInfo() << "measuring point " << measurePoint;

        //update measurement label
        ui->measurePointLabel->setText("Measure point: "+ QString::number(measurePoint+2));
        currMeasurement->generateValue();
        ui->measurementHistory->append("Point: " + QString::number(measurePoint+1) + " Value: " + QString::number(currMeasurement->getValue(measurePoint)));
        measurePoint++;//move onto next point

    }

    if(measurePoint == 24){//finished measuring
        qInfo() << "Add measurement to this profile";
        profiles[selectedProfile]->addMeasurement(currMeasurement);
        beginMeasurement = false;
        currMeasurement = nullptr;
        measurePoint = 0;
        ui->measurePointLabel->setText("Measuring complete");
    }
}

void MainWindow::loadHistory(){
    /*
    //get history data associated with selectedID
    for(int i = 0; i < vector.size(); ++i){
        QWidget* hInfo = new QWidget();//widget for historical info
        //add labels and other things to represent the data in UI



        ui->tabWidget->addTab(hInfo,"history" + QString::number(1));
    }

    */
}
