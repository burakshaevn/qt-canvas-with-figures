#include "line.h"

Line::Line() = default;

Line::Line(int x1, int y1, int x2, int y2, const QPen& pen)
    : Figure(x1, y1, x2 - x1, y2 - y1, pen, 3, FigureType::line_)
    , x2_(x2)
    , y2_(y2)
{
    line_item_ = new QGraphicsLineItem(x1, y1, x2, y2);
    line_item_->setPen(pen);
}

Line::~Line() {
    delete line_item_;
}

void Line::MoveTo(const int dx, const int dy) {
    // Смещаем начало и конец линии
    x_ += dx;
    y_ += dy;
    x2_ += dx;
    y2_ += dy;

    // Обновляем позицию линии на сцене, если line_item_ не равен nullptr
    if (line_item_) {
        line_item_->setLine(x_, y_, x2_, y2_);
    }
}

void Line::SetSize(const int w, const int h) {
    // Изменяем конечные координаты линии в зависимости от новых ширины и высоты
    x2_ = x_ + w;
    y2_ = y_ + h;

    // Обновляем позицию линии на сцене
    if (line_item_) {
        line_item_->setLine(x_, y_, x2_, y2_);
    }
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
