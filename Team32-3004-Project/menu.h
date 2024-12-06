#ifndef MENU_H
#define MENU_H

#include <QObject>
#include <QVector>
#include <QString>
#include <QLayout>

class Menu : public QObject {
    Q_OBJECT
    private:
        QString name;//current menu name
        Menu* parent;//pointer to parent;
        int menuIndex;//current index for this menu
    
    public:
        explicit Menu(const QString &name, Menu *parent);

        QString getName();//returns this menu's name
        Menu* getParent();//returns this menu's parent
        int getIndex();//returns the index of this menu
        void setIndex(int i);//sets the index of this menu
};

#endif // MENU_H
