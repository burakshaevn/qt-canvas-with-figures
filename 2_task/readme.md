# Реализация взаимодействия классов на основе агрегации

Задачи, которые необходимо реализовать в л/р 2:

1.  **Добавить новый класс для примитивов-точек, содержащий:**  
 * два свойства для хранения координат точки;
	 ```cpp
	 private:
	    int x_;
	    int y_;
	```
 * конструктор для инициализации свойств-координат и вывода сообщения о создании объекта (это будет использоваться в дальнейшем при проверке правильности вложенных вызовов конструкторов взаимодействующих классов);
	 ```cpp
	 Point(const int x = 0, const int y = 0)
        : x_(x)
        , y_(y)
    {
        qDebug() << "Создана точка: X=" << x << ", Y=" << y;
    }
	```
 * Set/Get-методы для доступа к координатам точки.
	 ```cpp
	inline int GetX() const {
		return x_;
	}
	inline int GetY() const {
		return y_;
	}

	inline void SetX(int x) {
		x_ = x;
	}
	inline void SetY(int y) {
		y_ = y;
	}
	```
Теперь у нас есть класс Point. Его объявление и реализация хранятся в point.h, исполняемого файла point.cpp у него нет.
	 <div align="center">
	  <img src="https://github.com/user-attachments/assets/0a827b5e-042a-4774-bc55-fa1df73a60e1" alt="image" width="70%"> 
	</div> 

Теперь у нас есть класс Point. Его объявление и реализация хранятся в point.h, исполняемого файла point.cpp у него нет.
	 <div align="center">
	  <img src="https://github.com/user-attachments/assets/67eac549-e322-42f9-9c7d-defea749c216" alt="image"> 
	</div> 

2. **Внести следующие изменения в ранее созданный класс *Окружность*:**

* заменить свойства-координаты одним свойством-точкой;
	Это значит, что теперь в классе Circle за координаты у нас отвечает не две переменные: `int x_` и `int y_`, а всего одна — `Point position_`.
* реализовать два конструктора, которые, кроме стандартных операций, выполняют дополнительно:
	1. проверку значения радиуса и при необходимости - изменение его так, чтобы окружность не выходила за пределы области рисования;
		Проверка происходит в функции MoveIsCorrect класса MainWindow. Для всех фигур проверка одинаковая, кроме если тип фигуры — линия. Для неё проверка будет другой (см. в коде).
		```cpp
		bool MainWindow::MoveIsCorrect(const int x, const int y, const int w, const int h, const int dx, const int dy) const {
		    // Новые координаты после перемещения
		    int new_x = x + dx;
		    int new_y = y + dy;
		
		    // Проверяем, что новые координаты не выходят за пределы сцены
		    bool is_x_valid = new_x >= 0 && (new_x + w) <= scene->width();
		    bool is_y_valid = new_y >= 0 && (new_y + h) <= scene->height();
		
		    return is_x_valid && is_y_valid;
		}
		```
	2. вывод сообщения о создании объекта-окружности;
		Этот вывод происходит в конструкторе класса Ellipse с помощью команды qDebug() — она выводит текст на экран точно также как и cout в С++, но так как мы делаем всё это с помощью фреймворка Qt, за поток вывода у нас отвечает другая команда.
		```cpp
		Circle::Circle(int x, int y, int radius_1, const QPen& pen)
		    : position_(x, y)
		    , radius_(radius_1)
		    , pen_(pen)
		    , is_visible_(true)
		{
		    Circle_item_ = new QGraphicsEllipseItem(0, 0, radius_ * 2, radius_ * 2);
		    Circle_item_->setPen(pen_);
		    qDebug() << "Создана окружность с центром в (" << x << "," << y;
		}
		```
* в методе прорисовки окружности вместо прямого использования координат центра применить вызовы соответствующих методов класса точек;
	В методе Show теперь вызываем position_.GetX() и position_.GetY() у атрибута position_ класса Point:
	```cpp
	void Circle::Show(QGraphicsScene *scene) {
	    if (!scene) {
	        return;
	    }
	
	    if (!Circle_item_) {
	        Circle_item_ = new QGraphicsEllipseItem(0, 0, radius_ * 2, radius_ * 2);
	    }
	
	    if (Circle_item_ && !Circle_item_->scene()) {
	        scene->addItem(Circle_item_);
	    }
	
	    if (Circle_item_) {
	        Circle_item_->setPos(position_.GetX(), position_.GetY());
	        Circle_item_->setPen(pen_);
	        Circle_item_->setVisible(is_visible_);
	    }
	}
	```
* в методе перемещения окружности заменить прямую установку новых значений координат вызовом соответствующего метода класса точек.
	В классе Ellipse есть атрибут position_ класса Point. В методе MoveTo вызываем метод GetX и GetY для перемещения:
	```cpp
	void Circle::MoveTo(int dx, int dy) {
	    position_.MoveToX(dx);
	    position_.MoveToY(dy);
	    if (Circle_item_) {
	        Circle_item_->setPos(position_.GetX() - radius_, position_.GetY() - radius_);
	    }
	}
	```

