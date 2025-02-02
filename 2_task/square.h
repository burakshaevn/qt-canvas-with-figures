#ifndef SQUARE_H
#define SQUARE_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QPen>

#include "domain.h"

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
    int x_;
    int y_;
    int size_;
    QPen pen_;
    QGraphicsRectItem* rect_item_;
};

#endif // SQUARE_H
