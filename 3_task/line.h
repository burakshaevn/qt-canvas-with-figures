#ifndef LINE_H
#define LINE_H

#pragma once

#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QPen>

#include "figure.h"

class Line : public Figure {
public:
    Line();
    Line(int x1, int y1, int x2, int y2, const QPen& pen = QPen(QColor("#7b6f5d")));
    ~Line();
    void MoveTo(const int dx, const int dy) override;
    void SetSize(const int w, const int h) override;
    void Show(QGraphicsScene *scene) override;
    void RemoveFromScene(QGraphicsScene* scene) override;

private:
    int x2_, y2_;
    QGraphicsLineItem* line_item_;
};

#endif // LINE_H
