#include "square.h"

Square::Square() = default;

Square::Square(int x, int y, int w, const QPen& pen)
    : Quadrilateral(x, y, w, w, pen, FigureType::square_)
{
    rect_item_ = new QGraphicsRectItem(0, 0, w, w);
    rect_item_->setPen(pen);
    SetFigureType(FigureType::square_);
}

Square::~Square() = default;

void Square::SetSize(const int w, const int h) {
    w_ = w;
    h_ = h;
    if (rect_item_) {
        rect_item_->setRect(0, 0, w_, h_);
    }
}

void Square::Show(QGraphicsScene *scene) {
    if (!rect_item_) {
        rect_item_ = new QGraphicsRectItem(0, 0, w_, w_);
    }
    if (rect_item_ && !rect_item_->scene()) {
        scene->addItem(rect_item_);
    }
    rect_item_->setPos(position_.GetX(), position_.GetY());
    rect_item_->setPen(pen_);
    rect_item_->setVisible(is_visible_);
}

void Square::RemoveFromScene(QGraphicsScene* scene) {
    if (rect_item_ && scene->items().contains(rect_item_)) {
        scene->removeItem(rect_item_);
        delete rect_item_;
        rect_item_ = nullptr;
    }
}

void Square::SetVisible(bool visible) {
    is_visible_ = visible;
}
bool Square::GetVisible() const {
    return is_visible_;
}
