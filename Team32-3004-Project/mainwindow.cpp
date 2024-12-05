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
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_summarywindow.h"
#include "defs.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    // Initialize all member variables
    ui->setupUi(this);
    device = new Device();
    device->show();

    this->selectedProfile = -1;
    this->numProfiles = 0;
    this->measurePoint = 0;
    this->currMeasurement = nullptr;
    this->summaryWindow = nullptr;
    this->beginMeasurement = false;

    //setting ui element states
    ui->measurementHistory->setReadOnly(true);

    // Connect measurementInterrupt signal to its handler function
    connect(this, &MainWindow::measurementInterrupted, this, &MainWindow::handleMeasureInterrupt);
    

    //connect ui navigation buttons
    connect(ui->backButton, &QPushButton::clicked, this, &MainWindow::backButtonPressed);
    connect(ui->createProfileButton, &QPushButton::clicked, this, &MainWindow::createProfile);
    connect(ui->startMeasureButton, &QPushButton::clicked, this, &MainWindow::measureMenuPressed);
    connect(ui->historyButton, &QPushButton::clicked, this, &MainWindow::historyMenuPressed);
    connect(ui->recommendationButton, &QPushButton::clicked, this, &MainWindow::recommendationPageButtonPressed);
    connect(ui->showDeviceButton, &QPushButton::clicked, this, &MainWindow::showDeviceButtonPressed);

    //connect Device to MainWindow
    connect(device, &Device::sendMeasurement, this, &MainWindow::handleProbePressed);
    connect(device, &Device::measurementInterrupted, this, &MainWindow::handleMeasureInterrupt);

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

void MainWindow::backButtonPressed(){
    if(currMenu->getParent() != nullptr){
        if(currMenu->getIndex() == 3 ){//exit measurement menu
            qInfo() << "Exiting measurement";
            ui->measurementHistory->clear();

            if(beginMeasurement){//exited an ongoing measurement
                emit(measurementInterrupted());
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
    ui->fNameTextBox->setText("");
    ui->lNameTextBox->setText("");
    ui->weightSpinBox->setValue(0);
    ui->heightSpinBox->setValue(0);
    QDate defaultDate;
    defaultDate.setDate(2000,1,1);
    ui->dobDateEdit->setDate(defaultDate);
    ui->countryTextBox->setText("");
    ui->emailTextBox->setText("");
    ui->passwordTextBox->setText("");
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
    //ensure that the user has entered info in all fields
    if(ui->fNameTextBox->document()->isEmpty() ||
       ui->lNameTextBox->document()->isEmpty() ||
       ui->countryTextBox->document()->isEmpty() ||
       ui->phoneTextBox->document()->isEmpty() ||
       ui->emailTextBox->document()->isEmpty() ||
       ui->passwordTextBox->document()->isEmpty()){

        QMessageBox msgBox;
        msgBox.setText("Please enter info in empty fields");
        msgBox.exec();
        return;
    }

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

void MainWindow::handleProbePressed(double value){
    //make measurements if in the measurement window

    if(beginMeasurement == true){

        //update measurement label
        ui->measurePointLabel->setText("Measure point: "+ QString::number(measurePoint+2));
        currMeasurement->addValue(value);
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

void MainWindow::handleMeasureInterrupt(){
    //display text in the measurement page
    ui->measurePointLabel->setText("Device Disconnected, ensure it is on and retry");
    //clear the measurement list
    ui->measurementHistory->clear();

    //delete measurement and reset measurement state
    if(currMeasurement != nullptr){
        qInfo() << "Deleting this incomplete measurement";
        delete currMeasurement;
    }
    beginMeasurement = false;
    currMeasurement = nullptr;
    measurePoint = 0;
}

void MainWindow::showDeviceButtonPressed() {
    if (device == nullptr) {
        device = new Device(this);
    }
    
    if (device->isMinimized()) device->showNormal();
    device->show();
    device->raise();
    device->activateWindow();
}