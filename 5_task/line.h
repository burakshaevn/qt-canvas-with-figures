#ifndef LINE_H
#define LINE_H

#pragma once

#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QPen>

#include "figure.h"
#include "point.h"

class Line : public Figure {
public:
    Line();
    Line(QGraphicsScene* scene, int x1, int y1, int x2, int y2, const QPen& pen = QPen(QColor(123, 111, 93), 3));

    void SetCoords(const int x, const int y) override;
    void SetSize(const int w, const int h) override;
    void UpdatePoints(const int dx, const int dy) override;
    void Show() override;
    void RemoveFromScene() override;

    int GetX() const override;
    int GetY() const override;

private:
    Point start_; // Начальная точка линии
    Point end_;   // Конечная точка линии
    int w_;   // Ширина (разница по X)
    int h_;   // Высота (разница по Y)
    QGraphicsLineItem* line_item_;
};

#endif // LINE_H
