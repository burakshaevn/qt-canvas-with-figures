#include "square.h"

Square::Square() : x_(0), y_(0), size_(0), rect_item_(nullptr) {}

Square::Square(int x, int y, int size, const QPen& pen)
    : x_(x), y_(y), size_(size), pen_(pen), rect_item_(nullptr) {
    rect_item_ = new QGraphicsRectItem(0, 0, size, size);
    rect_item_->setPen(pen);
}
void Square::MoveTo(int dx, int dy) {
    x_ += dx;
    y_ += dy;
    if (rect_item_) {
        rect_item_->setPos(x_, y_);
    }
}

void Square::SetSize(int w, int h) {
    // Квадрат имеет одинаковые стороны, поэтому берем минимальное значение
    size_ = std::min(w, h);
    if (rect_item_) {
        rect_item_->setRect(0, 0, size_, size_);
    }
}

void Square::Show(QGraphicsScene* scene) {
    if (!rect_item_) {
        rect_item_ = new QGraphicsRectItem(0, 0, size_, size_);
    }
    if (rect_item_ && !rect_item_->scene()) {
        scene->addItem(rect_item_);
    }
    rect_item_->setPos(x_, y_);
    rect_item_->setPen(pen_);
}

void Square::RemoveFromScene(QGraphicsScene* scene) {
    if (rect_item_ && scene->items().contains(rect_item_)) {
        scene->removeItem(rect_item_);
        delete rect_item_;
        rect_item_ = nullptr;
    }
}

int Square::GetX() const {
    return x_;
}
int Square::GetY() const {
    return y_;
}
int Square::GetSize() const {
    return size_;
}
int Square::GetW() const {
    return size_;
}
int Square::GetH() const {
    return size_;
}

void Square::SetPen(const QPen& pen, const int pen_width) {
    pen_ = pen;
    pen_.setWidth(pen_width);
    if (rect_item_) {
        rect_item_->setPen(pen_);
    }
}

FigureType Square::GetFigureType() const {
    return FigureType::square_;
}
