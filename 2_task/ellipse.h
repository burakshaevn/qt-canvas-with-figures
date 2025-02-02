#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QPen>

#include "domain.h"

enum class FigureType;

class Ellipse {
public:
    Ellipse();
    Ellipse(int x, int y, int radius_1, int radius_2, const QPen& pen = QPen(QColor("#7b6f5d"), 3));

    // Реализовывать деструктор здесь не нужно, потому что здесь нет динамического выделения памяти
    // ~Ellipse();

    void MoveTo(int dx, int dy);
    void SetSize(const int w, const int h);
    void Show(QGraphicsScene *scene);
    void RemoveFromScene(QGraphicsScene* scene);

    // Методы для получения координат и размеров
    int GetX() const;
    int GetY() const;
    int GetW() const; // Ширина = диаметр по горизонтали
    int GetH() const; // Высота = диаметр по вертикали

    void SetPen(const QPen& pen, const int pen_width);
    FigureType GetFigureType() const;

private:
    int radius_1_;
    int radius_2_;

    int x_ = 0;
    int y_ = 0;
    bool is_visible_ = true;
    QPen pen_ = QPen(QColor("#7b6f5d"), 3);

    QGraphicsEllipseItem* ellipse_item_;
};

#endif // ELLIPSE_H
