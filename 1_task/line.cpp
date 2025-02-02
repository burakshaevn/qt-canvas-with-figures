#include "line.h"

Line::Line() = default;

Line::Line(int x1, int y1, int x2, int y2, const QPen& pen)
    : x_(x1)
    , y_(y1)
    , x2_(x2)
    , y2_(y2)
    , w_(x2 - x1)
    , h_(y2 - y1)
{
    line_item_ = new QGraphicsLineItem(x1, y1, x2, y2);
    line_item_->setPen(pen);
}

void Line::MoveTo(const int dx, const int dy) {
    x_ += dx;
    y_ += dy;
    x2_ += dx;
    y2_ += dy;

    if (line_item_) {
        line_item_->setLine(x_, y_, x2_, y2_);
    }
}

void Line::SetCoords(const int x, const int y){
    x_ = x;
    y_ = y;
}

void Line::SetSize(const int w, const int h) {
    x2_ = x_ + w;
    y2_ = y_ + h;
    w_ = w;
    h_ = h;

    if (line_item_) {
        line_item_->setLine(x_, y_, x2_, y2_);
    }
}

int Line::GetX() const{
    return x_;
}
int Line::GetY() const{
    return y_;
}
int Line::GetW() const {
    return w_;
}
int Line::GetH() const {
    return h_;
}

void Line::Show(QGraphicsScene *scene) {
    // Если line_item_ еще не создан, создаем его
    if (!line_item_) {
        line_item_ = new QGraphicsLineItem(x_, y_, x2_, y2_);
        line_item_->setPen(pen_);
        scene->addItem(line_item_);
    }
    // Если создан, но не добавлен на сцену, добавляем его
    else if (!line_item_->scene()) {
        scene->addItem(line_item_);
    }

    // Устанавливаем параметры видимости и пера
    line_item_->setPen(pen_);
    line_item_->setVisible(is_visible_);
}

void Line::RemoveFromScene(QGraphicsScene* scene) {
    // Удаляем элемент из сцены и освобождаем память
    if (line_item_ && scene->items().contains(line_item_)) {
        scene->removeItem(line_item_);
        delete line_item_;
        line_item_ = nullptr;
    }
}

void Line::SetVisible(bool visible) {
    is_visible_ = visible;
}
bool Line::GetVisible() const {
    return is_visible_;
}

void Line::SetPen(const QPen& pen, const int pen_width) {
    pen_ = pen;
    pen_.setWidth(pen_width);
}
QPen Line::GetPen() const {
    return pen_;
}

FigureType Line::GetFigureType() const {
    return FigureType::line_;
}
