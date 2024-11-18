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
    
    // Connect the battery timer to the appropriate function
    connect(this->batteryTimer, &QTimer::timeout, this, QOverload<>::of(&MainWindow::drainBattery));
    
    // Connect the power button to its respective function
    connect(ui->powerButton, &QPushButton::clicked, this, &MainWindow::powerButtonPressed);
    
    // Set the initial display value for the battery indicator
    ui->batteryIndicator->display(STARTING_BATTERY_LEVEL);


    //create new profile
    addProfile(0,"first","last",70,200, "20000110","Canda","12345678980", "email@email.com","password");



    initProfilesMenu();
    initAddProfileMenu();


    currMenu = menus[0];
    ui->menuLabel->setText(currMenu->getName());
    ui->MenuWidget->setLayout(currMenu->getLayout());

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

void MainWindow::addMenu(const QString &name, Menu* parent, QLayout *layout){
    Menu *m = new Menu(name, parent);
    m->addLayout(layout);//point menu's layout to passed in layout
    menus.append(m);//add this pointer to the menus list
}

void MainWindow::initProfilesMenu(){
    //create example layout for profile list, placeholder buttons for now
    QVBoxLayout *layout = new QVBoxLayout();
    QComboBox *profileList = new QComboBox();

    layout->addWidget(profileList);
    layout->addStretch(1);//spacer between combo box and buttons

    QPushButton* loginPButton = new QPushButton("Login");
    connect(loginPButton, &QPushButton::clicked, this, &MainWindow::loginProfilePressed);
    layout->addWidget(loginPButton);

    QPushButton* addPButton = new QPushButton("add Profile");
    connect(addPButton, &QPushButton::clicked, this, &MainWindow::createProfilePressed);
    layout->addWidget(addPButton);

    QPushButton* deletePButton = new QPushButton("delete Profile");
    connect(deletePButton, &QPushButton::clicked, this, &MainWindow::removeProfilePressed);
    layout->addWidget(deletePButton);

    addMenu("Profile Menu", nullptr, layout);
}

void MainWindow::initAddProfileMenu(){
    //create layout for profile creation menu
    QVBoxLayout *layout = new QVBoxLayout();

    QLabel *label = new QLabel("First Name");
    layout->addWidget(label);
    QLineEdit *textField = new QLineEdit();
    textField->setPlaceholderText("Enter first name");
    layout->addWidget(textField);

    label = new QLabel("Last Name");
    layout->addWidget(label);
    textField = new QLineEdit();
    textField->setPlaceholderText("Enter last name");
    layout->addWidget(textField);

    label = new QLabel("Weight");
    layout->addWidget(label);
    QSpinBox *spinBox = new QSpinBox();
    layout->addWidget(spinBox);

    label = new QLabel("Height");
    layout->addWidget(label);
    spinBox = new QSpinBox();
    layout->addWidget(spinBox);

    label = new QLabel("Date of Birth");
    layout->addWidget(label);
    QDateEdit *dobSpinBox = new QDateEdit();
    layout->addWidget(dobSpinBox);

    label = new QLabel("Country");
    layout->addWidget(label);
    textField = new QLineEdit();
    textField->setPlaceholderText("Enter country");
    layout->addWidget(textField);

    label = new QLabel("Phone");
    layout->addWidget(label);
    textField = new QLineEdit();
    textField->setPlaceholderText("Enter phone number");
    layout->addWidget(textField);

    label = new QLabel("Email");
    layout->addWidget(label);
    textField = new QLineEdit();
    textField->setPlaceholderText("Enter email");
    layout->addWidget(textField);

    label = new QLabel("Password");
    layout->addWidget(label);
    textField = new QLineEdit();
    textField->setPlaceholderText("Enter password");
    layout->addWidget(textField);

    QPushButton *addButton = new QPushButton("Add Profile");
    layout->addWidget(addButton);

    layout->addStretch(1);//spacer
    addMenu("Create Profile", menus[0], layout);
    menus[0]->addSubMenu(menus[1]);
}

void MainWindow::createProfilePressed(){
    qInfo() << "handle profile creation screen";
}

void MainWindow::removeProfilePressed(){
    qInfo() << "handle deleting profile";
}

void MainWindow::loginProfilePressed(){
    qInfo() << "handle moving to app main menu";
}
