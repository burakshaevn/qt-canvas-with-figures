#include "rectangle.h"

Rectangle::Rectangle() = default;

Rectangle::Rectangle(int x, int y, int w, int h, const QPen& pen)
    : x_(x)
    , y_(y)
    , w_(w)
    , h_(h)
    , pen_(pen)
    , rect_item_(nullptr)
{}

void Rectangle::MoveTo(int dx, int dy) {
    x_ += dx;
    y_ += dy;
    if (rect_item_) {
        rect_item_->setPos(x_, y_);
    }
}

void Rectangle::SetSize(int w, int h) {
    w_ = w;
    h_ = h;
    if (rect_item_) {
        rect_item_->setRect(0, 0, w_, h_);
    }
}

void Rectangle::Show(QGraphicsScene* scene) {
    if (!rect_item_) {
        rect_item_ = new QGraphicsRectItem(0, 0, w_, h_);
    }
    if (rect_item_ && !rect_item_->scene()) {
        scene->addItem(rect_item_);
    }
    rect_item_->setPos(x_, y_);
    rect_item_->setPen(pen_);
}

void Rectangle::RemoveFromScene(QGraphicsScene* scene) {
    if (rect_item_ && scene->items().contains(rect_item_)) {
        scene->removeItem(rect_item_);
        delete rect_item_;
        rect_item_ = nullptr;
    }
}

int Rectangle::GetX() const {
    return x_;
}
int Rectangle::GetY() const {
    return y_;
}
int Rectangle::GetW() const {
    return w_;
}
int Rectangle::GetH() const {
    return h_;
}

void Rectangle::SetPen(const QPen& pen, const int pen_width) {
    pen_ = pen;
    pen_.setWidth(pen_width);
}
FigureType Rectangle::GetFigureType() const {
    return FigureType::rectangle_;
}
