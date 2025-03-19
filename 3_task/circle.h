#ifndef CIRCLE_H
#define CIRCLE_H

#pragma once

#include "figure.h"

#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QPen>

class Circle : public Figure {
public:
    Circle();
    Circle(int x, int y, int radius_1, int radius_2, const QPen& pen = QPen(QColor("#7b6f5d")), const FigureType& figure_type = FigureType::ellipse_);
    virtual ~Circle();
    void MoveTo(int x, int y) override;
    void SetSize(const int w, const int h) override;
    void Show(QGraphicsScene *scene) override;
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

protected:
    int radius_1_;
    int radius_2_;

    // Элемент для отображения окружности. Это класс из библиотеки фрейморка Qt, представляющий графический элемент,
    // который рисует окружность на сцене в рамках холста QGraphicsView.
    QGraphicsEllipseItem* circle_item_;
};

#endif // CIRCLE_H
