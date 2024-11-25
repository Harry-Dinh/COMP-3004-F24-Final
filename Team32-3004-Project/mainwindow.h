#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "profile.h"
#include "menu.h"
#include "history.h"

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
        void loadProfile();//load profile from the SQL database

        void deleteProfile(int id);
        void changePage(int index);
        void loadHistory();//load all historical data from the SQL database
    public slots:
        void drainBattery();
        void powerButtonPressed();
        void backButtonPressed();
        void createProfilePagePressed();
        void deleteProfilePressed();
        void loginProfilePressed();
        void measureMenuPressed();
        void historyMenuPressed();
        void probePressed();
        void createProfile();


    private slots:
        void on_profileComboBox_currentIndexChanged(int index);

private:
        Ui::MainWindow *ui;
        QTimer* batteryTimer;
        int batteryPercentage;
        bool deviceOn;
        QVector<Profile*> profiles;
        QVector<Menu*> menus;
        Menu *currMenu;//pointer to the current menu to display
        int selectedProfile;
        int numProfiles;
        history* historydb;

        bool beginMeasurement;
        Measurement* currMeasurement;//pointer to the current ongoing measurement
        int measurePoint;//number of points measured
};
#endif // MAINWINDOW_H
