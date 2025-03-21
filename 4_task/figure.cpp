#include "figure.h"

Figure::Figure()
    : scene_(nullptr)
    , position_({0, 0})
    , w_(0)
    , h_(0)
    , is_visible_(true)
    , pen_(QPen(QColor("#7b6f5d")))
    , figure_type_(FigureType::not_defined_)
{}

Figure::Figure(QGraphicsScene* scene, Point position, int w, int h, const QPen& pen, const int pen_width, const FigureType& figure_type)
    : scene_(scene)
    , position_(position)
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

void Figure::MoveTo(const int dx, const int dy) {
    position_.MoveToX(dx);
    position_.MoveToY(dy);
    // SetCoords(position_.GetX() + dx, position_.GetY() + dy);
    Show();
}
void Figure::Show() {
    // ..
}
void Figure::Rotate(const int degrees) {
    // ...
}

void Figure::SetCoords(const int x, const int y){
    position_.SetX(x);
    position_.SetY(y);
}
int Figure::GetX() const{
    return position_.GetX();
}
int Figure::GetY() const{
    return position_.GetY();
}

void Figure::SetSize(const int w, const int h) {
    w_ = w;
    h_ = h;
}
int Figure::GetW() const{
    return w_;
}
int Figure::GetH() const{
    return h_;
}

void Figure::SetPen(const QPen& pen, const int pen_width) {
    pen_ = pen;
    pen_.setWidth(pen_width);
}
QPen Figure::GetPen() const {
    return pen_;
}

void Figure::SetVisible(bool visible) {
    is_visible_ = visible;
}
bool Figure::GetVisible() const {
    return is_visible_;
}

void Figure::SetFigureType(const FigureType& figure_type){
    figure_type_ = figure_type;
}
FigureType Figure::GetFigureType() const {
    return figure_type_;
}
