#ifndef SQUARE_H
#define SQUARE_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QPen>

#include "domain.h"
#include "point.h"

class Square {
public:
    Square();
    Square(int x, int y, int size, const QPen& pen = QPen(QColor("#7b6f5d"), 3));

    // Реализовывать деструктор здесь не нужно, потому что здесь нет динамического выделения памяти
    // ~Square();

    void MoveTo(int dx, int dy);
    void SetSize(int size, int h);
    void Show(QGraphicsScene* scene);
    void RemoveFromScene(QGraphicsScene* scene);
    int GetX() const;
    int GetY() const;
    int GetSize() const;
    int GetW() const;
    int GetH() const;
    void SetPen(const QPen& pen, const int pen_width);

    FigureType GetFigureType() const;

private:
    Point position_; // Позиция квадрата
    int size_;       // Размер стороны квадрата
    QPen pen_;       // Перо для отрисовки
    QGraphicsRectItem* rect_item_; // Графический элемент
};

#endif // SQUARE_H
