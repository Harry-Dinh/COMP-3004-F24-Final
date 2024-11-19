#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "profile.h"
#include "menu.h"
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
        void deleteProfile(int id);
    public slots:
        void drainBattery();
        void powerButtonPressed();
        void backButtonPressed();
        void createProfilePagePressed();
        void deleteProfilePressed();
        void loginProfilePressed();
        void createProfile();

    private slots:
        void on_profileComboBox_currentIndexChanged(int index);

private:
        Ui::MainWindow *ui;
        QTimer* batteryTimer;
        int batteryPercentage;
        QVector<Profile*> profiles;
        QVector<Menu*> menus;
        Menu *currMenu;//pointer to the current menu to display
        int selectedProfile;
        int numProfiles;
};
#endif // MAINWINDOW_H
