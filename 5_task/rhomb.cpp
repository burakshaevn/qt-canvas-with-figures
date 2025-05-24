#include "rhomb.h"

Rhomb::Rhomb()
    : Quadrilateral()
    , side_(0)
    , height_(0)
    , rhomb_item_(nullptr)
{}

Rhomb::Rhomb(QGraphicsScene* scene, int x, int y, int side, int height, const QPen& pen, const FigureType& figure_type)
    : Quadrilateral(scene, x, y, side, height, pen, figure_type), side_(side), height_(height) {
    rhomb_item_ = new QGraphicsPolygonItem();
    SetFigureType(FigureType::rhomb_);
    SetSize(side, height);
}

Rhomb::~Rhomb() {
    if (rhomb_item_) {
        delete rhomb_item_;
    }
}

void Rhomb::SetSize(const int side, const int height) {
    side_ = side;
    height_ = height;

    // Создаем полигон для ромба
    QPolygonF polygon;
    int half_width = side / 2; // Половина ширины ромба

    polygon << QPointF(half_width, 0)                     // Верхняя точка
            << QPointF(side, height / 2)                 // Правая точка
            << QPointF(half_width, height)               // Нижняя точка
            << QPointF(0, height / 2);                   // Левая точка

    if (rhomb_item_) {
        rhomb_item_->setPolygon(polygon);
    }
}

void Rhomb::Show() {
    if (!rhomb_item_) {
        rhomb_item_ = new QGraphicsPolygonItem();
        SetSize(side_, height_); // Инициализация формы ромба
    }
    if (rhomb_item_ && !rhomb_item_->scene()) {
        scene_->addItem(rhomb_item_);
    }
    rhomb_item_->setPos(position_.GetX(), position_.GetY());
    rhomb_item_->setPen(pen_);
    rhomb_item_->setVisible(is_visible_);
}

void Rhomb::RemoveFromScene() {
    if (rhomb_item_ && scene_->items().contains(rhomb_item_)) {
        scene_->removeItem(rhomb_item_);
        delete rhomb_item_;
        rhomb_item_ = nullptr;
    }
}

void Rhomb::RotateRhomb(const int degrees) {
    if (!rhomb_item_) {
        return;
    }

    // Сохраняем текущий угол поворота для возможного восстановления
    qreal previous_rotation = rhomb_item_->rotation();

    // Применяем поворот
    rhomb_item_->setRotation(previous_rotation + degrees);

    // Проверяем, не выходит ли объект за границы
    QRectF global_bounds = rhomb_item_->mapToScene(rhomb_item_->boundingRect()).boundingRect();
    QRectF scene_bounds = scene_->sceneRect();

    if (!scene_bounds.contains(global_bounds)) {
        // Если выходит за границы, откатываем поворот назад
        rhomb_item_->setRotation(previous_rotation);
    }
}
