#include "rectangle.h"

Rectangle::Rectangle()
    : position_(0, 0)
    , w_(0)
    , h_(0)
    , pen_(QPen(QColor("#7b6f5d"), 3))
    , rect_item_(nullptr)
{}

Rectangle::Rectangle(int x, int y, int w, int h, const QPen& pen)
    : position_(x, y)
    , w_(w)
    , h_(h)
    , pen_(pen)
    , rect_item_(nullptr)
{}

void Rectangle::MoveTo(int dx, int dy) {
    position_.MoveToX(dx);
    position_.MoveToY(dy);
    if (rect_item_) {
        rect_item_->setPos(position_.GetX(), position_.GetY());
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
    rect_item_->setPos(position_.GetX(), position_.GetY());
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
    return position_.GetX();
}

int Rectangle::GetY() const {
    return position_.GetY();
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
