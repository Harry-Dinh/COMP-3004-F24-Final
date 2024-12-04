#include <iostream>
#include <QDebug>
#include <QComboBox>
#include <QLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QDateEdit>
#include <QDateTime>
#include <QListWidgetItem>
#include <QVBoxLayout>
#include <QFont>
#include <QWidget>
#include <QScrollArea>
#include <QFormLayout>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_summarywindow.h"
#include "defs.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    // Initialize all member variables
    ui->setupUi(this);
    this->batteryTimer = new QTimer();
    this->chargingTimer = new QTimer();
    this->batteryPercentage = STARTING_BATTERY_LEVEL;
    this->deviceOn = false;
    this->selectedProfile = -1;
    this->numProfiles = 0;
    this->measurePoint = 0;
    this->currMeasurement = nullptr;
    this->summaryWindow = nullptr;

    //setting ui element states
    ui->measurementHistory->setReadOnly(true);

    // Connect the battery timer to the appropriate function
    connect(this->batteryTimer, &QTimer::timeout, this, QOverload<>::of(&MainWindow::drainBattery));
    
    // Connect the charge timer to the appropriate function
    connect(this->chargingTimer, &QTimer::timeout, this, QOverload<>::of(&MainWindow::chargeDevice));
    
    // Connect the power button to its respective function
    connect(ui->powerButton, &QPushButton::clicked, this, &MainWindow::powerButtonPressed);
    
    // Connect the recharge button to its respective function
    connect(ui->rechargeButton, &QPushButton::clicked, this, &MainWindow::rechargeButtonPressed);
    
    // Set the initial display value for the battery indicator
    ui->batteryIndicator->display(STARTING_BATTERY_LEVEL);

    //connect ui navigation buttons
    connect(ui->backButton, &QPushButton::clicked, this, &MainWindow::backButtonPressed);
    connect(ui->createProfileButton, &QPushButton::clicked, this, &MainWindow::createProfile);
    connect(ui->startMeasureButton, &QPushButton::clicked, this, &MainWindow::measureMenuPressed);
    connect(ui->historyButton, &QPushButton::clicked, this, &MainWindow::historyMenuPressed);
    connect(ui->recommendationButton, &QPushButton::clicked, this, &MainWindow::recommendationPageButtonPressed);

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
    
    // Create recommendations menu, index 5
    addMenu("Recommendations", menus[2], 5);

    //create history menu, index 4
    addMenu("History", menus[2], 4);

    changePage(0);

    historydb = new History();

    historydb->addProfile(1, "John", "Doe", 70, 175, "1990-01-01", "USA", "123-456-7890", "john.doe@example.com", "password123");
    loadProfile();
}

MainWindow::~MainWindow() {
    delete ui;
    delete this->batteryTimer;
    delete this->chargingTimer;

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
        ui->powerButton->setDisabled(false);
        --batteryPercentage;
        ui->batteryIndicator->display(batteryPercentage);
    } else {
        batteryTimer->stop();       // Stop the timer when the battery level drops to 0
        deviceOn = false;
        
        // Device ran out of battery
        if (batteryPercentage <= 0) {
            cout << "Battery died while idling" << endl;
            ui->powerButton->setDisabled(true);
            ui->powerButton->setDefault(false);
            ui->powerButton->setText("Power On");
            ui->rechargeButton->setDisabled(false);
        }

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
            
            // Update some UI elements to reflect drained battery level
            ui->measurementHistory->clear();
        }
    }
}

void MainWindow::chargeDevice() {
    cout << "chargeDevice() called" << endl;
    if (batteryPercentage < STARTING_BATTERY_LEVEL) {
        ++batteryPercentage;
        ui->batteryIndicator->display(batteryPercentage);
    } else {
        chargingTimer->stop();
    }
}

void MainWindow::powerButtonPressed() {
    // Prevent the user from turning on the device when the battery died
    if (batteryPercentage <= 0) {
        ui->powerButton->setDisabled(true);
    } else {
        ui->powerButton->setDisabled(false);
    }
    
    if (!ui->powerButton->isDefault()) {
        ui->powerButton->setDefault(true);
        ui->powerButton->setText("Power Off");
        ui->rechargeButton->setDisabled(true);      // Prevent the device from charging when it's on (this is to avoid subtracting then re-adding the same variable)
        deviceOn = true;
        batteryTimer->start(2000);      // Drain the battery 1% every 2 seconds
    } else {
        ui->powerButton->setDefault(false);
        ui->powerButton->setText("Power On");
        ui->rechargeButton->setDisabled(false);
        deviceOn = false;
        batteryTimer->stop();           // Simulate the action of turning off the device when the power button is pressed again
    }
}

