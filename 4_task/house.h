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
    House(QGraphicsScene* scene, int x, int y, int size, const QPen& pen = QPen(QColor("#7b6f5d"), 3));

    // void MoveTo(int dx, int dy) override;
    void SetSize(int w, int h) override;
    void Show() override;
    void RemoveFromScene() override;

    void SetVisible(bool visible) override;
    bool GetVisible() const override;

    int GetX() const override;
    int GetY() const override;
    int GetW() const override;
    int GetH() const override;

    void SetPen(const QPen& pen, const int pen_width) override;

private:
    Square base_;       // Основание дома (квадрат)
    Line roof_left_;    // Левая сторона крыши (линия)
    Line roof_right_;   // Правая сторона крыши (линия)
    Line roof_top_;     // Верхняя сторона крыши (линия)
    int roof_height_;   // Высота треугольной крыши
};

#endif // HOUSE_H
