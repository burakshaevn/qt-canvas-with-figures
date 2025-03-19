#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include "rectangle.h"
#include <QGraphicsPolygonItem>

class Trapezoid : public Rectangle {
public:
    Trapezoid();
    Trapezoid(int x, int y, int base1, int base2, int height, const QPen& pen = QPen(QColor("#7b6f5d")), const FigureType& figure_type = FigureType::trapezoid_);
    virtual ~Trapezoid();

    void MoveTo(const int dx, const int dy) override;
    void SetSize(const int base1, const int base2, const int height);
    void Show(QGraphicsScene* scene) override;
    void RemoveFromScene(QGraphicsScene* scene) override;

    void Rotate(const int degrees, QGraphicsScene* scene) override;

protected:
    QGraphicsPolygonItem* trapezoid_item_;
    int base1_;  // Длина первого основания
    int base2_;  // Длина второго основания
    int height_; // Высота трапеции
};

#endif // TRAPEZOID_H
