#include "rectangle.h"

Rectangle::Rectangle() = default;

Rectangle::Rectangle(QGraphicsScene* scene, int x, int y, int w, int h, const QPen& pen, const FigureType& figure_type)
    : Figure(scene, {x, y}, w, h, pen, 3, figure_type)
{
    rect_item_ = new QGraphicsRectItem(0, 0, w, h);
    rect_item_->setPen(pen);
    SetFigureType(FigureType::rectangle_);
}

Rectangle::~Rectangle() = default;

// void Rectangle::MoveTo(const int dx, const int dy) {
//     position_.MoveToX(dx);
//     position_.MoveToY(dy);
//     if (rect_item_) {
//         rect_item_->setPos(position_.GetX(), position_.GetY());
//     }
// }

void Rectangle::SetSize(const int w, const int h) {
    w_ = w;
    h_ = h;
    if (rect_item_) {
        rect_item_->setRect(0, 0, w_, h_);
    }
}

void Rectangle::Show() {
    if (!rect_item_) {
        rect_item_ = new QGraphicsRectItem(0, 0, w_, h_);
    }
    if (rect_item_ && !rect_item_->scene()) {
        scene_->addItem(rect_item_);
    }
    rect_item_->setPos(position_.GetX(), position_.GetY());
    rect_item_->setPen(pen_);
    rect_item_->setVisible(is_visible_);
}

void Rectangle::RemoveFromScene() {
    if (rect_item_ && scene_->items().contains(rect_item_)) {
        scene_->removeItem(rect_item_);
        delete rect_item_;
        rect_item_ = nullptr;
    }
}

void Rectangle::Rotate(const int degrees) {
    if (!rect_item_) {
        return;
    }

    // Сохраняем текущий угол поворота для возможного восстановления
    qreal previous_rotation = rect_item_->rotation();

    // Применяем поворот
    rect_item_->setRotation(previous_rotation + degrees);

    // Проверяем, не выходит ли объект за границы
    QRectF global_bounds = rect_item_->mapToScene(rect_item_->boundingRect()).boundingRect();
    QRectF scene_bounds = scene_->sceneRect();

    if (!scene_bounds.contains(global_bounds)) {
        // Если выходит за границы, откатываем поворот назад
        rect_item_->setRotation(previous_rotation);
    }
}
