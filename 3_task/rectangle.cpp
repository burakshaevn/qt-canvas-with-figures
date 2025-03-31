#include "rectangle.h"

Rectangle::Rectangle() = default;

Rectangle::Rectangle(int x, int y, int w, int h, const QPen& pen, const FigureType& figure_type)
    : Quadrilateral(x, y, w, h, pen, figure_type)
{
    rect_item_ = new QGraphicsRectItem(0, 0, w, h);
    rect_item_->setPen(pen);
    SetFigureType(FigureType::rectangle_);
}

Rectangle::~Rectangle() {
    if (rect_item_) {
        delete rect_item_;
        rect_item_ = nullptr;
    }
}

void Rectangle::Show(QGraphicsScene* scene) {
    if (!rect_item_) {
        rect_item_ = new QGraphicsRectItem(0, 0, w_, h_);
    }
    if (rect_item_ && !rect_item_->scene()) {
        scene->addItem(rect_item_);
    }
    rect_item_->setPos(position_.GetX(), position_.GetY());
    rect_item_->setPen(pen_);
    rect_item_->setVisible(is_visible_);
}

void Rectangle::RemoveFromScene(QGraphicsScene* scene) {
    if (rect_item_ && scene->items().contains(rect_item_)) {
        scene->removeItem(rect_item_);
        delete rect_item_;
        rect_item_ = nullptr;
    }
}

void Rectangle::Rotate(const int degrees, QGraphicsScene* scene) {
    if (!rect_item_) return;

    qreal previous_rotation = rect_item_->rotation();
    rect_item_->setRotation(previous_rotation + degrees);

    QRectF global_bounds = rect_item_->mapToScene(rect_item_->boundingRect()).boundingRect();
    QRectF scene_bounds = scene->sceneRect();

    if (!scene_bounds.contains(global_bounds)) {
        rect_item_->setRotation(previous_rotation);
    }
}
