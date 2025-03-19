#include "rectangle.h"

Rectangle::Rectangle() = default;

Rectangle::Rectangle(int x, int y, int w, int h, const QPen& pen, const FigureType& figure_type)
    : Figure({x, y}, w, h, pen, 3, figure_type)
{
    rect_item_ = new QGraphicsRectItem(0, 0, w, h);
    rect_item_->setPen(pen);
    SetFigureType(FigureType::rectangle_);
}

Rectangle::~Rectangle() = default;

void Rectangle::MoveTo(const int dx, const int dy) {
    position_.MoveToX(dx);
    position_.MoveToY(dy);
    if (rect_item_) {
        rect_item_->setPos(position_.GetX(), position_.GetY());
    }
}

void Rectangle::SetSize(const int w, const int h) {
    w_ = w;
    h_ = h;
    if (rect_item_) {
        rect_item_->setRect(0, 0, w_, h_);
    }
}

void Rectangle::Show(QGraphicsScene *scene) {
    if (!rect_item_) {
        rect_item_ = new QGraphicsRectItem(0, 0, w_, h_);
    }
    if (rect_item_ && !rect_item_->scene()) {
        scene->addItem(rect_item_);
    }
    rect_item_->setPos(position_.GetX(), position_.GetY());
    rect_item_->setPen(pen_);
    rect_item_->setVisible(is_visible_);
}

void Rectangle::RemoveFromScene(QGraphicsScene* scene) {
    if (rect_item_ && scene->items().contains(rect_item_)) {
        scene->removeItem(rect_item_);
        delete rect_item_;
        rect_item_ = nullptr;
    }
}

void Rectangle::Rotate(const int degrees, QGraphicsScene* scene) {
    if (!rect_item_) {
        return;
    }

    // Сохраняем текущий угол поворота для возможного восстановления
    qreal previous_rotation = rect_item_->rotation();

    // Применяем поворот
    rect_item_->setRotation(previous_rotation + degrees);

    // Проверяем, не выходит ли объект за границы
    QRectF global_bounds = rect_item_->mapToScene(rect_item_->boundingRect()).boundingRect();
    QRectF scene_bounds = scene->sceneRect();

    if (!scene_bounds.contains(global_bounds)) {
        // Если выходит за границы, откатываем поворот назад
        rect_item_->setRotation(previous_rotation);
    }
}

void Rectangle::SetVisible(bool visible) {
    is_visible_ = visible;
}
bool Rectangle::GetVisible() const {
    return is_visible_;
}

void Rectangle::SetCoords(const int x, const int y){
    position_.SetX(x);
    position_.SetY(y);
}
int Rectangle::GetX() const{
    return position_.GetX();
}
int Rectangle::GetY() const{
    return position_.GetY();
}
int Rectangle::GetW() const{
    return w_;
}
int Rectangle::GetH() const{
    return h_;
}

void Rectangle::SetPen(const QPen& pen, const int pen_width) {
    pen_ = pen;
    pen_.setWidth(pen_width);
}
QPen Rectangle::GetPen() const {
    return pen_;
}