3. **Создать новый класс *Кольцо*, содержащий два свойства-окружности, два конструктора с выводом сообщения, а также методы прорисовки и перемещения.**
	
    Сам класс Ring находится в заголовочном файле — ring.h, реализация его методов в ring.cpp
	<div align="center">
	  <img src="https://github.com/user-attachments/assets/0c4d6476-3d00-4292-95f5-586c33b4e510" alt="image"> 
	</div> 
	
	Свойства окружности:
	```cpp
	private:
	    Circle outer_circle_; // Внешняя окружность
	    Circle inner_circle_; // Внутренняя окружность
	```
	Два конструктора (их реализация хранится в ring.cpp, там же мы и выводим сообщение о создании окружностей):
	```cpp
	Ring();
	Ring(int x, int y, int outer_radius_1, int outer_radius_2, int inner_radius_1, int inner_radius_2, const QPen& pen = QPen(QColor("#7b6f5d"), 3));
	```
	Метод прорисовки:
	```cpp
	
	// Прорисовка кольца
	void Ring::Show(QGraphicsScene* scene) {
	    outer_circle_.Show(scene);
	
	    // Обновление позиции внутреннего круга
	    int innerX = outer_circle_.GetX() + outer_circle_.GetW() / 2 - inner_circle_.GetW() / 2;
	    int innerY = outer_circle_.GetY() + outer_circle_.GetH() / 2 - inner_circle_.GetH() / 2;
	    inner_circle_.SetX(innerX);
	    inner_circle_.SetY(innerY);
	
	    inner_circle_.Show(scene);
	}
	```
	Метод перемещения:
	```cpp
	// Перемещение кольца
	void Ring::MoveTo(int dx, int dy) {
	    outer_circle_.MoveTo(dx, dy);
	    inner_circle_.MoveTo(dx, dy);
	}
	```

4. **Внести аналогичные изменения в классы Отрезок и Прямоугольник.**
Действия, аналогичные пункту 3 выполняются в `class Line` и `class Rectangle`.

5.  **Самостоятельно придумать и реализовать 1-2 класса для манипуляций со сложными объектами, включающими более простые объекты Точка, Отрезок, Прямоугольник, Окружность.**
	Реализуем класс House, который будет создавать дом на холсте. Он включает в себя более простые объекты — Square и Line. На самом верху квадрата строится треугольник, который образует крышу дома.
	<div align="center">
	  <img src="https://github.com/user-attachments/assets/47f0bcce-81b9-409d-ac0e-282ba92c82b9" alt="image"> 
	</div> 
	Объявление класса находится в файле house.h, его реализация — house.cpp
## В чём отличие л/р №1 от л/р №2?
Здесь мы добавляем отдельный класс точек (class Point) и замена во всех классах атрибутов, которые отвечают за позиции X и Y на объект класса Point.

## Как реализована проверка корректности выполнения операции MoveTo (перемещения фигуры)?
Перемещение фигуры происходит при срабатывании сигнала `on_pushButton_ok_size_clicked` (то есть, нажатие на кнопку `pushButton_ok_size`), он же в свою очередь вызывает функцию `ApplyChangesToFigure`, где мы и проверяем корректность перемещения и новых размеров фигуры. 

```cpp
bool MainWindow::ApplyChangesToFigure(FigureVariant& figure, int dx, int dy, int new_w, int new_h, bool size_fields_filled, bool coord_fields_filled) {
    // Получаем текущие координаты и размеры фигуры
    int x = std::visit([](auto& fig) { return fig.GetX(); }, figure);
    int y = std::visit([](auto& fig) { return fig.GetY(); }, figure);
    int w = std::visit([](auto& fig) { return fig.GetW(); }, figure);
    int h = std::visit([](auto& fig) { return fig.GetH(); }, figure);

    // Если размеры не указаны, используем текущие размеры фигуры
    if (!size_fields_filled) {
        new_w = w;
        new_h = h;
    }

    // Проверяем, можно ли переместить фигуру с новыми параметрами
    if (MoveIsCorrect(x, y, new_w, new_h, dx, dy)) {
        // Если поля смещения заполнены, перемещаем фигуру
        if (coord_fields_filled) {
            MoveFigure(figure, dx, dy);
            ui->lineEdit_current_x->setText(QString::number(x + dx));
            ui->lineEdit_current_y->setText(QString::number(y + dy));
        }
        // Если поля размеров заполнены, изменяем размер фигуры
        if (size_fields_filled) {
            SetFigureSize(figure, new_w, new_h);
            ui->lineEdit_current_w->setText(QString::number(new_w));
            ui->lineEdit_current_h->setText(QString::number(new_h));
        }
        return true;
    } else {
        return false;
    }
}
```

Функция, которая в зависимости от типа фигуры, осуществляет проверку, будет ли новое положение фигуры корректным, учитывая её текущие координаты (X, Y) с размерами (W, H) для нового смещения (dx, dy):
```cpp
bool MainWindow::MoveIsCorrect(const int x, const int y, const int w, const int h, const int dx, const int dy) const {
    // Новые координаты после перемещения
    int new_x = x + dx;
    int new_y = y + dy;

    // Проверяем, что новые координаты не выходят за пределы сцены
    bool is_x_valid = new_x >= 0 && (new_x + w) <= scene->width();
    bool is_y_valid = new_y >= 0 && (new_y + h) <= scene->height();

    return is_x_valid && is_y_valid;
}
```
