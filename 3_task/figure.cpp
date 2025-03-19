#include "figure.h"

Figure::Figure()
    : position_({0, 0})
    , w_(0)
    , h_(0)
    , is_visible_(true)
    , pen_(QPen(QColor("#7b6f5d")))
    , figure_type_(FigureType::not_defined_)
{}

Figure::Figure(Point position, int w, int h, const QPen& pen, const int pen_width, const FigureType& figure_type)
    : position_(position)
    , w_(w)
    , h_(h)
    , is_visible_(true)
    , pen_(pen)
    , figure_type_(figure_type)
{
    // Толщина обводки
    pen_.setWidth(pen_width);
}

Figure::~Figure() = default;

void Figure::SetFigureType(const FigureType& figure_type){
    figure_type_ = figure_type;
}
FigureType Figure::GetFigureType() const {
    return figure_type_;
}
