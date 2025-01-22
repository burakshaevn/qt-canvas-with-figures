#include "ellipse.h"

Ellipse::Ellipse()
    : x_(0)
    , y_(0)
    , radius_1_(0)
    , radius_2_(0)
    , is_visible_(true)
    , ellipse_item_(nullptr)
{}

Ellipse::Ellipse(int x, int y, int radius_1, int radius_2, const QPen& pen)
    : x_(x)
    , y_(y)
    , radius_1_(radius_1)
    , radius_2_(radius_2)
    , pen_(pen)
    , is_visible_(true)
{
    ellipse_item_ = new QGraphicsEllipseItem(0, 0, radius_1_ * 2, radius_2_ * 2);
    ellipse_item_->setPen(pen_);
}

void Ellipse::MoveTo(int dx, int dy) {
    x_ += dx;
    y_ += dy;
    if (ellipse_item_) {
        ellipse_item_->setPos(x_ - radius_1_, y_ - radius_2_);
    }
}

void Ellipse::SetSize(const int w, const int h) {
    radius_1_ = w / 2;
    radius_2_ = h / 2;
    if (ellipse_item_) {
        ellipse_item_->setRect(0, 0, radius_1_ * 2, radius_2_ * 2);
    }
}

void Ellipse::Show(QGraphicsScene *scene) {
    if (!scene) {
        return; // Проверяем, что сцена существует
    }

    if (!ellipse_item_) {
        ellipse_item_ = new QGraphicsEllipseItem(0, 0, radius_1_ * 2, radius_2_ * 2);
    }

    if (ellipse_item_ && !ellipse_item_->scene()) {
        scene->addItem(ellipse_item_);
    }

    if (ellipse_item_) {
        ellipse_item_->setPos(x_, y_);
        ellipse_item_->setPen(pen_);
        ellipse_item_->setVisible(is_visible_);
    }
}

void Ellipse::RemoveFromScene(QGraphicsScene *scene) {
    if (ellipse_item_ && scene) {
        scene->removeItem(ellipse_item_);
    }
}

int Ellipse::GetX() const {
    return x_;
}
int Ellipse::GetY() const {
    return y_;
}
int Ellipse::GetW() const {
    return radius_1_ * 2;
}
int Ellipse::GetH() const {
    return radius_2_ * 2;
}

void Ellipse::SetPen(const QPen& pen, const int pen_width) {
    pen_ = pen;
    pen_.setWidth(pen_width);
}
FigureType Ellipse::GetFigureType() const {
    return FigureType::ellipse_;
}
