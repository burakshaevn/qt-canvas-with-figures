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
    quadrilateral_,
    all_figures_
};

class Figure {
public:
    Figure();
    Figure(QGraphicsScene* scene, Point position, int w, int h, const QPen& pen = QPen(QColor(123, 111, 93), 3), const int pen_width = 3, const FigureType& figure_type = FigureType::not_defined_);

    ~Figure();

    void MoveTo(const int dx, const int dy);

    // Чисто виртуальные методы, которые обязан реализовать каждый наследник Figure
    // Чисто виртуальные методы это которые имеют вид virtual ... =0
    virtual void RemoveFromScene() = 0;

    // Обычные виртуальные методы, которые имеют свою реализацию, но
    // классы наследники могут её как переопределять, так и оставить такой, какой она написана в базовом классе.
    // Если класс наследник не переопределил реализацию обычной функции virtual (которая без =0),
    // то он будет использовать определение метода из базового класса
    virtual void UpdatePoints(const int dx, const int dy);
    virtual void Show();
    virtual void Rotate(const int degrees);

    virtual void SetCoords(const int x, const int y);
    virtual int GetX() const;
    virtual int GetY() const;

    virtual void SetSize(const int w, const int h);
    virtual int GetW() const;
    virtual int GetH() const;

    // Pen отвечает за цвет и толщину обводки фигуры.
    // Эти методы мы позволяем переопределить потому что, например, House состоит из нескольких фигур: линия и квдарат,
    // или, например, Circle состоит из двух окружностей разных размеров.
    // Поэтому, чтобы задать им нужную обводку, нужно обработать каждую фигуру,
    // которая входит в композицию. Поэтому сделать «общую» реализацию здесь нельзя,
    // нужно каждому классу свою реализацию этих методов
    virtual void SetPen(const QPen& pen, const int pen_width);
    virtual QPen GetPen() const;

    virtual void SetVisible(bool visible);
    virtual bool GetVisible() const;

    void SetFigureType(const FigureType& figure_type);
    FigureType GetFigureType() const;

protected:
    Point position_;
    int w_;
    int h_;
    bool is_visible_;
    QPen pen_;
    FigureType figure_type_;

    // Указатель на сцену, где будет расположена фигура
    QGraphicsScene* scene_;
};

#endif // FIGURE_H
