#ifndef RECOMMENDATION_H
#define RECOMMENDATION_H

#include <QString>
#include <QWidget>
#include <QVBoxLayout>

class Recommendation: public QWidget {
    private:
        QString title;
        QString description;
        
    public:
        Recommendation(QWidget* parent, QString& title, QString& description);
        
        QVBoxLayout& createRecommendationWidget();
};

#endif // RECOMMENDATION_H
