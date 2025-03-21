#include "circle.h"

Circle::Circle() = default;

Circle::Circle(QGraphicsScene* scene, int x, int y, int radius_1, int radius_2, const QPen& pen, const FigureType& figure_type)
    : Figure(scene, {x, y}, radius_1 * 2, radius_2 * 2, pen, 3, figure_type)
    , radius_1_(radius_1)
    , radius_2_(radius_2)
{
    circle_item_ = new QGraphicsEllipseItem(0, 0, radius_1_ * 2, radius_2_ * 2);
    circle_item_->setPen(pen);
    SetFigureType(FigureType::circle_);
    qDebug() << "Создана окружность с центром в (" << x << ',' << y << ") и радиусом " << radius_1 << " и внутренним радиусом " << radius_2 << '.';
}

Circle::~Circle() = default;

// void Circle::MoveTo(const int dx, const int dy) {
//     position_.MoveToX(dx);
//     position_.MoveToY(dy);
//     // if (circle_item_) {
//     //     circle_item_->setPos(position_.GetX() - radius_1_, position_.GetY() - radius_2_);
//     // }
// }

void Circle::SetSize(const int w, const int h) {
    radius_1_ = radius_2_ = w / 2;
    if (circle_item_) {
        circle_item_->setRect(0, 0, radius_1_ * 2, radius_1_ * 2);
    }
}

void Circle::Show() {
    if (!circle_item_) {
        circle_item_ = new QGraphicsEllipseItem(0, 0, radius_1_ * 2, radius_2_ * 2);
    }

    if (circle_item_ && !circle_item_->scene()) {
        scene_->addItem(circle_item_);
    }
    circle_item_->setPos(position_.GetX(), position_.GetY());
    circle_item_->setPen(pen_);
    circle_item_->setVisible(is_visible_);
}

void Circle::RemoveFromScene() {
    if (circle_item_ && circle_item_->scene() == scene_) {
        scene_->removeItem(circle_item_);
        delete circle_item_;
        circle_item_ = nullptr;
    }
}
