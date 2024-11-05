#include "square.h"

Square::Square() = default;

Square::Square(int x, int y, int w, const QPen& pen)
    : Rectangle(x, y, w, w, pen, FigureType::square_)
{
    rect_item_ = new QGraphicsRectItem(0, 0, w, w);
    rect_item_->setPen(pen);
}

Square::~Square() = default;

void Square::SetSize(const int w, const int h) {
    w_ = w;
    h_ = h;
    if (rect_item_) {
        rect_item_->setRect(0, 0, w_, h_);
    }
}
