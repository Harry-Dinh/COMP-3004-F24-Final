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
        void addProfile(Profile *p);
        void loadProfile();//load profile from the SQL database
        void changePage(int index);
        
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
        void recommendationPageButtonPressed();


    private slots:
        void on_profileComboBox_currentIndexChanged(int index);

        void on_viewSummaryButton_clicked();

        void on_summaryButton_clicked();

private:
        Ui::MainWindow *ui;
        SummaryWindow *summaryWindow;
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
