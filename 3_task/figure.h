#ifndef FIGURE_H
#define FIGURE_H

#include <QGraphicsGridLayout>
#include <QPen>
#include <QMessageBox>
#include "point.h"

enum class FigureType{
    not_defined_,
    ellipse_,
    circle_,
    rectangle_,
    square_,
    line_,
    ring_,
    house_,
    trapezoid_,
    rhomb_,
    quadrilateral_
};

class Figure {
public:
    Figure();
    Figure(Point position, int w, int h, const QPen& pen = QPen(QColor("#7b6f5d")), const int pen_width = 3, const FigureType& figure_type = FigureType::not_defined_);

    ~Figure();

    // Чисто виртуальные методы, которые обязан реализовать каждый наследник Figure
    // Чисто виртуальные методы это которые имеют вид virtual ... =0
    virtual void MoveTo(const int dx, const int dy) = 0;
    virtual void Show(QGraphicsScene* scene) = 0;
    virtual void RemoveFromScene(QGraphicsScene* scene) = 0;
    virtual void SetVisible(bool visible) = 0;
    virtual bool GetVisible() const = 0;

    // Здесь мы оставляем {} после заголовка функции имя в виду что реализация функции пуста,
    // потому что такие классы, как House, Line, Circle и Ring, они не имеют заголовка этой функции в .h файлах
    // и этой функции и не будет у этих классов. Поэтому они будут «ссылаться» на эту пустую реализацию ниже
    virtual void Rotate(const int degrees, QGraphicsScene* scene) {}

    virtual void SetCoords(const int x, const int y) = 0;
    virtual int GetX() const = 0;
    virtual int GetY() const = 0;

    virtual void SetSize(const int w, const int h) = 0;
    virtual int GetW() const = 0;
    virtual int GetH() const = 0;

    // Pen отвечает за цвет и толщину обводки фигуры.
    // Эти методы мы позволяем переопределить потому что, например, House состоит из нескольких фигур: линия и квдарат,
    // или, например, Circle состоит из двух окружностей разных размеров.
    // Поэтому, чтобы задать им нужную обводку, нужно обработать каждую фигуру,
    // которая входит в композицию. Поэтому сделать «общую» реализацию здесь нельзя,
    // нужно каждому классу свою реализацию этих методов
    virtual void SetPen(const QPen& pen, const int pen_width) = 0;
    virtual QPen GetPen() const = 0;

    void SetFigureType(const FigureType& figure_type);
    FigureType GetFigureType() const;

protected:
    Point position_;
    int w_;
    int h_;
    bool is_visible_;
    QPen pen_;
    FigureType figure_type_;
};

#endif // FIGURE_H
