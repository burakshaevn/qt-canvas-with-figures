#include "line.h"

Line::Line()
    : Figure(Point(0, 0), 0, 0)
    , start_(0, 0)
    , end_(0, 0)
    , w_(0)
    , h_(0)
    , is_visible_(true)
    , line_item_(nullptr)
{}

Line::Line(int x1, int y1, int x2, int y2, const QPen& pen)
    : Figure(Point(x1, y1), x2 - x1, y2 - y1, pen)
    , start_(x1, y1)
    , end_(x2, y2)
    , w_(x2 - x1)
    , h_(y2 - y1)
    , is_visible_(true)
{
    line_item_ = new QGraphicsLineItem(x1, y1, x2, y2);
    line_item_->setPen(GetPen());
    SetFigureType(FigureType::line_);
}

void Line::MoveTo(const int dx, const int dy) {
    start_.MoveToX(dx);
    start_.MoveToY(dy);
    end_.MoveToX(dx);
    end_.MoveToY(dy);

    if (line_item_) {
        line_item_->setLine(start_.GetX(), start_.GetY(), end_.GetX(), end_.GetY());
    }
}

void Line::SetCoords(const int x, const int y) {
    start_.SetX(x);
    start_.SetY(y);
}

void Line::SetSize(const int w, const int h) {
    end_.SetX(start_.GetX() + w);
    end_.SetY(start_.GetY() + h);
    w_ = w;
    h_ = h;

    if (line_item_) {
        line_item_->setLine(start_.GetX(), start_.GetY(), end_.GetX(), end_.GetY());
    }
}

void Line::Show(QGraphicsScene *scene) {
    if (!line_item_) {
        line_item_ = new QGraphicsLineItem(start_.GetX(), start_.GetY(), end_.GetX(), end_.GetY());
        line_item_->setPen(pen_);
        scene->addItem(line_item_);
    } else if (!line_item_->scene()) {
        scene->addItem(line_item_);
    }

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

int Line::GetX() const {
    return start_.GetX();
}

int Line::GetY() const {
    return start_.GetY();
}

int Line::GetW() const {
    return w_;
}

int Line::GetH() const {
    return h_;
}

void Line::SetPen(const QPen& pen, const int pen_width) {
    pen_ = pen;
    pen_.setWidth(pen_width);
}
QPen Line::GetPen() const {
    return pen_;
}
