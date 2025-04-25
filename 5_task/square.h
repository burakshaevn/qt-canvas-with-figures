#ifndef SQUARE_H
#define SQUARE_H
#pragma once

#include "quadrilateral.h"

class Square : public Quadrilateral {
public:
    Square();
    Square(QGraphicsScene* scene, int x, int y, int width, const QPen& pen = QPen(QColor(123, 111, 93), 3));
    ~Square();
    void SetSize(const int w, const int h) override;
    void Show() override;
    void RemoveFromScene() override;

    void SetVisible(bool visible) override;
    bool GetVisible() const override;
};

#endif // SQUARE_H
