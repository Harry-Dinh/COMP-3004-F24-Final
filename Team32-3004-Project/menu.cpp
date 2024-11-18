#include "menu.h"

Menu::Menu(const QString &name, Menu *parent){
    this->name = name;
    this->parent = parent;
}

void Menu::addSubMenu(Menu* m){
    this->subMenus.append(m);
}

void Menu::addLayout(QLayout* l){
    this->layout = l;
}

QLayout* Menu::getLayout(){
    return this->layout;
}
