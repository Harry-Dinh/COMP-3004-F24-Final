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

        void addSubMenu(Menu* m);

    private:
        QString name;//current menu name
        Menu* parent;//pointer to parent;
        QVector<Menu*> subMenus;//pointers to subMenus
        QLayout *layout;//pointer to a layout
    signals:

};

#endif // MENU_H
