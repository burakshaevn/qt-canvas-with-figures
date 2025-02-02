# Создание графических примитивов

### 1.  Разместить на форме компонент Image для отображения примитивов и выровнять его на всю клиентскую область

У нас роль «холста будет принимать приватный атрибут, который хранится в классе MainWindow: `std::unique_ptr<QGraphicsScene> scene;`. Заметим, что это не обычный сырой указатель, а умный указатель «std::unique_ptr», который сам следит за временем жизни объекта, для которого выделялась динамически память, и удаляет объект, как только он перестаёт использоваться. То есть, нам не нужно собственноручно писать деструктор для этого объекта (`scene`):

```cpp
class MainWindow : public QMainWindow
{
   // Какие-то прочие методы ...
private:
   std::unique_ptr<QGraphicsScene> scene;
   // Какие-то прочие приватные атрибуты
};
```

Он у нас инициализируется в конструкторе класса MainWindow. Задаём расположение x: 0, y: 0, width: 1260, height: 557.
```cpp
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , scene(nullptr)
{
    // Создаем сцену с фиксированными размерами
    scene = std::make_unique<QGraphicsScene>(0, 0, 1260, 557, this);
    ui->graphicsView->setScene(scene.get());

    // ...
}
```

### 2.  Создать обработчик события формы OnCreate для инициализации датчика псевдослучайных чисел и установки режима рисования на поверхности компонента Image.
В классе MainWindow есть функция GetRandomNumber:
```cpp
int MainWindow::GetRandomNumber(const int min, const int max) const {
   static std::mt19937 engine{ std::random_device{}() };
   std::uniform_int_distribution<int> distribution(min, max);
   return distribution(engine);
}
```
Этот код использует библиотеку `<random>` для создания генератора случайных чисел.

### 5.  Добавить в проект новый программный модуль, НЕ СВЯЗАННЫЙ со своей формой: команда меню File / New / Unit   и  ОБЯЗАТЕЛЬНО СОХРАНИТЬ ЕГО ВМЕСТЕ С ПРОЕКТОМ. Поскольку модуль является чисто программным, то его заготовка содержит лишь заголовок, начало интерфейсной секции (директива interface) и начало секции реализации (директива implementation).

В контексте C++ и Qt это означает, что нам нужно создать новый заголовочный файл (.h) и файл реализации (.cpp), которые будут содержать код, не связанный с графическим интерфейсом. То есть, создать отдельные файлы (.h) и (.cpp) для классов фигур. У нас все заголовочные файлы (.h) отделены от файлов реализации (.cpp):
<div align="center">
  <img src="https://github.com/user-attachments/assets/86486d0c-0da8-45e9-9d30-6b72b9bd7d05" alt="image">
   <img src="https://github.com/user-attachments/assets/84faa424-5bb0-4edc-a372-9410c63af20d" alt="image">
</div> 
 
### 7.  В интерфейсном разделе нового модуля ввести описание (ТОЛЬКО ОПИСАНИЕ!) одного из создаваемых классов (в разделе описания типов). Для простоты сначала можно взять класс окружностей, подробно описанный в лекционном материале. Остальные классы можно добавить после проверки работы класса окружностей. В классе сделать поля данных закрытыми, а методы – открытыми. Каждый примитив должен иметь базовую точку, изменение координат которой приводит к перемещению примитива без изменения его размеров.

Здесь имеется в виду что в заголочных файлах у нас должно быть только объявление интерфейса (функций), а реализация должна быть в (.cpp) файлах. Пример ellipse.h:
```cpp
#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QPen>

#include "domain.h"

enum class FigureType;

class Ellipse {
public:
    Ellipse();
    Ellipse(int x, int y, int radius_1, int radius_2, const QPen& pen = QPen(QColor("#7b6f5d"), 3));

    // Реализовывать деструктор здесь не нужно, потому что здесь нет динамического выделения памяти
    // ~Ellipse();

    void MoveTo(int dx, int dy);
    void SetSize(const int w, const int h);
    void Show(QGraphicsScene *scene);
    void RemoveFromScene(QGraphicsScene* scene);

    // Методы для получения координат и размеров
    int GetX() const;
    int GetY() const;
    int GetW() const; // Ширина = диаметр по горизонтали
    int GetH() const; // Высота = диаметр по вертикали

    void SetPen(const QPen& pen, const int pen_width);
    FigureType GetFigureType() const;

private:
    int radius_1_;
    int radius_2_;

    int x_ = 0;
    int y_ = 0;
    bool is_visible_ = true;
    QPen pen_ = QPen(QColor("#7b6f5d"));

    QGraphicsEllipseItem* ellipse_item_;
};

#endif // ELLIPSE_H
```
   
