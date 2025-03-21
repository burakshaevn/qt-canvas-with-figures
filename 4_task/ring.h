#pragma once

#ifndef RING_H
#define RING_H

#include "ellipse.h"

#include <QGraphicsScene>
#include <QGraphicsPathItem>
#include <QMessageBox>

class Ring : public Circle {
private:
    Circle outer_circle_;  // Внешний круг
    Circle inner_circle_;  // Внутренний круг

public:
    Ring();
    Ring(QGraphicsScene* scene, int x, int y, int outer_radius_1, int inner_radius_1, const QPen& pen = QPen(QColor("#7b6f5d"), 3));

    // void MoveTo(int dx, int dy) override;
    void SetCoords(const int x, const int y) override;
    int GetX() const override;
    int GetY() const override;

    void SetSize(int outer_radius, int inner_radius) override;
    int GetW() const override;
    int GetH() const override;

    void Show() override;

    void SetPen(const QPen& pen, const int pen_width) override;

    void SetVisible(bool visible) override;
    bool GetVisible() const override;

    void RemoveFromScene() override;

};

#endif // RING_H
