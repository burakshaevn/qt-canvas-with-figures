#include "rectangle.h"

Rectangle::Rectangle() = default;

Rectangle::Rectangle(int x, int y, int w, int h, const QPen& pen, const FigureType& figure_type)
    : Figure(x, y, w, h, pen, 3, figure_type)
{
    rect_item_ = new QGraphicsRectItem(0, 0, w, h);
    rect_item_->setPen(pen);
}

Rectangle::~Rectangle() = default;

void Rectangle::MoveTo(const int dx, const int dy) {
    x_ += dx;
    y_ += dy;
    if (rect_item_) {
        rect_item_->setPos(x_, y_);
    }
}

void Rectangle::SetSize(const int w, const int h) {
    w_ = w;
    h_ = h;
    if (rect_item_) {
        rect_item_->setRect(0, 0, w_, h_);
    }
}

void Rectangle::Show(QGraphicsScene *scene) {
    if (!rect_item_) {
        rect_item_ = new QGraphicsRectItem(0, 0, w_, h_);
    }
    if (rect_item_ && !rect_item_->scene()) {
        scene->addItem(rect_item_);
    }
    rect_item_->setPos(x_, y_);
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