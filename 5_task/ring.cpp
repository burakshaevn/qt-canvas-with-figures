#include "ring.h"

Ring::Ring() = default;

Ring::Ring(QGraphicsScene* scene, int x, int y, int outer_radius_1, int inner_radius_1, const QPen& pen)
    : outer_circle_(scene, x, y, outer_radius_1, outer_radius_1, pen)
    , inner_circle_(scene, x, y, inner_radius_1, inner_radius_1, pen)
{
    SetFigureType(FigureType::ring_);
    qDebug() << "Создано кольцо с центром в (" << x << ',' << y << "), внешним радиусом "
             << outer_radius_1 << " и внутренним радиусом " << inner_radius_1 << '.';
}

Ring::~Ring() = default;

void Ring::UpdatePoints(const int dx, const int dy) {
    outer_circle_.MoveTo(dx, dy);
    int innerX = outer_circle_.GetX() + (outer_circle_.GetW() - inner_circle_.GetW()) / 2;
    int innerY = outer_circle_.GetY() + (outer_circle_.GetH() - inner_circle_.GetH()) / 2;
    inner_circle_.SetCoords(innerX, innerY);
}

void Ring::SetCoords(const int x, const int y) {
    outer_circle_.SetSize(x, y);
    int innerX = outer_circle_.GetX() + outer_circle_.GetW() / 2 - inner_circle_.GetW() / 2;
    int innerY = outer_circle_.GetY() + outer_circle_.GetH() / 2 - inner_circle_.GetH() / 2;
    inner_circle_.SetCoords(innerX, innerY);
}
int Ring::GetX() const {
    return outer_circle_.GetX();
}
int Ring::GetY() const {
    return outer_circle_.GetY();
}

void Ring::SetSize(int outer_radius, int inner_radius) {
    w_ = outer_radius;
    h_ = outer_radius;
    inner_radius /= 2;
    outer_circle_.SetSize(outer_radius, outer_radius);
    inner_circle_.SetSize(inner_radius, inner_radius);
}
int Ring::GetW() const {
    return outer_circle_.GetW();
}
int Ring::GetH() const {
    return outer_circle_.GetH();
}

void Ring::Show() {
    outer_circle_.Show();

    int innerX = outer_circle_.GetX() + outer_circle_.GetW() / 2 - inner_circle_.GetW() / 2;
    int innerY = outer_circle_.GetY() + outer_circle_.GetH() / 2 - inner_circle_.GetH() / 2;
    inner_circle_.SetCoords(innerX, innerY);

    inner_circle_.Show();
}

void Ring::SetPen(const QPen& pen, const int pen_width) {
    outer_circle_.SetPen(pen, pen_width);
    inner_circle_.SetPen(pen, pen_width);
}

void Ring::SetVisible(bool visible) {
    outer_circle_.SetVisible(visible);
    inner_circle_.SetVisible(visible);
}
bool Ring::GetVisible() const {
    return outer_circle_.GetVisible();
}

void Ring::RemoveFromScene() {
    outer_circle_.RemoveFromScene();
    inner_circle_.RemoveFromScene();
}
