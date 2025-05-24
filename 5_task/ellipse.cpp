#include "ellipse.h"

Ellipse::Ellipse() = default;

Ellipse::Ellipse(QGraphicsScene* scene, int x, int y, int radius_1, int radius_2, const QPen& pen)
    : Circle(scene, x, y, radius_1, radius_2, pen, FigureType::ellipse_)
{
    // Устанавливаем только один радиус в оба радиуса, так как это круг (один диаметр)
    radius_1_ = radius_1;
    radius_2_ = radius_2;
    if (!circle_item_) {
        circle_item_ = new QGraphicsEllipseItem(0, 0, radius_1 * 2, radius_2 * 2);
    }
    circle_item_->setPen(pen);
    SetFigureType(FigureType::ellipse_);
}

Ellipse::~Ellipse() = default;

void Ellipse::SetSize(const int w, [[maybe_unused]] const int h) {
    w_ = radius_1_ = w / 2;
    h_ = radius_2_ = h / 2;
    if (circle_item_) {
        circle_item_->setRect(circle_item_->rect().x(), circle_item_->rect().y(), radius_1_ * 2, radius_2_ * 2);
    }
}

void Ellipse::RotateEllipse(int degrees) {
    if (!circle_item_) {
        return;
    }

    // Сохраняем текущий угол поворота для возможного восстановления
    qreal previous_rotation = circle_item_->rotation();

    // Применяем поворот
    circle_item_->setRotation(previous_rotation + degrees);

    // Проверяем, не выходит ли объект за границы
    QRectF global_bounds = circle_item_->mapToScene(circle_item_->boundingRect()).boundingRect();
    QRectF scene_bounds = scene_->sceneRect();

    if (!scene_bounds.contains(global_bounds)) {
        // Если выходит за границы, откатываем поворот назад
        circle_item_->setRotation(previous_rotation);
    }
}
