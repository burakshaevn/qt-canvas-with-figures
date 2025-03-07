#include "square.h"

Square::Square()
    : position_(0, 0)
    , size_(0)
    , pen_(QPen(QColor("#7b6f5d"), 3))
    , rect_item_(nullptr)
{}

Square::Square(int x, int y, int size, const QPen& pen)
    : position_(x, y)
    , size_(size)
    , pen_(pen)
    , rect_item_(nullptr)
{
    rect_item_ = new QGraphicsRectItem(0, 0, size, size);
    rect_item_->setPen(pen);
}

void Square::MoveTo(int dx, int dy) {
    position_.MoveToX(dx);
    position_.MoveToY(dy);
    if (rect_item_) {
        rect_item_->setPos(position_.GetX(), position_.GetY());
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
    rect_item_->setPos(position_.GetX(), position_.GetY());
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
    return position_.GetX();
}

int Square::GetY() const {
    return position_.GetY();
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
