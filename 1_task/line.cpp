// #include "line.h"

// Line::Line() = default;

// Line::Line(int x1, int y1, int x2, int y2, const QPen& pen)
//     : Figure(x1, y1, x2 - x1, y2 - y1, pen)
//     , x2_(x2)
//     , y2_(y2)
// {
//     line_item_ = new QGraphicsLineItem(x1, y1, x2, y2);
//     line_item_->setPen(pen);
// }

// Line::~Line() = default;

// void Line::MoveTo(const int x, const int y) {
//     int dx = x - x_;
//     int dy = y - y_;
//     x_ = x;
//     y_ = y;
//     x2_ += dx;
//     y2_ += dy;
//     if (line_item_) {
//         line_item_->setLine(x_, y_, x2_, y2_);
//     }
// }

// void Line::SetSize([[maybe_unused]] const int w, [[maybe_unused]] const int h) {
//     // Размер линии не изменяется таким образом. Изменение положения второй точки требует отдельного метода.
// }

// void Line::Show(QGraphicsScene *scene) {
//     if (!line_item_) {
//         line_item_ = new QGraphicsLineItem(x_, y_, x2_, y2_);
//     }
//     else if (line_item_->scene() != scene) {
//         scene->addItem(line_item_);
//         scene->update();
//     }
//     line_item_->setPen(pen_);
//     line_item_->setVisible(is_visible_);
// }

// void Line::RemoveFromScene(QGraphicsScene* scene) {
//     if (line_item_ && scene->items().contains(line_item_)) {
//         scene->removeItem(line_item_);
//         delete line_item_;
//         line_item_ = nullptr;
//     }
// }
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

void Line::SetSize([[maybe_unused]] const int w, [[maybe_unused]] const int h) {
    // Метод пока не используется, так как линия изменяется через координаты.
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
