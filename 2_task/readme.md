# Реализация взаимодействия классов на основе агрегации

Задачи, которые необходимо реализовать в л/р:

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

2. **Внести следующие изменения в ранее созданный класс *Окружность*:**

* заменить свойства-координаты одним свойством-точкой;
	Это значит, что теперь в классе Ellipse за координаты у нас отвечает не две переменные: `int x_` и `int y_`, а всего одна — `Point position_`.
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
		
			// Для линии проверяем обе точки
			if (current_figure_ == FigureType::line_) {
				int x1_new = new_x;
				int y1_new = new_y;
				int x2_new = new_x + w;
				int y2_new = new_y + h;
		
				is_x_valid = x1_new >= 0 && x1_new <= scene->width() &&
							 x2_new >= 0 && x2_new <= scene->width();
				is_y_valid = y1_new >= 0 && y1_new <= scene->height() &&
							 y2_new >= 0 && y2_new <= scene->height();
			}
		
			return is_x_valid && is_y_valid;
		}
		```
	2. вывод сообщения о создании объекта-окружности;
		Этот вывод происходит в конструкторе класса Ellipse с помощью команды qDebug() — она выводит текст на экран точно также как и cout в С++, но так как мы делаем всё это с помощью фреймворка Qt, за поток вывода у нас отвечает другая команда.
		```cpp
		Ellipse::Ellipse(int x, int y, int radius_1, int radius_2, const QPen& pen)
		    : position_(x, y)
		    , radius_1_(radius_1)
		    , radius_2_(radius_2)
		    , pen_(pen)
		    , is_visible_(true)
		{
		    ellipse_item_ = new QGraphicsEllipseItem(0, 0, radius_1_ * 2, radius_2_ * 2);
		    ellipse_item_->setPen(pen_);
		    qDebug() << "Создана окружность с центром в (" << x << "," << y;
		}
		```
* в методе прорисовки окружности вместо прямого использования координат центра применить вызовы соответствующих методов класса точек;
	В методе Show теперь вызываем position_.GetX() и position_.GetY() у атрибута position_ класса Point:
	```cpp
	void Ellipse::Show(QGraphicsScene *scene) {
	    if (!scene) {
	        return; 
	    }
	
	    if (!ellipse_item_) {
	        ellipse_item_ = new QGraphicsEllipseItem(0, 0, radius_1_ * 2, radius_2_ * 2);
	    }
	
	    if (ellipse_item_ && !ellipse_item_->scene()) {
	        scene->addItem(ellipse_item_);
	    }
	
	    if (ellipse_item_) {
	        ellipse_item_->setPos(position_.GetX(), position_.GetY());
	        ellipse_item_->setPen(pen_);
	        ellipse_item_->setVisible(is_visible_);
	    }
	}
	```
* в методе перемещения окружности заменить прямую установку новых значений координат вызовом соответствующего метода класса точек.
	В классе Ellipse есть атрибут position_ класса Point. В методе MoveTo вызываем метод GetX и GetY для перемещения:
	```cpp
	void Ellipse::MoveTo(int dx, int dy) {
		position_.MoveToX(dx);
		position_.MoveToY(dy);
		if (ellipse_item_) {
			ellipse_item_->setPos(position_.GetX() - radius_1_, position_.GetY() - radius_2_);
		}
	}
	```

3. **Создать новый класс *Кольцо*, содержащий два свойства-окружности, два конструктора с выводом сообщения, а также методы прорисовки и перемещения.**
	
    Сам класс Ring находится в заголовочном файле — ring.h, реализация его методов в ring.cpp
	<div align="center">
	  <img src="https://github.com/user-attachments/assets/14fa9b35-052c-4567-b35a-96cfdd47bf13" alt="image" width="70%"> 
	</div> 
	
	Свойства окружности:
	```cpp
	private:
	    Ellipse outer_ellipse_; // Внешняя окружность
	    Ellipse inner_ellipse_; // Внутренняя окружность
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
	    outer_ellipse_.Show(scene);
	
	    // Обновление позиции внутреннего круга
	    int innerX = outer_ellipse_.GetX() + outer_ellipse_.GetW() / 2 - inner_ellipse_.GetW() / 2;
	    int innerY = outer_ellipse_.GetY() + outer_ellipse_.GetH() / 2 - inner_ellipse_.GetH() / 2;
	    inner_ellipse_.SetX(innerX);
	    inner_ellipse_.SetY(innerY);
	
	    inner_ellipse_.Show(scene);
	}
	```
	Метод перемещения:
	```cpp
	// Перемещение кольца
	void Ring::MoveTo(int dx, int dy) {
	    outer_ellipse_.MoveTo(dx, dy);
	    inner_ellipse_.MoveTo(dx, dy);
	}
	```

4. **Внести аналогичные изменения в классы Отрезок и Прямоугольник.**
Действия, аналогичные пункту 3 выполняются в `class Line` и `class Rectangle`.

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

    // Для линии проверяем обе точки
    if (current_figure_ == FigureType::line_) {
        int x1_new = new_x;
        int y1_new = new_y;
        int x2_new = new_x + w;
        int y2_new = new_y + h;

        is_x_valid = x1_new >= 0 && x1_new <= scene->width() &&
                     x2_new >= 0 && x2_new <= scene->width();
        is_y_valid = y1_new >= 0 && y1_new <= scene->height() &&
                     y2_new >= 0 && y2_new <= scene->height();
    }

    return is_x_valid && is_y_valid;
}
```