void MainWindow::rechargeButtonPressed() {
    if (!ui->rechargeButton->isDefault()) {
        ui->rechargeButton->setDefault(true);
        ui->rechargeButton->setText("Stop Charging");
        ui->powerButton->setDisabled(true);
        if (batteryPercentage == STARTING_BATTERY_LEVEL) {
            ui->chargeStatus->setText("Battery fully charged!");
        } else {
            ui->chargeStatus->setText("Charging...");
        }
        chargingTimer->start(500);    // Charge the battery 1% every 0.5 seconds
    } else {
        ui->rechargeButton->setDefault(false);
        ui->rechargeButton->setText("Recharge");
        ui->powerButton->setDisabled(false);
        ui->chargeStatus->setText("Not charging");
        chargingTimer->stop();
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
    historydb->addProfile(id, firstName, lastName, weight, height, DOB, country, phone, email, password);
    profiles.append(p);
    ui->profileComboBox->addItem(firstName);
}

void MainWindow::addProfile(Profile *p){
    profiles.append(p);
    ui->profileComboBox->addItem(p->getFirstName());
}

void MainWindow::loadProfile(){
    QVector<int> ids = historydb->getAllProfileID();
    for(int i = 0; i < ids.size(); ++i){//begin loading all profiles from the DB
        Profile *p = historydb->getProfile(ids[i]);
        addProfile(p);

        //start loading all measurements associated with this profile
        for(Measurement *m : historydb->getHealth(ids[i])){
            p->addMeasurement(m);
        }
    }
    numProfiles = ids.back()+1;//set the next id
}

void MainWindow::addMenu(const QString &name, Menu* parent, int index){
    Menu *m = new Menu(name, parent);
    m->setIndex(index);
    menus.append(m);//add this pointer to the menus list
}

void MainWindow::createProfilePagePressed(){
    changePage(1);//change page to profile creation page
}

void MainWindow::deleteProfilePressed(){
    //send query to DB to delete the selected profile
    historydb->deleteProfile(profiles[selectedProfile]->getID());

    //erase the selected profile from program and UI
    if(profiles.size() != 0){
        profiles.erase(profiles.begin()+selectedProfile);
        ui->profileComboBox->removeItem(selectedProfile);
    }
}

void MainWindow::loginProfilePressed(){
    if(selectedProfile != -1){//a profile is selected
        changePage(2);
    }
}

void MainWindow::createProfile(){
    //take in user input from the ui fields

    if(numProfiles < MAXPROFILES){
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
        numProfiles++;
    }
    //return to profiles page
    changePage(0);

}

void MainWindow::measureMenuPressed(){
    changePage(3);
    beginMeasurement = true;

    //start taking measurements
    QDateTime date = QDateTime::currentDateTime();
    Measurement *m = new Measurement(profiles[selectedProfile]->getID(), date);
    currMeasurement = m;
    ui->measurePointLabel->setText("Measure point: 1");
}

void MainWindow::historyMenuPressed(){
    changePage(5);
    //clear the history
    ui->historyTab->clear();

    //begin creating tabs for each measurement
    for(Measurement* m: profiles[selectedProfile]->getAllMeasurements()){
        //create widget and layout
        QWidget* measurementWidget = new QWidget();
        QFormLayout* layout = new QFormLayout();
        measurementWidget->setLayout(layout);

        for(int i = 0; i < m->getValues().size(); ++i){//add measurement labels to the widget
            double currentValue = m->getValue(i);
            QString interpretation = QString::fromUtf8(m->interpretValue(currentValue).c_str());
            QLabel* label = new QLabel("Point " + QString::number(i+1) + " Value: " +QString::number(currentValue) + " (" + interpretation + ")");
            layout->addWidget(label);
        }

        //add tab with the date of measurement as its header
        ui->historyTab->addTab(measurementWidget,m->getTimeRecorded());
    }
}

void MainWindow::on_profileComboBox_currentIndexChanged(int index){
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

        //update measurement label
        ui->measurePointLabel->setText("Measure point: "+ QString::number(measurePoint+2));
        currMeasurement->generateValue();
        ui->measurementHistory->append("Point: " + QString::number(measurePoint+1) + " Value: " + QString::number(currMeasurement->getValue(measurePoint)));
        measurePoint++;//move onto next point

    }

    if(measurePoint == 24){//finished measuring
        profiles[selectedProfile]->addMeasurement(currMeasurement);
        historydb->addHealth(currMeasurement);

        beginMeasurement = false;
        currMeasurement = nullptr;
        measurePoint = 0;
        ui->measurePointLabel->setText("Measuring complete");


    }
}

void MainWindow::on_summaryButton_clicked()
{
    qInfo() << "showing summary";
    qInfo() << this->selectedProfile;
    if (summaryWindow == nullptr) {
        summaryWindow = new SummaryWindow(profiles[selectedProfile]);
    }
    else{
        delete summaryWindow;
        summaryWindow = new SummaryWindow(profiles[selectedProfile]);
    }
    summaryWindow->show();
}

void MainWindow::recommendationPageButtonPressed() {
    changePage(4);
}
