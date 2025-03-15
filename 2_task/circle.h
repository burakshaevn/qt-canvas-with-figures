#ifndef CIRCLE_H
#define CIRCLE_H

#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QPen>

#include "domain.h"
#include "point.h"

enum class FigureType;

class Circle {
public:
    Circle();
    Circle(int x, int y, int radius_, const QPen& pen = QPen(QColor("#7b6f5d"), 3));

    void MoveTo(int dx, int dy);
    void SetSize(const int w, const int h);
    void Show(QGraphicsScene *scene);
    void RemoveFromScene(QGraphicsScene* scene);

    // Методы для обновления координат и размеров
    void SetX(const int);
    void SetY(const int);
    void SetW(const int);
    void SetH(const int);

    // Методы для получения координат и размеров
    int GetX() const;
    int GetY() const;
    int GetW() const;
    int GetH() const;

    void SetPen(const QPen& pen, const int pen_width);
    FigureType GetFigureType() const;

private:
    int radius_;

    Point position_;
    bool is_visible_ = true;
    QPen pen_ = QPen(QColor("#7b6f5d"), 3);

    QGraphicsEllipseItem* Circle_item_;
};

#endif // CIRCLE_H
