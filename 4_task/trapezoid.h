#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include "rectangle.h"
#include <QGraphicsPolygonItem>

class Trapezoid : public Rectangle {
public:
    Trapezoid();
    Trapezoid(QGraphicsScene* scene, int x, int y, int base1, int base2, int height, const QPen& pen = QPen(QColor("#7b6f5d")), const FigureType& figure_type = FigureType::trapezoid_);
    virtual ~Trapezoid();

    // void MoveTo(const int dx, const int dy) override;
    void SetSize(const int base1, const int base2, const int height);
    void Show() override;
    void RemoveFromScene() override;

    void Rotate(const int degrees) override;

protected:
    QGraphicsPolygonItem* trapezoid_item_;
    int base1_;  // Длина первого основания
    int base2_;  // Длина второго основания
    int height_; // Высота трапеции
};

#endif // TRAPEZOID_H
