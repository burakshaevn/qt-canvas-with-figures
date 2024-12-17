#include "ellipse.h"

Ellipse::Ellipse() = default;

Ellipse::Ellipse(int x, int y, int radius_1, int radius_2, const QPen& pen, const FigureType& figure_type)
    : Figure(x, y, radius_1 * 2, radius_2 * 2, pen, 3, figure_type)
    , radius_1_(radius_1)
    , radius_2_(radius_2)
{
    ellipse_item_ = new QGraphicsEllipseItem(0, 0, radius_1_ * 2, radius_2_ * 2);
    ellipse_item_->setPen(pen);
}

Ellipse::~Ellipse() = default;

void Ellipse::MoveTo(const int dx, const int dy) {
    x_ += dx;
    y_ += dy;
    if (ellipse_item_) {
        ellipse_item_->setPos(x_ - radius_1_, y_ - radius_2_);
    }
}

void Ellipse::Show(QGraphicsScene *scene) {
    if (!ellipse_item_) {
        ellipse_item_ = new QGraphicsEllipseItem(0, 0, radius_1_ * 2, radius_2_ * 2);
    }
    if (ellipse_item_ && !ellipse_item_->scene()) {
        scene->addItem(ellipse_item_);
    }
    ellipse_item_->setPos(x_, y_);
    ellipse_item_->setPen(pen_);
    ellipse_item_->setVisible(is_visible_);
}

void Ellipse::SetSize(const int w, const int h) {
    radius_1_ = w / 2;
    radius_2_ = h / 2;
    w_ = radius_1_ * 2;
    h_ = radius_2_ * 2;
    if (ellipse_item_) {
        ellipse_item_->setRect(0, 0, w_, h_);
    }
}

void Ellipse::RemoveFromScene(QGraphicsScene *scene) {
    if (ellipse_item_ && ellipse_item_->scene() == scene) {
        scene->removeItem(ellipse_item_);
        delete ellipse_item_;
        ellipse_item_ = nullptr;
    }
}
