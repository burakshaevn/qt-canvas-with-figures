#ifndef CIRCLE_H
#define CIRCLE_H

#pragma once

#include "ellipse.h"

class Circle : public Ellipse {
public:
    Circle();
    Circle(int x, int y, int radius, const QPen& pen = QPen(QColor("#7b6f5d")));
    ~Circle();
    void SetSize(const int w, [[maybe_unused]] const int h) override;
};

#endif // CIRCLE_H
