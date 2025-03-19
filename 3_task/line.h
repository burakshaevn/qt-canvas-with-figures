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
    Line(int x1, int y1, int x2, int y2, const QPen& pen = QPen(QColor("#7b6f5d"), 3));

    void MoveTo(const int dx, const int dy) override;
    void SetCoords(const int x, const int y) override;
    void SetSize(const int w, const int h) override;
    void Show(QGraphicsScene *scene) override;
    void RemoveFromScene(QGraphicsScene* scene) override;

    void SetVisible(bool visible) override;
    bool GetVisible() const override;

    int GetX() const override;
    int GetY() const override;
    int GetW() const override;
    int GetH() const override;

    void SetPen(const QPen& pen, const int pen_width) override;
    QPen GetPen() const override;

private:
    Point start_; // Начальная точка линии
    Point end_;   // Конечная точка линии
    int w_ = 0;   // Ширина (разница по X)
    int h_ = 0;   // Высота (разница по Y)
    bool is_visible_ = true;
    QGraphicsLineItem* line_item_;
};

#endif // LINE_H
