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
        void drainBattery();
        void chargeDevice();
        void powerButtonPressed();
        void rechargeButtonPressed();
        void backButtonPressed();//sets the current page to the menu's parent menu
        void createProfilePagePressed();//sets current page to the profile creation menu
        void deleteProfilePressed();//deletes the selected profile
        void loginProfilePressed();//login as the selected profile
        void measureMenuPressed();//sets current page to the measurement menu and begins measurement
        void historyMenuPressed();//sets current page to the history menu
        void probePressed();//simulate applying the probe on the skin
        void createProfile();//handle profile creation from ui input fields
        void recommendationPageButtonPressed();


    private slots:
        void on_profileComboBox_currentIndexChanged(int index);

        void on_viewSummaryButton_clicked();

        void on_summaryButton_clicked();

private:
        Ui::MainWindow *ui;
        SummaryWindow *summaryWindow;
        QTimer* batteryTimer;
        QTimer* chargingTimer;
        int batteryPercentage;
        bool deviceOn;//device on/off state
        QVector<Profile*> profiles;//stores pointers of profiles in the program
        QVector<Menu*> menus;//stores pointers of menus in the program
        Menu *currMenu;//pointer to the current menu to display
        int selectedProfile;//index of the ui's profileComboBox
        int numProfiles;//stores number of profiles currently loaded in the program
        History* historydb;

        bool beginMeasurement;//begin measurement state
        Measurement* currMeasurement;//pointer to the current ongoing measurement
        int measurePoint;//number of points measured
};
#endif // MAINWINDOW_H
