#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "profile.h"

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
        
    public slots:
        void drainBattery();
        void powerButtonPressed();
        void addProfile(int id, const QString &firstName, const QString &lastName,
                        int weight, int height, const QString &DOB, const QString &country,
                        const QString &phone, const QString &email, const QString &password);
        void deleteProfile(int id);

    private:
        Ui::MainWindow *ui;
        QTimer* batteryTimer;
        int batteryPercentage;
        QVector<Profile*> profiles;
};
#endif // MAINWINDOW_H
