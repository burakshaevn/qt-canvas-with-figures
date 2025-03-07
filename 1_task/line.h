#ifndef LINE_H
#define LINE_H

#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QPen>

#include "domain.h"
#include "point.h"

class Line {
public:
    Line();
    Line(int x1, int y1, int x2, int y2, const QPen& pen = QPen(QColor("#7b6f5d"), 3));

    // Реализовывать деструктор здесь не нужно, потому что здесь нет динамического выделения памяти
    // ~Line();

    void MoveTo(const int dx, const int dy);
    void SetCoords(const int x, const int y);
    void SetSize(const int w, const int h);

    int GetX() const;
    int GetY() const;
    int GetW() const;
    int GetH() const;

    void Show(QGraphicsScene *scene);
    void RemoveFromScene(QGraphicsScene* scene);

    void SetVisible(bool visible);
    bool GetVisible() const;

    void SetPen(const QPen& pen, const int pen_width);
    QPen GetPen() const;

    FigureType GetFigureType() const;

private:
    Point start_; // Начальная точка линии
    Point end_;   // Конечная точка линии
    int w_ = 0;   // Ширина (разница по X)
    int h_ = 0;   // Высота (разница по Y)
    bool is_visible_ = true;
    QPen pen_ = QPen(QColor("#7b6f5d"), 3);
    QGraphicsLineItem* line_item_;
};

#endif // LINE_H
