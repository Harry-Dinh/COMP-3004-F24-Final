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

        QString getName();//return this menu's name
        Menu* getParent();//return the pointer to the parent of this menu
        int getIndex();//get the menu's index
        void setIndex(int i);//set the menu's index

    private:
        QString name;//current menu name
        Menu* parent;//pointer to parent;
        int menuIndex;//stores the index of this menu
    signals:

};

#endif // MENU_H
