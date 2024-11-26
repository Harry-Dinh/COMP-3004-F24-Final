#include <QLabel>
#include <QFont>
#include "recommendation.h"

Recommendation::Recommendation(QWidget* parent, string title, string description): QWidget(parent) {
    this->title = title;
    this->description = description;
}

QVBoxLayout* Recommendation::createRecommendationWidget() {
    QVBoxLayout box = QVBoxLayout(this);
    QLabel titleLabel = QLabel(QString::fromUtf8(title.c_str()));
    QLabel descriptionLabel = QLabel(QString::fromUtf8(description.c_str()));
    
    // Styling the title font
    QFont titleFont = titleLabel.font();
    titleFont.setWeight(QFont::Bold);
    titleLabel.setFont(titleFont);
    
    // Adding the font to the box layout
    box.addWidget(&titleLabel);
    box.addWidget(&descriptionLabel);
    
    box.setAlignment(&titleLabel, Qt::AlignLeft);
    box.setAlignment(&titleLabel, Qt::AlignLeft);
    
    /// @note Hopefully this warning is nothing important...
    return &box;
}