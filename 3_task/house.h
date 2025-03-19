#ifndef HOUSE_H
#define HOUSE_H

#include "figure.h"
#include "line.h"
#include "square.h"
#include <QGraphicsScene>
#include <QPen>

class House : public Figure {
public:
    House();
    House(int x, int y, int size, const QPen& pen = QPen(QColor("#7b6f5d"), 3));

    void MoveTo(int dx, int dy) override;
    void SetSize(int w, int h) override;
    void Show(QGraphicsScene* scene) override;
    void RemoveFromScene(QGraphicsScene* scene) override;

    void SetVisible(bool visible) override;
    bool GetVisible() const override;

    void SetCoords(const int x, const int y) override;
    int GetX() const override;
    int GetY() const override;
    int GetW() const override;
    int GetH() const override;

    void SetPen(const QPen& pen, const int pen_width) override;
    QPen GetPen() const override;

private:
    Square base_;       // Основание дома (квадрат)
    Line roof_left_;    // Левая сторона крыши (линия)
    Line roof_right_;   // Правая сторона крыши (линия)
    Line roof_top_;     // Верхняя сторона крыши (линия)
    int roof_height_;   // Высота треугольной крыши
};

#endif // HOUSE_H
