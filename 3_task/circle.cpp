#include "circle.h"

Circle::Circle() = default;

Circle::Circle(int x, int y, int radius, const QPen& pen)
    : Ellipse(x, y, radius, radius, pen, FigureType::circle_)
{
    // Устанавливаем только один радиус в оба радиуса, так как это круг (один диаметр)
    radius_1_ = radius;
    radius_2_ = radius;
    if (!ellipse_item_) {
        ellipse_item_ = new QGraphicsEllipseItem(0, 0, radius * 2, radius * 2);
    }
    ellipse_item_->setPen(pen);
    SetFigureType(FigureType::circle_);
}

Circle::~Circle() = default;

void Circle::SetSize(const int w, [[maybe_unused]] const int h) {
    w_ = w;
    h_ = h;
    radius_1_ = w / 2;
    radius_2_ = radius_1_;
    if (ellipse_item_) {
        ellipse_item_->setRect(ellipse_item_->rect().x(), ellipse_item_->rect().y(), radius_1_ * 2, radius_2_ * 2);
    }
}
