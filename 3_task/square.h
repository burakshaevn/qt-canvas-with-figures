#ifndef SQUARE_H
#define SQUARE_H
#pragma once

#include "rectangle.h"

class Square : public Rectangle {
public:
    Square();
    Square(int x, int y, int width, const QPen& pen = QPen(QColor("#7b6f5d")));
    ~Square();
    void SetSize(const int w, const int h) override;
    void Show(QGraphicsScene *scene) override;
    void RemoveFromScene(QGraphicsScene* scene) override;

private:
    QGraphicsRectItem* rect_item_;
};

#endif // SQUARE_H
