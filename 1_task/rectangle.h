#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QPen>

#include "domain.h"
#include "point.h"

class Rectangle {
public:
    Rectangle();
    Rectangle(int x = 0, int y = 0, int width = 0, int height = 0, const QPen& pen = QPen(QColor("#7b6f5d"), 3));

    // Реализовывать деструктор здесь не нужно, потому что здесь нет динамического выделения памяти
    // ~Rectangle();

    void MoveTo(int dx, int dy);
    void SetSize(int w, int h);
    void Show(QGraphicsScene* scene);
    void RemoveFromScene(QGraphicsScene* scene);
    int GetX() const;
    int GetY() const;
    int GetW() const;
    int GetH() const;

    void SetPen(const QPen& pen, const int pen_width);
    FigureType GetFigureType() const;

private:
    Point position_; // Позиция прямоугольника
    int w_;          // Ширина
    int h_;          // Высота
    QPen pen_;       // Перо для отрисовки
    QGraphicsRectItem* rect_item_; // Графический элемент
};

#endif // RECTANGLE_H
