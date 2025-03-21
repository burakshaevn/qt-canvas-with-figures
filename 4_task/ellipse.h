#ifndef ELLIPSE_H
#define ELLIPSE_H

#pragma once

#include "circle.h"

class Ellipse : public Circle {
public:
    Ellipse();
    Ellipse(QGraphicsScene* scene, int x, int y, int radius_1, int radius_2, const QPen& pen = QPen(QColor("#7b6f5d")));
    ~Ellipse();
    void SetSize(const int w, [[maybe_unused]] const int h) override;

    void Rotate(const int degrees) override;
};

#endif // ELLIPSE_H
