#ifndef MENU_H
#define MENU_H

#include <QObject>
#include <QVector>
#include <QString>
#include <QLayout>

class Menu : public QObject{
    Q_OBJECT
    public:
        explicit Menu(const QString &name, Menu *parent);

    private:
        QString name;//current menu name
        Menu* parent;//pointer to parent;
        QVector<Menu*> subMenus;//pointers to subMenus
        QVector<QObject> widgets;//store a list of objects
        QLayout *layout;//pointer to a layout
    signals:

};

#endif // MENU_H