### 9.  Оформить раздел реализации модуля, включив в него программную реализацию каждого объявленного метода. В методе MoveTo для удобства дальнейшего использования задаются не новые координаты базовой точки, а СМЕЩЕНИЕ относительно нее, которое может быть и отрицательным.

То есть имеют в виду что нужно реализовать каждый метод в (.cpp) файлах, что мы объявили в (.h) файлах. Написать саму логику для этих функций. И при этом, MoveTo должен не телепортировать объект на координаты, а добавлять к текущим X и Y указанные пользователем координаты.

Здесь в качесте примера реализации этого метода можно показать функцию MoveTo.

```cpp
void Ellipse::MoveTo(int dx, int dy) {
   // добавляем к текущим координатам (x_ и y_) новые значения, то есть, х и у
    x_ += dx;
    y_ += dy;
   // Проверяем, инициализирован ли ellipse_item_. Если да, то перемещаем объект.
    if (ellipse_item_) {
        ellipse_item_->setPos(x_ - radius_1_, y_ - radius_2_);
    }
}
```

### 11.  Программная реализация методов показа примитивов может использовать стандартные графические примитивы системы Windows. Например, вывод окружности выполняется следующим образом:
`Form1.Image1.Canvas.Ellipse(x-r, y-r, x+r, y+r);`

У нас не Delphi Pascal, а C++, поэтому, у нас объект окружности реализует `QGraphicsEllipseItem* ellipse_item_`. В каждом классе есть свой такой объект. Например, в классе прямоугольник это `QGraphicsRectItem* rect_item_`.
 
### 13.   В разделе реализации основного модуля объявить одну-две переменные объектного типа, а также – массив объектных указателей для проверки возможностей групповой обработки объектов-примитивов.

* Тип FigureVariant

Мы используем `std::variant` для хранения объектов разных типов фигур (Rectangle, Square, Ellipse, Line). Это позволяет хранить в одном векторе объекты разных типов.
```cpp
using FigureVariant = std::variant<Rectangle, Square, Ellipse, Line>;
```

* Вектор figures_

Вектор figures_ объявлен как член класса MainWindow:

```cpp
std::vector<FigureVariant> figures_;
```

Этот вектор хранит все созданные фигуры.

5. Пример создания объектов
Предположим, пользователь выбрал тип фигуры "Прямоугольник", ввел координаты (10, 20) и размеры (100, 50). Вот что произойдет:

Вызов `CreateFigure(FigureType::rectangle_, 10, 20, 100, 50)` создаст объект Rectangle и вернет его как FigureVariant.

Фигура будет добавлена в вектор figures_:

```cpp
figures_.push_back(new_figure);
```

Фигура будет отображена на сцене:

```cpp
ShowFigure(new_figure, scene.get());
```

### 14.   Написать обработчики команд создания примитивов, выполняющие следующие действия:

*  создать новый объект вызовом конструктора со случайными параметрами примитива;
Выбираем любой тип фигуры → В разделе создания нажимаем на стрелки. Благодаря этому у нас загружаются случайные числа в строки для ввода информации о координатах и размерах.

Пример 1. Создаём 5 случайных фигур на холсте. Для этого указываем только нужное нам количество фигур — 5. После этого нажимаем на галочку и фигуры создаются в случайном порядке.
<div align="center">
  <img src="https://github.com/user-attachments/assets/b6bf5493-b85d-4604-8e51-2b5f7c61ded9" alt="image"> 
</div> 


Пример 2. Создаём одну случайную фигуру в случайных координатах. Для этого указываем количество фигур — 1, а координаты можем ввести сами, а можем создать случайные. Для этого просто нажимаем на стрелочки и они вернут случайные значения.
<div align="center">
  <img src="https://github.com/user-attachments/assets/df945db3-8602-4d69-bd9d-9b5cff06092c" alt="image"> 
</div> 

*  показать примитив методом Show.
У каждого объекта есть свой метод Show, который просто отображает фигуру на холсте. То есть, тут можно просто показать реализацию этих методов для каждого класса и всё. Вот примеры:

