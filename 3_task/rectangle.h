#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "quadrilateral.h"

class Rectangle : public Quadrilateral {
public:
    Rectangle();
    Rectangle(int x, int y, int width, int height, const QPen& pen = QPen(QColor("#7b6f5d")),
              const FigureType& figure_type = FigureType::rectangle_);
    virtual ~Rectangle();

    void Show(QGraphicsScene* scene) override;
    void RemoveFromScene(QGraphicsScene* scene) override;
    void Rotate(const int degrees, QGraphicsScene* scene) override;
};

#endif // RECTANGLE_H
