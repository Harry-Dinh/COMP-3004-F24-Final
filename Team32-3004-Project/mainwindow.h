#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QString>
#include "profile.h"
#include "menu.h"
#include "history.h"
#include "summarywindow.h"
#include "device.h"

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
        Device *device;

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
         * @brief Handle receiving a measurement signal from the Device
         */
        void handleProbePressed(double value);
        
        /**
         * @brief Create a new user profile for storing a collection of measurements associated with that user.
         */
        void createProfile();
        
        /**
         * @brief Navigate to the recommendations page.
         */
        void recommendationPageButtonPressed();

        /**
         * @brief Handle when a measurement is interrupted.
         * occurs during measurement when:
         *      - back button is pressed
         *      - device is turned off
         *      - device runs out of battery
         */
        void handleMeasureInterrupt();
        
        /**
         * @brief Bring the device window forward or create one if it hasn't been created already.
         */
        void showDeviceButtonPressed();

    signals:
        void measurementInterrupted();
};
#endif // MAINWINDOW_H
