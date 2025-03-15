#include "circle.h"

Circle::Circle()
    : position_(0, 0)
    , radius_(0)
    , is_visible_(true)
    , Circle_item_(nullptr)
{}

Circle::Circle(int x, int y, int radius_1, const QPen& pen)
    : position_(x, y)
    , radius_(radius_1)
    , pen_(pen)
    , is_visible_(true)
{
    Circle_item_ = new QGraphicsEllipseItem(0, 0, radius_ * 2, radius_ * 2);
    Circle_item_->setPen(pen_);
    qDebug() << "Создана окружность с центром в (" << x << ',' << y << ')';
}

void Circle::MoveTo(int dx, int dy) {
    position_.MoveToX(dx);
    position_.MoveToY(dy);
    if (Circle_item_) {
        Circle_item_->setPos(position_.GetX() - radius_, position_.GetY() - radius_);
    }
}

void Circle::SetSize(const int w, const int h) {
    radius_ = w / 2;
    if (Circle_item_) {
        Circle_item_->setRect(0, 0, radius_ * 2, radius_ * 2);
    }
}

void Circle::Show(QGraphicsScene *scene) {
    if (!scene) {
        return;
    }

    if (!Circle_item_) {
        Circle_item_ = new QGraphicsEllipseItem(0, 0, radius_ * 2, radius_ * 2);
    }

    if (Circle_item_ && !Circle_item_->scene()) {
        scene->addItem(Circle_item_);
    }

    if (Circle_item_) {
        Circle_item_->setPos(position_.GetX(), position_.GetY());
        Circle_item_->setPen(pen_);
        Circle_item_->setVisible(is_visible_);
    }
}

void Circle::RemoveFromScene(QGraphicsScene *scene) {
    if (Circle_item_ && scene) {
        scene->removeItem(Circle_item_);
    }
}

void Circle::SetX(const int x){
    position_.SetX(x);
}
void Circle::SetY(const int y){
    position_.SetY(y);
}
void Circle::SetW(const int w){
    radius_ = w;
}
void Circle::SetH(const int h){
    SetW(h);
}

int Circle::GetX() const {
    return position_.GetX();
}

int Circle::GetY() const {
    return position_.GetY();
}

int Circle::GetW() const {
    return radius_ * 2;
}

int Circle::GetH() const {
    return radius_ * 2;
}

void Circle::SetPen(const QPen& pen, const int pen_width) {
    pen_ = pen;
    pen_.setWidth(pen_width);
}
FigureType Circle::GetFigureType() const {
    return FigureType::circle_;
}
