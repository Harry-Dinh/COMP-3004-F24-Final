#ifndef DEVICE_H
#define DEVICE_H

#include <QWidget>
#include <QTimer>

namespace Ui {
    class Device;
}

class Device : public QWidget {
    Q_OBJECT
    private:
        Ui::Device *ui;
        QTimer* batteryTimer;
        QTimer* chargingTimer;
        int batteryPercentage;
        bool deviceOn;
    
    public:
        explicit Device(QWidget *parent = nullptr);
        ~Device();
    
    
    public slots:
        /**
         * @brief An action that drains the battery of the device 1% every two seconds to simulate the device being drained of power.
         */
        void drainBattery();
    
        /**
         * @brief An action that "charges" the device's battery when it's running low. It charges the battery 1% every 0.5 seconds (faster than draining.)
         */
        void chargeDevice();
    
        /**
         * @brief An action that occur when the power button is pressed.
         */
        void powerButtonPressed();
    
        /**
         * @brief An action that occur when the recharge button is pressed.
         */
        void rechargeButtonPressed();
    
        /**
         * @brief Generate a random meridian value within the pre-specified range and add it to a newly created measurement.
         * This action simulates pressing the device tip against parts of your body to take a reading.
         */
        void probePressed();
    
    signals:
        void sendMeasurement(int value);
        void measurementInterrupted();
};

#endif // DEVICE_H
