#ifndef RECOMMENDATION_H
#define RECOMMENDATION_H

#include <iostream>
#include <QWidget>
#include <QVBoxLayout>

using namespace std;

class Recommendation: public QWidget {
    private:
        string title;
        string description;
        
    public:
        Recommendation(QWidget* parent, string title, string description);
        
        QVBoxLayout* createRecommendationWidget();
};

#endif // RECOMMENDATION_H
