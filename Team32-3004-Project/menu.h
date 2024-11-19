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

        void addSubMenu(Menu* m);//add pointer to a submenu to this menu
        QString getName();//return this menu's name
        Menu* getParent();
        int getIndex();
        void setIndex(int i);

    private:
        QString name;//current menu name
        Menu* parent;//pointer to parent;
        QVector<Menu*> subMenus;//pointers to subMenus
        int menuIndex;
    signals:

};

#endif // MENU_H
