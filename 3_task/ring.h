#pragma once

#ifndef RING_H
#define RING_H

#include "circle.h"

#include <QGraphicsScene>
#include <QGraphicsPathItem>
#include <QMessageBox>

class Ring : public Circle {
private:
    Circle outer_circle_;  // Внешний круг
    Circle inner_circle_;  // Внутренний круг

public:
    Ring() = default;

    Ring(int x, int y, int outer_radius)
        : outer_circle_(x, y, outer_radius)
        , inner_circle_(x, y, outer_radius / 2)
    {
        if (inner_circle_.GetW() / 2 >= outer_circle_.GetW() / 2) {
            QMessageBox::critical(nullptr, "Ошибка", "Inner radius must be smaller than outer radius.");
        }
        SetFigureType(FigureType::ring_);
    }

    void MoveTo(int dx, int dy) override {
        outer_circle_.MoveTo(dx, dy);
        int innerX = outer_circle_.GetX() + (outer_circle_.GetW() - inner_circle_.GetW()) / 2;
        int innerY = outer_circle_.GetY() + (outer_circle_.GetH() - inner_circle_.GetH()) / 2;
        inner_circle_.SetCoords(innerX, innerY);
    }
    void SetCoords(const int x, const int y) override {
        outer_circle_.SetSize(x, y);

        int innerX = outer_circle_.GetX() + outer_circle_.GetW() / 2 - inner_circle_.GetW() / 2;
        int innerY = outer_circle_.GetY() + outer_circle_.GetH() / 2 - inner_circle_.GetH() / 2;
        inner_circle_.SetCoords(innerX, innerY);
    }
    int GetX() const override {
        return outer_circle_.GetX();
    }
    int GetY() const override {
        return outer_circle_.GetY();
    }

    void SetSize(int outer_radius, int inner_radius) override {
        w_ = outer_radius;
        h_ = outer_radius;
        inner_radius /= 2;
        outer_circle_.SetSize(outer_radius, outer_radius);
        inner_circle_.SetSize(inner_radius, inner_radius);
    }
    int GetW() const override {
        return outer_circle_.GetW();
    }
    int GetH() const override {
        return outer_circle_.GetH();
    }

    void Show(QGraphicsScene* painter) override {
        outer_circle_.Show(painter);

        // Обновление позиции внутреннего круга
        int innerX = outer_circle_.GetX() + outer_circle_.GetW() / 2 - inner_circle_.GetW() / 2;
        int innerY = outer_circle_.GetY() + outer_circle_.GetH() / 2 - inner_circle_.GetH() / 2;
        inner_circle_.SetCoords(innerX, innerY);

        inner_circle_.Show(painter);
    }

    void SetPen(const QPen& pen, const int pen_width) override {
        outer_circle_.SetPen(pen, pen_width);
        inner_circle_.SetPen(pen, pen_width);
    }

    void SetVisible(bool visible) override {
        outer_circle_.SetVisible(visible);
        inner_circle_.SetVisible(visible);
    }
    bool GetVisible() const override{
        return outer_circle_.GetVisible();
    }

    void RemoveFromScene(QGraphicsScene *scene) override {
        outer_circle_.RemoveFromScene(scene);
        inner_circle_.RemoveFromScene(scene);
    }

};

#endif // RING_H
