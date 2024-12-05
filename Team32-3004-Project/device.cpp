#include "device.h"
#include "ui_device.h"
#include "defs.h"
#include <random>

Device::Device(QWidget *parent) : QWidget(parent),ui(new Ui::Device){
    ui->setupUi(this);
    setWindowTitle("RaDoTech Device");

    this->batteryTimer = new QTimer();
    this->chargingTimer = new QTimer();
    this->batteryPercentage = STARTING_BATTERY_LEVEL;
    this->deviceOn = false;

    // Connect the battery timer to the appropriate function
    connect(this->batteryTimer, &QTimer::timeout, this, QOverload<>::of(&Device::drainBattery));

    // Connect the charge timer to the appropriate function
    connect(this->chargingTimer, &QTimer::timeout, this, QOverload<>::of(&Device::chargeDevice));

    // Connect the power button to its respective function
    connect(ui->powerButton, &QPushButton::clicked, this, &Device::powerButtonPressed);

    // Connect the recharge button to its respective function
    connect(ui->rechargeButton, &QPushButton::clicked, this, &Device::rechargeButtonPressed);

    //connect probe button with
    connect(ui->probeButton, &QPushButton::clicked, this, &Device::probePressed);

    // Set the initial display value for the battery indicator
    ui->batteryIndicator->display(STARTING_BATTERY_LEVEL);
}

Device::~Device() {
    delete this->batteryTimer;
    delete this->chargingTimer;
    delete ui;
}


void Device::drainBattery(){
    if (batteryPercentage > 0) {
        ui->powerButton->setDisabled(false);
        --batteryPercentage;
        ui->batteryIndicator->display(batteryPercentage);

        // Change the battery indicator to a red colour to let the user know that the device is low on battery
        if (batteryPercentage <= 10) {
            ui->batteryIndicator->setStyleSheet("color: red;");
            ui->chargeStatus->setText("Battery low, please recharge!");
            ui->chargeStatus->setStyleSheet("color: red;");
        }
    } else {
        batteryTimer->stop();       // Stop the timer when the battery level drops to 0
        deviceOn = false;

        // Device ran out of battery
        if (batteryPercentage <= 0) {
            ui->powerButton->setDisabled(true);
            ui->powerButton->setDefault(false);
            ui->powerButton->setText("Power On");
            ui->rechargeButton->setDisabled(false);
            ui->probeButton->setDisabled(true);
        }

        //device battery ran out before finishing measurement
        if(batteryPercentage == 0){
            emit(measurementInterrupted());
        }
    }
}

void Device::chargeDevice() {
    if (batteryPercentage < STARTING_BATTERY_LEVEL) {
        ++batteryPercentage;
        ui->batteryIndicator->display(batteryPercentage);

        if (batteryPercentage == STARTING_BATTERY_LEVEL) {
            ui->chargeStatus->setText("Battery fully charged!");
            ui->chargeStatus->setStyleSheet("color: green;");
        }
    } else {
        chargingTimer->stop();
        ui->batteryIndicator->setStyleSheet("");
        ui->chargeStatus->setStyleSheet("");
    }
}

void Device::powerButtonPressed() {
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
        ui->probeButton->setDisabled(false);
        deviceOn = true;
        batteryTimer->start(2000);      // Drain the battery 1% every 2 seconds
    } else {
        ui->powerButton->setDefault(false);
        ui->powerButton->setText("Power On");
        ui->rechargeButton->setDisabled(false);
        ui->probeButton->setDisabled(true);
        deviceOn = false;

        //send signal to mainWindow since turning off may have interrupted an ongoing measurement
        emit(measurementInterrupted());


        batteryTimer->stop();           // Simulate the action of turning off the device when the power button is pressed again
    }
}

void Device::rechargeButtonPressed() {
    // Change the states of the associated UI elements when the recharge button is pressed

    if (!ui->rechargeButton->isDefault()) {     // Recharge button is not pressed
        ui->rechargeButton->setDefault(true);
        ui->batteryIndicator->setStyleSheet("color: green;");   // Set the battery percentage colour to green to indicate charging
        ui->rechargeButton->setText("Stop Charging");
        ui->powerButton->setDisabled(true);
        ui->chargeStatus->setText("Charging...");
        ui->probeButton->setDisabled(true);
        ui->chargeStatus->setStyleSheet("");
        chargingTimer->start(500);    // Charge the battery 1% every 0.5 seconds
    } else {    // Recharge button is pressed
        ui->rechargeButton->setDefault(false);
        ui->batteryIndicator->setStyleSheet("");   // Change the colour of the battery indicator back to default
        ui->rechargeButton->setText("Recharge");
        ui->powerButton->setDisabled(false);
        ui->chargeStatus->setText("Not charging");
        chargingTimer->stop();
    }
}

void Device::probePressed(){
    //make measurements if in the measurement window
    if(deviceOn){
        // Set up the random number generator (got this from some random stackoverflow forum)
        std::random_device rand;
        std::mt19937 gen(rand());
        std::uniform_int_distribution<> distr(RYODORAKU_MIN_BOUND, RYODORAKU_MAX_BOUND); // Define the range (5, 160)

        // Generate the random value then send it to MainWindow
        double randValue = distr(gen);
        emit(sendMeasurement(randValue));
    }
}
