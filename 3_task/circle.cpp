#include "circle.h"

Circle::Circle() = default;

Circle::Circle(int x, int y, int radius_1, int radius_2, const QPen& pen, const FigureType& figure_type)
    : Figure({x, y}, radius_1 * 2, radius_2 * 2, pen, 3, figure_type)
    , radius_1_(radius_1)
    , radius_2_(radius_2)
{
    circle_item_ = new QGraphicsEllipseItem(0, 0, radius_1_ * 2, radius_2_ * 2);
    circle_item_->setPen(pen);
    SetFigureType(FigureType::circle_);
    qDebug() << "Создана окружность с центром в (" << x << ',' << y << ") и радиусом " << radius_1 << " и внутренним радиусом " << radius_2 << '.';
}

Circle::~Circle() = default;

void Circle::MoveTo(const int dx, const int dy) {
    position_.MoveToX(dx);
    position_.MoveToY(dy);
    if (circle_item_) {
        circle_item_->setPos(position_.GetX() - radius_1_, position_.GetY() - radius_2_);
    }
}

void Circle::Show(QGraphicsScene *scene) {
    if (!circle_item_) {
        circle_item_ = new QGraphicsEllipseItem(0, 0, radius_1_ * 2, radius_2_ * 2);
    }
    if (circle_item_ && !circle_item_->scene()) {
        scene->addItem(circle_item_);
    }
    circle_item_->setPos(position_.GetX(), position_.GetY());
    circle_item_->setPen(pen_);
    circle_item_->setVisible(is_visible_);
}

void Circle::SetSize(const int w, const int h) {
    radius_1_ = radius_2_ = w / 2;
    if (circle_item_) {
        circle_item_->setRect(0, 0, radius_1_ * 2, radius_1_ * 2);
    }
}

void Circle::RemoveFromScene(QGraphicsScene *scene) {
    if (circle_item_ && circle_item_->scene() == scene) {
        scene->removeItem(circle_item_);
        delete circle_item_;
        circle_item_ = nullptr;
    }
}

void Circle::SetVisible(bool visible) {
    is_visible_ = visible;
}
bool Circle::GetVisible() const {
    return is_visible_;
}

void Circle::SetCoords(const int x, const int y){
    position_.SetX(x);
    position_.SetY(y);
}
int Circle::GetX() const{
    return position_.GetX();
}
int Circle::GetY() const{
    return position_.GetY();
}
int Circle::GetW() const{
    return w_;
}
int Circle::GetH() const{
    return h_;
}

void Circle::SetPen(const QPen& pen, const int pen_width) {
    pen_ = pen;
    pen_.setWidth(pen_width);
}
QPen Circle::GetPen() const {
    return pen_;
}
