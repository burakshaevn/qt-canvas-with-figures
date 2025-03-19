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

    void Rotate(const int degrees, QGraphicsScene* scene) override;

    void SetVisible(bool visible) override;
    bool GetVisible() const override;

    void SetCoords(const int x, const int y) override;
    int GetX() const override;
    int GetY() const override;
    int GetW() const override;
    int GetH() const override;

    void SetPen(const QPen& pen, const int pen_width) override;
    QPen GetPen() const override;

protected:
    QGraphicsRectItem* rect_item_;

};

#endif // RECTANGLE_H
