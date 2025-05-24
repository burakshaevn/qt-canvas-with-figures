#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include "quadrilateral.h"
#include <QGraphicsPolygonItem>

class Trapezoid : public Quadrilateral {
public:
    Trapezoid();
    Trapezoid(QGraphicsScene* scene, int x, int y, int base1, int base2, int height, const QPen& pen = QPen(QColor(123, 111, 93), 3), const FigureType& figure_type = FigureType::trapezoid_);
    virtual ~Trapezoid();

    // void MoveTo(const int dx, const int dy) override;
    void SetSize(const int base1, const int base2, const int height);
    void Show() override;
    void RemoveFromScene() override;

    void RotateTrapezoid(const int degrees);

protected:
    QGraphicsPolygonItem* trapezoid_item_;
    int base1_;  // Длина первого основания
    int base2_;  // Длина второго основания
    int height_; // Высота трапеции
};

#endif // TRAPEZOID_H
