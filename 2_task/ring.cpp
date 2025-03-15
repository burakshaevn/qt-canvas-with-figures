#include "ring.h"
#include <QDebug>

// Конструктор по умолчанию
Ring::Ring() {
    qDebug() << "Создано кольцо с параметрами по умолчанию.";
}

// Параметризованный конструктор
Ring::Ring(int x, int y, int outer_radius_1, int outer_radius_2, int inner_radius_1, int inner_radius_2, const QPen& pen)
    : outer_ellipse_(x, y, outer_radius_1, outer_radius_2, pen)
    , inner_ellipse_(x, y, inner_radius_1, inner_radius_2, pen)
{
    qDebug() << "Создано кольцо с центром в (" << x << "," << y << "), внешним радиусом ("
             << outer_radius_1 << "," << outer_radius_2 << ") и внутренним радиусом ("
             << inner_radius_1 << "," << inner_radius_2 << ").";
}

// Перемещение кольца
void Ring::MoveTo(int dx, int dy) {
    outer_ellipse_.MoveTo(dx, dy);
    inner_ellipse_.MoveTo(dx, dy);
}

// Установка размера
void Ring::SetSize(int w, int h) {
    // Устанавливаем размер внешнего эллипса
    outer_ellipse_.SetSize(w, h);
    // Внутренний эллипс делаем в два раза меньше
    inner_ellipse_.SetSize(w / 2, h / 2);
}

// Прорисовка кольца
void Ring::Show(QGraphicsScene* scene) {
    outer_ellipse_.Show(scene);

    // Обновление позиции внутреннего круга
    int innerX = outer_ellipse_.GetX() + outer_ellipse_.GetW() / 2 - inner_ellipse_.GetW() / 2;
    int innerY = outer_ellipse_.GetY() + outer_ellipse_.GetH() / 2 - inner_ellipse_.GetH() / 2;
    inner_ellipse_.SetX(innerX);
    inner_ellipse_.SetY(innerY);

    inner_ellipse_.Show(scene);
}

// Удаление кольца со сцены
void Ring::RemoveFromScene(QGraphicsScene* scene) {
    outer_ellipse_.RemoveFromScene(scene);
    inner_ellipse_.RemoveFromScene(scene);
}

// Получение координаты X центра кольца
int Ring::GetX() const {
    return outer_ellipse_.GetX();
}

// Получение координаты Y центра кольца
int Ring::GetY() const {
    return outer_ellipse_.GetY();
}

// Получение ширины внешнего эллипса
int Ring::GetW() const {
    return outer_ellipse_.GetW();
}

// Получение высоты внешнего эллипса
int Ring::GetH() const {
    return outer_ellipse_.GetH();
}

// Установка пера для обеих окружностей
void Ring::SetPen(const QPen& pen, const int pen_width) {
    outer_ellipse_.SetPen(pen, pen_width);
    inner_ellipse_.SetPen(pen, pen_width);
}

// Получение типа фигуры
FigureType Ring::GetFigureType() const {
    return FigureType::ring_;
}
