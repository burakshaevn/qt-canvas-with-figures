#ifndef CIRCLE_H
#define CIRCLE_H

#pragma once

#include "figure.h"

#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QPen>

class Circle : public Figure {
public:
    Circle();
    Circle(QGraphicsScene* scene, int x, int y, int radius_1, int radius_2, const QPen& pen = QPen(QColor(123, 111, 93), 3), const FigureType& figure_type = FigureType::ellipse_);
    virtual ~Circle();
    void SetSize(const int w, const int h) override;
    void Show() override;
    void RemoveFromScene() override;

protected:
    int radius_1_;
    int radius_2_;

    // Элемент для отображения окружности. Это класс из библиотеки фрейморка Qt, представляющий графический элемент,
    // который рисует окружность на сцене в рамках холста QGraphicsView.
    QGraphicsEllipseItem* circle_item_;
};

#endif // CIRCLE_H
