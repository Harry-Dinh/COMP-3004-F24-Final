#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QString>
#include "profile.h"
#include "menu.h"
#include "history.h"
#include "summarywindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
    
    private:
        Ui::MainWindow *ui;
        SummaryWindow *summaryWindow;
        QTimer* batteryTimer;
        QTimer* chargingTimer;
        int batteryPercentage;
        bool deviceOn;
        QVector<Profile*> profiles;
        QVector<Menu*> menus;
        Menu *currMenu;//pointer to the current menu to display
        int selectedProfile;
        int numProfiles;
        History* historydb;
        
        bool beginMeasurement;
        Measurement* currMeasurement;//pointer to the current ongoing measurement
        int measurePoint;//number of points measured
        
    private slots:
        void on_profileComboBox_currentIndexChanged(int index);
        
        void on_viewSummaryButton_clicked();
        
        void on_summaryButton_clicked();

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();
        void addMenu(const QString &name, Menu* parent, int index);
        void addProfile(int id, const QString &firstName, const QString &lastName,
                        int weight, int height, const QString &DOB, const QString &country,
                        const QString &phone, const QString &email, const QString &password);
        void addProfile(Profile *p);//overloaded addProfile used for loading profiles from the DB
        void loadProfile();//load profile from the SQL database
        void changePage(int index);//change the page index on the UI
        
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
         * @brief Navigate to the previous page.
         */
        void backButtonPressed();
        
        /**
         * @brief Navigate to the profile creation page.
         */
        void createProfilePagePressed();
        
        /**
         * @brief An action that occur when the delete profile button is pressed.
         */
        void deleteProfilePressed();
        
        /**
         * @brief Navigate from the profile creation screen to the main menu screen.
         */
        void loginProfilePressed();
        
        /**
         * @brief Navigate to the measurement menu.
         */
        void measureMenuPressed();
        
        /**
         * @brief Navigate to the history menu.
         */
        void historyMenuPressed();
        
        /**
         * @brief Generate a random meridian value within the pre-specified range and add it to a newly created measurement.
         * This action simulates pressing the device tip against parts of your body to take a reading.
         */
        void probePressed();
        
        /**
         * @brief Create a new user profile for storing a collection of measurements associated with that user.
         */
        void createProfile();
        
        /**
         * @brief Navigate to the recommendations page.
         */
        void recommendationPageButtonPressed();
};
#endif // MAINWINDOW_H
