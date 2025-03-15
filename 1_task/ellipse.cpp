#include "ellipse.h"

Ellipse::Ellipse()
    : position_(0, 0)
    , radius_1_(0)
    , radius_2_(0)
    , is_visible_(true)
    , ellipse_item_(nullptr)
{}

Ellipse::Ellipse(int x, int y, int radius_1, int radius_2, const QPen& pen)
    : position_(x, y)
    , radius_1_(radius_1)
    , radius_2_(radius_2)
    , pen_(pen)
    , is_visible_(true)
{
    ellipse_item_ = new QGraphicsEllipseItem(0, 0, radius_1_ * 2, radius_2_ * 2);
    ellipse_item_->setPen(pen_);
}

void Ellipse::MoveTo(int dx, int dy) {
    position_.MoveToX(dx);
    position_.MoveToY(dy);
    if (ellipse_item_) {
        ellipse_item_->setPos(position_.GetX() - radius_1_, position_.GetY() - radius_2_);
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
        ellipse_item_->setPos(position_.GetX(), position_.GetY());
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
    return position_.GetX();
}

int Ellipse::GetY() const {
    return position_.GetY();
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
