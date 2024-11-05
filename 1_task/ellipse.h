#ifndef ELLIPSE_H
#define ELLIPSE_H

#pragma once

#include "figure.h"

#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QPen>

class Ellipse : public Figure {
public:
    Ellipse();
    Ellipse(int x, int y, int radius_1, int radius_2, const QPen& pen = QPen(QColor("#7b6f5d")), const FigureType& figure_type = FigureType::ellipse_);
    virtual ~Ellipse();
    void MoveTo(int x, int y) override;
    void SetSize(const int w, [[maybe_unused]] const int h) override;
    void Show(QGraphicsScene *scene) override;
    void RemoveFromScene(QGraphicsScene* scene) override;

protected:
    int radius_1_;
    int radius_2_;

    // Элемент для отображения окружности. Это класс из библиотеки фрейморка Qt, представляющий графический элемент,
    // который рисует эллипс (или окружность) на сцене в рамках холста QGraphicsView.
    QGraphicsEllipseItem* ellipse_item_;
};

#endif // ELLIPSE_H
