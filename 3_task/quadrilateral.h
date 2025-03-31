#ifndef QUADRILATERAL_H
#define QUADRILATERAL_H

#include "figure.h"
#include <QGraphicsRectItem>
#include <QGraphicsScene>

class Quadrilateral : public Figure {
public:
    Quadrilateral();
    Quadrilateral(int x, int y, int width, int height,
                  const QPen& pen = QPen(QColor("#7b6f5d")),
                  const FigureType& figure_type = FigureType::quadrilateral_);
    ~Quadrilateral();

    // Реализация виртуальных методов
    void MoveTo(const int dx, const int dy) override;
    void Show(QGraphicsScene* scene) override;
    void RemoveFromScene(QGraphicsScene* scene) override;
    void SetVisible(bool visible) override;
    bool GetVisible() const override;

    void Rotate(const int degrees, QGraphicsScene* scene) override;

    void SetCoords(const int x, const int y) override;
    int GetX() const override;
    int GetY() const override;

    void SetSize(const int w, const int h) override;
    int GetW() const override;
    int GetH() const override;

    void SetPen(const QPen& pen, const int pen_width) override;
    QPen GetPen() const override;

protected:
    QGraphicsRectItem* rect_item_;
};

#endif // QUADRILATERAL_H
