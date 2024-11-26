#include "recommendation.h"

Recommendation::Recommendation(QWidget* parent, QString& title, QString& description): QWidget(parent) {
    this->title = title;
    this->description = description;
}

QVBoxLayout& Recommendation::createRecommendationWidget() {
    QVBoxLayout box = QVBoxLayout(this);
}