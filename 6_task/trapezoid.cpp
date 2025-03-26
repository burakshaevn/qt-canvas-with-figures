#include "trapezoid.h"

Trapezoid::Trapezoid()
    : Rectangle()
    , base1_(0)
    , base2_(0)
    , height_(0)
    , trapezoid_item_(nullptr)
{}

Trapezoid::Trapezoid(QGraphicsScene* scene, int x, int y, int base1, int base2, int height, const QPen& pen, const FigureType& figure_type)
    : Rectangle(scene, x, y, base1, height, pen, figure_type), base1_(base1), base2_(base2), height_(height) {
    trapezoid_item_ = new QGraphicsPolygonItem();
    SetFigureType(FigureType::trapezoid_);
    SetSize(base1, base2, height);
}

Trapezoid::~Trapezoid() = default;

void Trapezoid::SetSize(const int base1, const int base2, const int height) {
    base1_ = base1;
    base2_ = base2;
    height_ = height;

    // Создаем полигон для трапеции
    QPolygonF polygon;
    int offset = (base1 - base2) / 2; // Смещение для второго основания

    polygon << QPointF(0, 0)                     // Левый верхний угол
            << QPointF(base1, 0)                 // Правый верхний угол
            << QPointF(base1 - offset, height)   // Правый нижний угол
            << QPointF(offset, height);          // Левый нижний угол

    if (trapezoid_item_) {
        trapezoid_item_->setPolygon(polygon);
    }
}

void Trapezoid::Show() {
    if (!trapezoid_item_) {
        trapezoid_item_ = new QGraphicsPolygonItem();
        SetSize(base1_, base2_, height_); // Инициализация формы трапеции
    }
    if (trapezoid_item_ && !trapezoid_item_->scene()) {
        scene_->addItem(trapezoid_item_);
    }
    trapezoid_item_->setPos(position_.GetX(), position_.GetY());
    trapezoid_item_->setPen(pen_);
    trapezoid_item_->setVisible(is_visible_);
}

void Trapezoid::RemoveFromScene() {
    if (trapezoid_item_ && scene_->items().contains(trapezoid_item_)) {
        scene_->removeItem(trapezoid_item_);
        delete trapezoid_item_;
        trapezoid_item_ = nullptr;
    }
}

void Trapezoid::Rotate(const int degrees) {
    if (!trapezoid_item_) {
        return;
    }

    // Сохраняем текущий угол поворота для возможного восстановления
    qreal previous_rotation = trapezoid_item_->rotation();

    // Применяем поворот
    trapezoid_item_->setRotation(previous_rotation + degrees);

    // Проверяем, не выходит ли объект за границы
    QRectF global_bounds = trapezoid_item_->mapToScene(trapezoid_item_->boundingRect()).boundingRect();
    QRectF scene_bounds = scene_->sceneRect();

    if (!scene_bounds.contains(global_bounds)) {
        // Если выходит за границы, откатываем поворот назад
        trapezoid_item_->setRotation(previous_rotation);
    }
}
