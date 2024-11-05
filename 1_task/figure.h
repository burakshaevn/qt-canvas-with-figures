#ifndef FIGURE_H
#define FIGURE_H

#include <QGraphicsGridLayout>
#include <QPen>

enum class FigureType{
    not_defined_,
    ellipse_,
    circle_,
    rectangle_,
    square_,
    line_
};

class Figure {
public:
    Figure() = default;
    Figure(int x, int y, int w, int h, const QPen& pen = QPen(QColor("#7b6f5d")), const int pen_width = 3, const FigureType& figure_type = FigureType::not_defined_)
        : x_(x)
        , y_(y)
        , w_(w)
        , h_(h)
        , is_visible_(true)
        , pen_(pen)
        , figure_type_(figure_type)
    {
        // Толщина обводки
        pen_.setWidth(pen_width);
    }

    ~Figure() = default;

    // Чисто виртуальные методы, которые обязан реализовать каждый наследник Figure
    // Чисто виртуальные методы это которые имеют virtual ... =0
    virtual void MoveTo(const int dx, const int dy) = 0;
    virtual void Show(QGraphicsScene* scene) = 0;
    virtual void RemoveFromScene(QGraphicsScene* scene) = 0;

    // Обычные виртуальные методы, которые имеют свою реализацию, но
    // классы наследники могут её как переопределять, так и оставить такой, какой она написана в базовом классе.
    // Если класс наследник не переопределил реализацию обычной функции virtual (которая без =0),
    // то он будет использовать определение метода из базового класса
    virtual void SetCoords(const int x, const int y){
        x_ = x;
        y_ = y;
    }
    virtual int GetX() const{
        return x_;
    }
    virtual int GetY() const{
        return y_;
    }

    virtual void SetSize(const int w, const int h) {
        w_ = w;
        h_ = h;
    }
    virtual int GetW() const{
        return w_;
    }
    virtual int GetH() const{
        return h_;
    }

    virtual void SetVisible(bool visible) {
        is_visible_ = visible;
    }
    virtual bool GetVisible() const {
        return is_visible_;
    }

    virtual void SetPen(const QPen& pen, const int pen_width) {
        pen_ = pen;
        pen_.setWidth(pen_width);
    }
    virtual QPen GetPen() const {
        return pen_;
    }

    virtual void SetFigureType(const FigureType& figure_type){
        figure_type_ = figure_type;
    }
    FigureType GetFigureType() const {
        return figure_type_;
    }

protected:
    int x_ = 0;
    int y_ = 0;
    int w_ = 0;
    int h_ = 0;
    bool is_visible_ = true;
    QPen pen_ = QPen(QColor("#7b6f5d"));
    FigureType figure_type_ = FigureType::not_defined_;
};

#endif // FIGURE_H
