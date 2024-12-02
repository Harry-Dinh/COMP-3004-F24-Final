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
        QVector<Menu*> subMenus;//pointers to subMenus
        int menuIndex;
    
    public:
        explicit Menu(const QString &name, Menu *parent);

        QString getName();//return this menu's name
        Menu* getParent();
        int getIndex();
        void setIndex(int i);
};

#endif // MENU_H
