#include "line.h"

Line::Line()
    : Figure(nullptr, Point(0, 0), 0, 0)
    , start_(0, 0)
    , end_(0, 0)
    , w_(0)
    , h_(0)
    , line_item_(nullptr)
{}

Line::Line(QGraphicsScene* scene, int x1, int y1, int x2, int y2, const QPen& pen)
    : Figure(scene, Point(x1, y1), x2 - x1, y2 - y1, pen)
    , start_(x1, y1)
    , end_(x2, y2)
    , w_(x2 - x1)
    , h_(y2 - y1)
{
    line_item_ = new QGraphicsLineItem(x1, y1, x2, y2);
    line_item_->setPen(GetPen());
    SetFigureType(FigureType::line_);
}

Line::~Line() = default;

void Line::SetCoords(const int x, const int y) {
    start_.SetX(x);
    start_.SetY(y);
    end_.SetX(x);
    end_.SetY(y);
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

void Line::UpdatePoints(const int dx, const int dy){
    start_.MoveToX(dx);
    start_.MoveToY(dy);
    end_.MoveToX(dx);
    end_.MoveToY(dy);
}

void Line::Show() {
    if (!line_item_) {
        line_item_ = new QGraphicsLineItem(start_.GetX(), start_.GetY(), end_.GetX(), end_.GetY());
        line_item_->setPen(GetPen());
        scene_->addItem(line_item_);
    }
    else if (!line_item_->scene()) {
        scene_->addItem(line_item_);
    }
    else {
        line_item_->setLine(start_.GetX(), start_.GetY(), end_.GetX(), end_.GetY());
    }

    line_item_->setPen(GetPen());
    line_item_->setVisible(is_visible_);
}

void Line::RemoveFromScene() {
    if (line_item_ && scene_->items().contains(line_item_)) {
        scene_->removeItem(line_item_);
        delete line_item_;
        line_item_ = nullptr;
    }
}

int Line::GetX() const {
    return start_.GetX();
}

int Line::GetY() const {
    return start_.GetY();
}
