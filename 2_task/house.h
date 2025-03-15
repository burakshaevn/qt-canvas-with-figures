#ifndef HOUSE_H
#define HOUSE_H

#include "line.h"
#include "square.h"
#include <QGraphicsScene>
#include <QPen>

class House {
public:
    House();
    House(int x, int y, int size, const QPen& pen = QPen(QColor("#7b6f5d"), 3));

    void MoveTo(int dx, int dy);
    void SetSize(int w, int h);
    void Show(QGraphicsScene* scene);
    void RemoveFromScene(QGraphicsScene* scene);
    void SetPen(const QPen& pen, const int pen_width);

    int GetX() const;
    int GetY() const;
    int GetW() const;
    int GetH() const;

    FigureType GetFigureType() const;

private:
    Square base_;       // Основание дома (квадрат)
    Line roof_left_;    // Левая сторона крыши (линия)
    Line roof_right_;   // Правая сторона крыши (линия)
    Line roof_top_;     // Верхняя сторона крыши (линия)
    int roof_height_;   // Высота треугольной крыши
};

#endif // HOUSE_H
