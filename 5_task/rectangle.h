#ifndef RECTANGLE_H
#define RECTANGLE_H
#pragma once

#include "quadrilateral.h"

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QPen>

class Rectangle : public Quadrilateral {
public:
    Rectangle();
    Rectangle(QGraphicsScene* scene, int x, int y, int width, int height, const QPen& pen = QPen(QColor(123, 111, 93), 3), const FigureType& figure_type = FigureType::rectangle_);
    ~Rectangle();

    void SetSize(const int w, const int h) override;
    void Show() override;
    void RemoveFromScene() override;

    void RotateRectangle(const int degrees);

protected:
    QGraphicsRectItem* rect_item_;
};

#endif // RECTANGLE_H
