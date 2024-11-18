#include <iostream>
#include <QDebug>
#include <QListWidget>
#include <QLayout>
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


    //create new profile
    addProfile(0,"first","last",70,200, "20000110","Canda","12345678980", "email@email.com","password");


    //create example layout for profile list, placeholder buttons for now
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setContentsMargins(0,0,0,0);
    layout->setMargin(0);
    layout->setSpacing(0);
    QPushButton* pButton = new QPushButton("Profile1");
    layout->addWidget(pButton);
    pButton = new QPushButton("Profile2");
    layout->addWidget(pButton);
    pButton = new QPushButton("Profile3");
    layout->addWidget(pButton);
    pButton = new QPushButton("Profile4");
    layout->addWidget(pButton);
    pButton = new QPushButton("Profile5");
    layout->addWidget(pButton);

    layout->addStretch(1);//align all buttons on top

    addMenu("Profile Menu", nullptr, layout);//create this menu with layout from above

    ui->MenuWidget->setLayout(menus[0]->getLayout());
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
