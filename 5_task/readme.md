# Использование полиморфных объектных указателей

Задачи, которые необходимо реализовать в л/р 5:

1. **В разделе реализации основного модуля объявить массив из 20-30 полиморфных указателей, т.е. элементов базового типа Figure.**

В классе MainWindow содержится вектор `std::vector<std::unique_ptr<Figure>> figures_;`, который будет содержать все фигуры. Количество фигур в этой структуре будет зависеть от значения в поле «Колич.»

2. **В основное меню ввести команду Массив с подкомандами Создать, Уничтожить, Стереть, Показать и Переместить.**

Чтобы создать фигуры всех доступных типов, необходимо выбрать в списке фигур «Все типы» и указать количество.  
<div align="center">
  <img src="https://github.com/user-attachments/assets/a3c7d4eb-8ab1-4b53-bfbf-d022be6a3867" alt="image"> 
</div> 

3. **Написать обработчик команды Создать, который должен в цикле создать случайный набор из 20-30 фигур со случайными параметрами и сохранить указатель на каждый из них как элемент массива.**

Логику реализует метод `void MainWindow::on_pushButton_ok_create_clicked();`. Если `current_figure_` имеет значение `nullptr`, это значит, что идёт обработка всех элементов в массиве фигур. Если `current_figure_` имеет конкретный тип фигуры, значит, обрабатываться будет только она.

4. **Написать обработчик команды Показать для прорисовки всего изображения за счет прохода по массиву с вызовом для каждого элемента массива виртуального метода Show.**

В функции `void MainWindow::CreateRandomFigures();` есть следующие строки, которые реализуют это:

```cpp
void MainWindow::CreateRandomFigures() {
    // ...
	auto figure = CreateFigure(randomType, x, y, w, h); // Возвращается созданная фигура
	figure->Show(); // Показывается
	figures_.push_back(std::move(figure)); // Фигура добавляется в общий массив
	// ...
}
```

4. **Написать обработчик команды Стереть только для стирания изображения всех фигур без уничтожения объектов, что дает возможность повторно нарисовать изображение.**

Логику реализует кнопка:
<div align="center">
  <img src="https://github.com/user-attachments/assets/2678462f-9b9a-4e64-95a4-c3896ef62420" alt="image"> 
</div> 

```cpp
void MainWindow::on_pushButton_eye_clicked() {
    if (!figures_.empty()) {
        for (auto& figure : figures_) {
            // Если current_figure_ == nullptr, обрабатываем все фигуры, иначе только фигуры того же типа
            if (current_figure_ == nullptr || figure.get()->GetFigureType() == current_figure_.get()->GetFigureType()) {
                figure->SetVisible(!figure->GetVisible());
                figure->Show();
            }
        }
    } else {
        QMessageBox::critical(this, "Ошибка", "Массив фигур пуст. Добавьте фигуры для обработки.");
    }
}
```

6. **Написать обработчик команды Уничтожить для стирания изображения всех фигур и уничтожения соответствующих объектов; для этого в цикле для каждого указателя вызывается метод Show и затем метод Free.**

Логику реализует кнопка:
<div align="center">
  <img src="https://github.com/user-attachments/assets/57a8ea0f-2f78-4d23-a2f2-ec23c458d6fa" alt="image"> 
</div> 

```cpp
void MainWindow::on_pushButton_trash_clicked() {
    if (!figures_.empty()) {
        auto it = figures_.begin();
        bool anyDeleted = false;

        while (it != figures_.end()) {
            if (current_figure_ == nullptr || typeid(**it) == typeid(*current_figure_)) {
                (it->get())->RemoveFromScene(); // Удаление из сцены
                it = figures_.erase(it); // Получаем следующий итератор
                anyDeleted = true;
                ui->checkBox_all_size->setCheckState(Qt::Unchecked);
            } else {
                ++it;
            }
        }
        if (!anyDeleted) {
            QMessageBox::information(this, "Информация", "Фигуры указанного типа отсутствуют для удаления.");
        }
    } else {
        QMessageBox::critical(this, "Ошибка", "Массив фигур пуст. Добавьте фигуры для удаления.");
    }
}
```

7. **Написать код, который перемещает все изображение влево-вправо-вверх-вниз по нажатию соответствующей клавиши. Для простоты шаг перемещения можно взять равным 10 пикселам.** 

Метод `keyPressEvent` — это **слот (обработчик событий)**, который вызывается, когда пользователь нажимает клавишу на клавиатуре. Этот метод является частью системы событий Qt и используется для обработки событий клавиатуры.

Реагирует на кнопки **W, A, S, D** и **↑, ←, →, ↓**.
```cpp
void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (figures_.empty()) {
        QMainWindow::keyPressEvent(event);
        return;
    }

    int dx = 0;
    int dy = 0;

    // Определяем направление перемещения
    switch (event->key()) {
    case Qt::Key_Left: case Qt::Key_A:
        dx = -10; // Перемещение влево на 10 пикселей
        break;
    case Qt::Key_Right: case Qt::Key_D:
        dx = 10; // Перемещение вправо на 10 пикселей
        break;
    case Qt::Key_Up: case Qt::Key_W:
        dy = -10; // Перемещение вверх на 10 пикселей
        break;
    case Qt::Key_Down: case Qt::Key_S:
        dy = 10; // Перемещение вниз на 10 пикселей
        break;
    default:
        return;
    }

    for (auto& figure : figures_) {
        if (MoveIsCorrect(figure->GetX(), figure->GetY(), figure->GetW(), figure->GetH(), dx, dy)) {
            figure->MoveTo(dx, dy);
        }
    }
}
```

8. **Добавить в меню команду для выборочного перемещения только объектов-фигур некоторой подиерархии. Обработчик этой команды должен как обычно пройти по массиву объектных указателей, но при этом выполнить проверку динамического типа каждого указателя на принадлежность к заданной подиерархии с помощью операции is.**

Чтобы управлять всеми фигурами как единым целым, нужно чтобы в окне «Фигура» оставался вариант «Все фигуры». Тогда редактирование размеров, перемещение, показ и удаление фигур будут доступны для каждой в массиве фигур. 
