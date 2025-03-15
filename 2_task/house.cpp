#include "house.h"

// Конструктор по умолчанию
House::House()
    : base_(0, 0, 0)
    , roof_left_(0, 0, 0, 0)
    , roof_right_(0, 0, 0, 0)
    , roof_top_(0, 0, 0, 0)
    , roof_height_(0)
{}

// Параметризованный конструктор
House::House(int x, int y, int size, const QPen& pen)
    : base_(x, y + size / 2, size, pen)
    , roof_height_(size / 2)
{
    // Вычисляем координаты для крыши
    int roof_top_x = x + size / 2;
    int roof_top_y = y;
    int roof_left_x = x;
    int roof_left_y = y + roof_height_;
    int roof_right_x = x + size;
    int roof_right_y = y + roof_height_;

    // Инициализируем линии крыши
    roof_left_ = Line(roof_left_x, roof_left_y, roof_top_x, roof_top_y, pen);
    roof_right_ = Line(roof_right_x, roof_right_y, roof_top_x, roof_top_y, pen);
    roof_top_ = Line(roof_left_x, roof_left_y, roof_right_x, roof_right_y, pen);
}


// Перемещение дома
void House::MoveTo(int dx, int dy) {
    // Получаем текущие координаты
    int newX = base_.GetX() + dx;
    int newY = base_.GetY() + dy;

    qreal sceneWidth = 1260;
    qreal sceneHeight = 557;

    // Проверяем, что дом не выходит за пределы сцены
    if (newX < 0 || newX + base_.GetW() > sceneWidth ||
        newY - roof_height_ < 0 || newY + base_.GetH() > sceneHeight) {
        qDebug() << "House would go out of bounds. Move canceled.";
        return;
    }

    // Перемещаем дом, если проверка пройдена
    base_.MoveTo(dx, dy);
    roof_left_.MoveTo(dx, dy);
    roof_right_.MoveTo(dx, dy);
    roof_top_.MoveTo(dx, dy);
}

// Установка размера дома
void House::SetSize(int w, int h) {
    // Устанавливаем размер основания
    base_.SetSize(w, h);

    // Обновляем высоту крыши
    roof_height_ = h / 2;

    // Обновляем координаты крыши
    int x = base_.GetX();
    int y = base_.GetY();
    int roof_top_x = x + w / 2;
    // int roof_top_y = y - roof_height_;
    int roof_top_y = std::max(0, y - roof_height_);
    int roof_left_x = x;
    int roof_left_y = y;
    int roof_right_x = x + w;
    int roof_right_y = y;

    roof_left_.SetCoords(roof_left_x, roof_left_y);
    roof_left_.SetSize(roof_top_x - roof_left_x, roof_top_y - roof_left_y);

    roof_right_.SetCoords(roof_right_x, roof_right_y);
    roof_right_.SetSize(roof_top_x - roof_right_x, roof_top_y - roof_right_y);

    roof_top_.SetCoords(roof_left_x, roof_left_y);
    roof_top_.SetSize(roof_right_x - roof_left_x, 0);
}

// Отображение дома на сцене
void House::Show(QGraphicsScene* scene) {
    base_.Show(scene);
    roof_left_.Show(scene);
    roof_right_.Show(scene);
    roof_top_.Show(scene);
}

// Удаление дома со сцены
void House::RemoveFromScene(QGraphicsScene* scene) {
    base_.RemoveFromScene(scene);
    roof_left_.RemoveFromScene(scene);
    roof_right_.RemoveFromScene(scene);
    roof_top_.RemoveFromScene(scene);
}

// Установка пера для всех элементов дома
void House::SetPen(const QPen& pen, const int pen_width) {
    base_.SetPen(pen, pen_width);
    roof_left_.SetPen(pen, pen_width);
    roof_right_.SetPen(pen, pen_width);
    roof_top_.SetPen(pen, pen_width);
}

// Получение координаты X дома
int House::GetX() const {
    return base_.GetX();
}

// Получение координаты Y дома
int House::GetY() const {
    return base_.GetY();
}

// Получение ширины дома
int House::GetW() const {
    return base_.GetW();
}

// Получение высоты дома (основание + крыша)
int House::GetH() const {
    return base_.GetH() + roof_height_;
}

// Получение типа фигуры
FigureType House::GetFigureType() const {
    return FigureType::house_;
}
