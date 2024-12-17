#include "circle.h"

Circle::Circle() = default;

Circle::Circle(int x, int y, int radius, const QPen& pen)
    : Ellipse(x, y, radius, radius, pen)
{
    // Устанавливаем только один радиус в оба радиуса, так как это круг (один диаметр)
    radius_1_ = radius;
    radius_2_ = radius;
    if (!ellipse_item_) {
        ellipse_item_ = new QGraphicsEllipseItem(0, 0, radius * 2, radius * 2);
    }
    ellipse_item_->setPen(pen);
}

Circle::~Circle() = default;

void Circle::SetSize(const int w, [[maybe_unused]] const int h) {
    radius_1_ = w / 2;
    radius_2_ = radius_1_;
    if (ellipse_item_) {
        ellipse_item_->setRect(0, 0, radius_1_ * 2, radius_2_ * 2);
    }
}
