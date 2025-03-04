#ifndef RING_H
#define RING_H

#include "ellipse.h"
#include <QGraphicsScene>
#include <QPen>

class Ring {
public:
    // Конструкторы
    Ring();
    Ring(int x, int y, int outer_radius_1, int outer_radius_2, int inner_radius_1, int inner_radius_2, const QPen& pen = QPen(QColor("#7b6f5d"), 3));

    // Методы
    void MoveTo(int dx, int dy); // Перемещение кольца
    void SetSize(int w, int h);  // Установка размера
    void Show(QGraphicsScene* scene); // Прорисовка кольца
    void RemoveFromScene(QGraphicsScene* scene); // Удаление кольца со сцены

    // Методы для получения координат и размеров
    int GetX() const;
    int GetY() const;
    int GetW() const; // Ширина внешнего эллипса
    int GetH() const; // Высота внешнего эллипса

    void SetPen(const QPen& pen, const int pen_width); // Установка пера для обеих окружностей
    FigureType GetFigureType() const; // Получение типа фигуры

private:
    Ellipse outer_ellipse_; // Внешняя окружность
    Ellipse inner_ellipse_; // Внутренняя окружность
};

#endif // RING_H
