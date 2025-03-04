#include "ellipse.h"

Ellipse::Ellipse() = default;

Ellipse::Ellipse(int x, int y, int radius_1, int radius_2, const QPen& pen, const FigureType& figure_type)
    : Figure({x, y}, radius_1 * 2, radius_2 * 2, pen, 3, figure_type)
    , radius_1_(radius_1)
    , radius_2_(radius_2)
{
    ellipse_item_ = new QGraphicsEllipseItem(0, 0, radius_1_ * 2, radius_2_ * 2);
    ellipse_item_->setPen(pen);
    SetFigureType(FigureType::ellipse_);
}

Ellipse::~Ellipse() = default;

void Ellipse::MoveTo(const int dx, const int dy) {
    position_.MoveToX(dx);
    position_.MoveToY(dy);
    if (ellipse_item_) {
        ellipse_item_->setPos(position_.GetX() - radius_1_, position_.GetY() - radius_2_);
    }
}

void Ellipse::Show(QGraphicsScene *scene) {
    if (!ellipse_item_) {
        ellipse_item_ = new QGraphicsEllipseItem(0, 0, radius_1_ * 2, radius_2_ * 2);
    }
    if (ellipse_item_ && !ellipse_item_->scene()) {
        scene->addItem(ellipse_item_);
    }
    ellipse_item_->setPos(position_.GetX(), position_.GetY());
    ellipse_item_->setPen(pen_);
    ellipse_item_->setVisible(is_visible_);
}

void Ellipse::SetSize(const int w, const int h) {
    w_ = w;
    h_ = h;
    if (ellipse_item_) {
        // ellipse_item_->setRect(0, 0, w_, h_);
        ellipse_item_->setRect(ellipse_item_->rect().x(), ellipse_item_->rect().y(), radius_1_ * 2, radius_2_ * 2);
    }
}

void Ellipse::RemoveFromScene(QGraphicsScene *scene) {
    if (ellipse_item_ && ellipse_item_->scene() == scene) {
        scene->removeItem(ellipse_item_);
        delete ellipse_item_;
        ellipse_item_ = nullptr;
    }
}
