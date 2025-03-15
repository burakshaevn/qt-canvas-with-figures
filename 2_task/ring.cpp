#include "ring.h"
#include <QDebug>

// Конструктор по умолчанию
Ring::Ring() {
    qDebug() << "Создано кольцо с параметрами по умолчанию.";
}

// Параметризованный конструктор
Ring::Ring(int x, int y, int outer_radius_1, int inner_radius_1, const QPen& pen)
    : outer_circle_(x, y, outer_radius_1, pen)
    , inner_circle_(x, y, inner_radius_1, pen)
{
    qDebug() << "Создано кольцо с центром в (" << x << ',' << y << "), внешним радиусом "
             << outer_radius_1 << " и внутренним радиусом " << inner_radius_1 << '.';
}

// Перемещение кольца
void Ring::MoveTo(int dx, int dy) {
    outer_circle_.MoveTo(dx, dy);
    inner_circle_.MoveTo(dx, dy);
}

// Установка размера
void Ring::SetSize(int w, int h) {
    // Устанавливаем размер внешнего эллипса
    outer_circle_.SetSize(w, h);
    // Внутренний эллипс делаем в два раза меньше
    inner_circle_.SetSize(w / 2, h / 2);
}

// Прорисовка кольца
void Ring::Show(QGraphicsScene* scene) {
    outer_circle_.Show(scene);

    // Обновление позиции внутреннего круга
    int innerX = outer_circle_.GetX() + outer_circle_.GetW() / 2 - inner_circle_.GetW() / 2;
    int innerY = outer_circle_.GetY() + outer_circle_.GetH() / 2 - inner_circle_.GetH() / 2;
    inner_circle_.SetX(innerX);
    inner_circle_.SetY(innerY);

    inner_circle_.Show(scene);
}

// Удаление кольца со сцены
void Ring::RemoveFromScene(QGraphicsScene* scene) {
    outer_circle_.RemoveFromScene(scene);
    inner_circle_.RemoveFromScene(scene);
}

// Получение координаты X центра кольца
int Ring::GetX() const {
    return outer_circle_.GetX();
}

// Получение координаты Y центра кольца
int Ring::GetY() const {
    return outer_circle_.GetY();
}

// Получение ширины внешнего эллипса
int Ring::GetW() const {
    return outer_circle_.GetW();
}

// Получение высоты внешнего эллипса
int Ring::GetH() const {
    return outer_circle_.GetH();
}

// Установка пера для обеих окружностей
void Ring::SetPen(const QPen& pen, const int pen_width) {
    outer_circle_.SetPen(pen, pen_width);
    inner_circle_.SetPen(pen, pen_width);
}

// Получение типа фигуры
FigureType Ring::GetFigureType() const {
    return FigureType::ring_;
}
