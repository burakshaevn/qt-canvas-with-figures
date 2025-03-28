#ifndef Rhomb_H
#define Rhomb_H

#include "rectangle.h"
#include <QGraphicsPolygonItem>

class Rhomb : public Rectangle {
public:
    Rhomb();
    Rhomb(QGraphicsScene* scene, int x, int y, int side, int height, const QPen& pen = QPen(QColor(123, 111, 93), 3), const FigureType& figure_type = FigureType::rhomb_);
    ~Rhomb();

    void SetSize(const int side, const int height) override;
    void Show() override;
    void RemoveFromScene() override;

    void Rotate(const int degrees) override;

protected:
    QGraphicsPolygonItem* rhomb_item_;
    int side_;  // Длина стороны ромба
    int height_; // Высота ромба
};

#endif // RHOMB_H
