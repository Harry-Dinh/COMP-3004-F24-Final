#include "menu.h"

Menu::Menu(const QString &name, Menu *parent){
    this->name = name;
    this->parent = parent;
}

QString Menu::getName(){
    return this->name;
}

Menu* Menu::getParent(){
    return this->parent;
}

int Menu::getIndex(){
    return this->menuIndex;
}

void Menu::setIndex(int i){
    this->menuIndex = i;
}
