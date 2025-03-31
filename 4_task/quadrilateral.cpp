#include "quadrilateral.h"

Quadrilateral::Quadrilateral()
    : Figure(), rect_item_(nullptr) {}

Quadrilateral::Quadrilateral(QGraphicsScene* scene, int x, int y, int w, int h, const QPen& pen, const FigureType& figure_type)
    : Figure(scene, {x, y}, w, h, pen, 3, figure_type)
{
    rect_item_ = new QGraphicsRectItem(0, 0, w, h);
    rect_item_->setPen(pen);
    SetFigureType(figure_type);
}

Quadrilateral::~Quadrilateral() {
    if (rect_item_) {
        delete rect_item_;
    }
}

// void Quadrilateral::MoveTo(const int dx, const int dy) {
//     position_.MoveToX(dx);
//     position_.MoveToY(dy);
//     if (rect_item_) {
//         rect_item_->setPos(position_.GetX(), position_.GetY());
//     }
// }

void Quadrilateral::Show() {
    if (!rect_item_) {
        rect_item_ = new QGraphicsRectItem(0, 0, w_, h_);
    }
    if (rect_item_ && !rect_item_->scene()) {
        scene_->addItem(rect_item_);
    }
    rect_item_->setPos(position_.GetX(), position_.GetY());
    rect_item_->setPen(pen_);
    rect_item_->setVisible(is_visible_);
}

void Quadrilateral::RemoveFromScene() {
    if (rect_item_ && scene_->items().contains(rect_item_)) {
        scene_->removeItem(rect_item_);
        delete rect_item_;
        rect_item_ = nullptr;
    }
}

void Quadrilateral::SetVisible(bool visible) {
    is_visible_ = visible;
    if (rect_item_) {
        rect_item_->setVisible(visible);
    }
}

bool Quadrilateral::GetVisible() const {
    return is_visible_;
}

void Quadrilateral::Rotate(const int degrees) {
    if (!rect_item_) return;

    qreal previous_rotation = rect_item_->rotation();
    rect_item_->setRotation(previous_rotation + degrees);

    QRectF global_bounds = rect_item_->mapToScene(rect_item_->boundingRect()).boundingRect();
    QRectF scene_bounds = scene_->sceneRect();

    if (!scene_bounds.contains(global_bounds)) {
        rect_item_->setRotation(previous_rotation);
    }
}

void Quadrilateral::SetCoords(const int x, const int y) {
    position_.SetX(x);
    position_.SetY(y);
}

int Quadrilateral::GetX() const {
    return position_.GetX();
}

int Quadrilateral::GetY() const {
    return position_.GetY();
}

void Quadrilateral::SetSize(const int w, const int h) {
    w_ = w;
    h_ = h;
    if (rect_item_) {
        rect_item_->setRect(0, 0, w_, h_);
    }
}

int Quadrilateral::GetW() const {
    return w_;
}

int Quadrilateral::GetH() const {
    return h_;
}

void Quadrilateral::SetPen(const QPen& pen, const int pen_width) {
    pen_ = pen;
    pen_.setWidth(pen_width);
    if (rect_item_) {
        rect_item_->setPen(pen_);
    }
}

QPen Quadrilateral::GetPen() const {
    return pen_;
}
