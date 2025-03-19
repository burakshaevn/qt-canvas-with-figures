# Создание и использование библиотеки классов для графических примитивов на основе принципа наследования

Задачи, которые необходимо реализовать в л/р 3:

1. **В интерфейсный раздел модуля-библиотеки ввести описание класса Figure, используя для задания абстрактных методов директиву abstract в заголовке метода.**

У нас есть абстрактный класс Figure. В С++ мы не пишем «abstract» у класса, чтобы сделать его таким. Здесь мы говорим что он абстрактный благодаря тому, что у класса есть хотя бы один **чисто виртуальный метод**, не путать с **обычными виртуальными методами**.
```cpp
virtual void FooName() = 0; // чисто виртуальный метод
virtual void FooName(); // обычная виртуальная функция
```
Если в классе есть хотя бы один чисто виртуальный метод, класс — абстрактный. Объявление класса Figure хранится в файле figure.h, реализация в исполнительном файле figure.cpp.

figure.h:
```cpp
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
    rhomb_
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
```

2.     **Создать класс окружностей Circle как потомка класса Figure с добавлением нового свойства – радиуса окружности, собственным конструктором, методом Show, методом  MoveTo и новым методом изменения радиуса.**

Объявление класса Circle содержится в circle.h, реализация его методов — в circle.cpp:
```cpp
#ifndef CIRCLE_H
#define CIRCLE_H

#pragma once

#include "figure.h"

#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QPen>

class Circle : public Figure {
public:
    Circle();
    Circle(int x, int y, int radius_1, int radius_2, const QPen& pen = QPen(QColor("#7b6f5d")), const FigureType& figure_type = FigureType::ellipse_);
    virtual ~Circle();
    void MoveTo(int x, int y) override;
    void SetSize(const int w, const int h) override;
    void Show(QGraphicsScene *scene) override;
    void RemoveFromScene(QGraphicsScene* scene) override; 

    void SetVisible(bool visible) override;
    bool GetVisible() const override;

protected:
    int radius_1_;
    int radius_2_;

    // Элемент для отображения окружности. Это класс из библиотеки фрейморка Qt, представляющий графический элемент,
    // который рисует окружность на сцене в рамках холста QGraphicsView.
    QGraphicsEllipseItem* circle_item_;
};

#endif // CIRCLE_H
```

У функций этого класса есть слово `override` это функция из базового класса (Figure) и она будет перегружена (определена своя логика).

3.     **Дать программную реализацию конструктора дочернего класса окружностей, ОБЯЗАТЕЛЬНО начинающуюся с вызова конструктора родителя, в конце предусмотреть вывод сообщения о создании объекта.**
```cpp
Circle::Circle(int x, int y, int radius_1, int radius_2, const QPen& pen, const FigureType& figure_type)
    : Figure({x, y}, radius_1 * 2, radius_2 * 2, pen, 3, figure_type)
    , radius_1_(radius_1)
    , radius_2_(radius_2)
{
    circle_item_ = new QGraphicsEllipseItem(0, 0, radius_1_ * 2, radius_2_ * 2);
    circle_item_->setPen(pen);
    SetFigureType(FigureType::circle_);
    qDebug() << "Создана окружность с центром в (" << x << ',' << y << ") и радиусом " << radius_1 << " и внутренним радиусом " << radius_2 << '.';
}
```
Вызов конструктора родителя происходит в строке `Figure({x, y}, radius_1 * 2, radius_2 * 2, pen, 3, figure_type)`. 

4.     **В основном (демонстрационном) модуле предусмотреть создание объектов-окружностей, их перемещение и изменение радиуса.** 

В выпадающем списке появляется возможность добавлять окружность и эллипс. 
<div align="center">
  <img src="https://github.com/user-attachments/assets/fea7b684-e3c3-41b5-9a07-650e282146d0" alt="image"> 
</div> 

5.     **На базе класса Circle создать дочерний подкласс эллипсов добавлением свойства-полуоси. Реализовать свой конструктор и методы прорисовки и перемещения. Для поворота на 90 градусов ввести новый метод.** 

Метод поворота на 90 градусов является чисто виртуальной функцией из базового класса Figure. То есть, класс Ellipse переопределяет функцию базового класса `Figure::Ellipse`. Для окружности этого метода нет потому что её положение никак не изменится.
```cpp
#ifndef ELLIPSE_H
#define ELLIPSE_H

#pragma once

#include "circle.h"

class Ellipse : public Circle {
public:
    Ellipse();
    Ellipse(int x, int y, int radius_1, int radius_2, const QPen& pen = QPen(QColor("#7b6f5d")));
    ~Ellipse();
    void SetSize(const int w, [[maybe_unused]] const int h) override;

    void Rotate(const int degrees, QGraphicsScene* scene) override;
};

#endif // ELLIPSE_H
```

Сама функция принимает целочисленное значение — на сколько градусов повернуть фигуру. Вторым параметром передаётся указатель на холст, чтобы внутри функции Rotate проверить, останется ли фигура в пределах холста, если выполнить поворот на указанное количество градусов. Классы, для которых доступен поворот на 90 градусов:
* `class Ellipse`,
* `class Rectangle`,
* `class Trapezoid`,
* `class Rhomb`.
6.  **Аналогично создать класс четырехугольников и подклассы для ромбов, трапеций, прямоугольников и проверить их работоспособность.**
Добавляем класс Rhomb:
```cpp
#ifndef Rhomb_H
#define Rhomb_H

#include "rectangle.h"
#include <QGraphicsPolygonItem>

class Rhomb : public Rectangle {
public:
    Rhomb();
    Rhomb(int x, int y, int side, int height, const QPen& pen = QPen(QColor("#7b6f5d")), const FigureType& figure_type = FigureType::rhomb_);
    virtual ~Rhomb();

    void MoveTo(const int dx, const int dy) override;
    void SetSize(const int side, const int height) override;
    void Show(QGraphicsScene* scene) override;
    void RemoveFromScene(QGraphicsScene* scene) override;

    void Rotate(const int degrees, QGraphicsScene* scene) override;

protected:
    QGraphicsPolygonItem* rhomb_item_;
    int side_;  // Длина стороны ромба
    int height_; // Высота ромба
};

#endif // RHOMB_H
```
и класс Trapezoid:
```cpp
#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include "rectangle.h"
#include <QGraphicsPolygonItem>

class Trapezoid : public Rectangle {
public:
    Trapezoid();
    Trapezoid(int x, int y, int base1, int base2, int height, const QPen& pen = QPen(QColor("#7b6f5d")), const FigureType& figure_type = FigureType::trapezoid_);
    virtual ~Trapezoid();

    void MoveTo(const int dx, const int dy) override;
    void SetSize(const int base1, const int base2, const int height);
    void Show(QGraphicsScene* scene) override;
    void RemoveFromScene(QGraphicsScene* scene) override;

    void Rotate(const int degrees, QGraphicsScene* scene) override;

protected:
    QGraphicsPolygonItem* trapezoid_item_;
    int base1_;  // Длина первого основания
    int base2_;  // Длина второго основания
    int height_; // Высота трапеции
};

#endif // TRAPEZOID_H
```
