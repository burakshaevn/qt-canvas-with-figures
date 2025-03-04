#ifndef RECTANGLE_H
#define RECTANGLE_H
#pragma once

#include "figure.h"

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QPen>

class Rectangle : public Figure {
public:
    Rectangle();
    Rectangle(int x, int y, int width, int height, const QPen& pen = QPen(QColor("#7b6f5d")), const FigureType& figure_type = FigureType::rectangle_);
    virtual ~Rectangle();
    void MoveTo(const int dx, const int dy) override;
    void SetSize(const int w, const int h) override;
    void Show(QGraphicsScene *scene) override;
    void RemoveFromScene(QGraphicsScene* scene) override;

protected:
    QGraphicsRectItem* rect_item_;
};

#endif // RECTANGLE_H