class Line:
```cpp
void Line::Show(QGraphicsScene *scene) {
    // Если line_item_ еще не создан, создаем его
    if (!line_item_) {
        line_item_ = new QGraphicsLineItem(x_, y_, x2_, y2_);
        line_item_->setPen(pen_);
        scene->addItem(line_item_);
    }
    // Если создан, но не добавлен на сцену, добавляем его
    else if (!line_item_->scene()) {
        scene->addItem(line_item_);
    }

    // Устанавливаем параметры видимости и пера
    line_item_->setPen(pen_);
    line_item_->setVisible(is_visible_);
}
```

class Rectangle:
```cpp
void Rectangle::Show(QGraphicsScene* scene) {
    if (!rect_item_) {
        rect_item_ = new QGraphicsRectItem(0, 0, w_, h_);
    }
    if (rect_item_ && !rect_item_->scene()) {
        scene->addItem(rect_item_);
    }
    rect_item_->setPos(x_, y_);
    rect_item_->setPen(pen_);
}
```

### 15.   Написать обработчики команд перемещения примитивов в новую точку со случайными координатами, используя генерацию значений смещения координат в пределах [-50, 50].

Эту логику реализуют функции MoveTo в каждом классе. Но они не от -50 до 50, а насколько захочет пользователь. Но там тоже есть кнопка генерации случайных чисел, поэтому если что можно вернуть и случайные числа.
![image](https://github.com/user-attachments/assets/d90c608d-a87d-41a8-a397-40ae0ca667d6)


### 16.   Написать обработчики команд изменения геометрических свойств объектов (радиус окружности, размеры прямоугольника, положение конечной точки отрезка и т.д.).

Всё это реализуется в окне выше (15 пункт). Там можно изменять геометрию объекта.

### 17.   Написать обработчики команд создания массивов объектов и группового изменения их свойств.
Все фигуры создаются и добавляются в `std::vector<FigureVariant> figures_;` (находится в классе MainWindow). Обработка всех фигур целиком происходит в функции `MainWindow::on_checkBox_all_size_stateChanged`. Она выделяет все фигуры жёлтым цветом, а уже применение изменений происходит в функции `MainWindow::on_pushButton_ok_size_clicked` (в ней каждая строка расписана комментарием).

```cpp
void MainWindow::on_checkBox_all_size_stateChanged(int arg1) {
    bool is_found = false;

    switch (arg1) {
    case Qt::Checked:
        for (auto& figure : figures_) {
            std::visit([this, &is_found](auto& fig) {
                // Если current_figure_ равен not_defined_, выделяем все фигуры
                if (current_figure_ == FigureType::not_defined_) {
                    fig.SetPen(QColor(QString("#e9a000")), 5); // Выделяем цветом
                    is_found = true;
                }
                // Иначе выделяем только те фигуры, которые соответствуют типу current_figure_
                else if (fig.GetFigureType() == current_figure_) {
                    fig.SetPen(QColor(QString("#e9a000")), 5); // Выделяем цветом
                    is_found = true;
                }

                fig.Show(scene.get()); // Обновляем отображение фигуры на сцене
            }, figure);
        }

        // Если ни одна фигура не была выделена, показываем предупреждение
        if (!is_found) {
            QMessageBox::warning(this, "Фигуры не выделены", "Проверьте схождение выбранного типа фигуры с тем типом, что в данный момент находится на холсте.");
            ui->checkBox_all_size->setCheckState(Qt::Unchecked); // Сбрасываем флажок
        } else {
            // Если выбран чек-бокс «Все», запрещаем ввод индекса конкретной фигуры
            ui->lineEdit_index_size->setReadOnly(true);
            ClearLineEdit(); // Очищаем поля ввода
        }
        break;

    case Qt::Unchecked:
        // Сбрасываем стиль для всех фигур
        for (auto& figure : figures_) {
            std::visit([this](auto& fig) {
                fig.SetPen(QColor(QString("#7b6f5d")), 3); // Возвращаем стандартный цвет
                fig.Show(scene.get()); // Обновляем отображение фигуры на сцене
            }, figure);
        }

        // Снова разрешаем ввод индекса фигуры для поиска
        ui->lineEdit_index_size->setReadOnly(false);
        break;
    }
}
```
