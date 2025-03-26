#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <random>
#include "ellipse.h"
#include "circle.h"
#include "rectangle.h"
#include "square.h"
#include "line.h"
#include "ring.h"
#include "house.h"
#include "trapezoid.h"
#include "rhomb.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , scene(nullptr)
{
    ui->setupUi(this);
    this->setFixedSize(1300, 760);

    // Создаем сцену с фиксированными размерами
    scene = std::make_unique<QGraphicsScene>(0, 0, 1260, 557, this);
    ui->graphicsView->setScene(scene.get());

    // Отключаем прокрутку холста.
    // То есть, мы не можем прокручивать его как интернет карту. Потому что иначе бы
    // это привело к бесконенчому холсту. А так у него есть рамки благодаря отключению прокрутки.
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Устанавливаем размер QGraphicsView, то есть,
    // задаём размеры нашему холсту
    ui->graphicsView->setFixedSize(1260, 557);

    ChooseContainerType();
    FillComboBox();
    SetLineEditSettings();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    std::visit([this, event](auto& container) {
        if (container.empty()) {
            QMainWindow::keyPressEvent(nullptr);
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

        for (size_t i = 0; i < container.size(); ++i) {
            if (MoveIsCorrect(container.at(i).GetX(), container.at(i).GetY(), container.at(i).GetW(), container.at(i).GetH(), dx, dy)) {
                container.at(i).MoveTo(dx, dy);
            }
        }
    }, figures_.value());
}

// Заполняем выпадающий список доступными фигурами для выбора
void MainWindow::FillComboBox(){
    ui->comboBox->addItem("Все типы");
    ui->comboBox->setCurrentText("Все типы");
    ui->comboBox->addItem("Эллипс");
    ui->comboBox->addItem("Окружность");
    ui->comboBox->addItem("Прямоугольник");
    ui->comboBox->addItem("Квадрат");
    ui->comboBox->addItem("Линия");
    ui->comboBox->addItem("Кольцо");
    ui->comboBox->addItem("Дом");
    ui->comboBox->addItem("Трапеция");
    ui->comboBox->addItem("Ромб");
}

void MainWindow::SetLineEditSettings() {
    QList<QLineEdit*> lineEdits = findChildren<QLineEdit*>();

    for (QLineEdit* lineEdit : lineEdits) {
        if (lineEdit->parentWidget() == ui->page) {
            lineEdit->setMaxLength(5);
            lineEdit->setAlignment(Qt::AlignCenter);
        }
    }
    // Сообщаем, что эти лейблы lineEdit доступны только для чтения,
    // туда будет выводиться информация о текущих значениях X, Y, Width и Height
    ui->lineEdit_current_x->setReadOnly(true);
    ui->lineEdit_current_y->setReadOnly(true);
    ui->lineEdit_current_w->setReadOnly(true);
    ui->lineEdit_current_h->setReadOnly(true);
}

void MainWindow::ClearLineEdit(){
    // Проходимся по всем лейблам, в которые можно вводить текст (они имеют тип QLineEdit*),
    // и чистим их от содержимого
    QList<QLineEdit*> lineEdits = findChildren<QLineEdit*>();
    for (QLineEdit* lineEdit : lineEdits) {
        if (lineEdit->parentWidget() == ui->page) {
            lineEdit->clear();
        }
    }
}

void MainWindow::ChooseContainerType() {
    QStringList options = {"DynamicArray", "DynamicList"};
    bool ok;
    QString choice = QInputDialog::getItem(this, "Выбор контейнера", "Выберите контейнер:", options, 0, false, &ok);

    if (ok) {
        if (choice == "DynamicArray") {
            figures_.emplace(std::in_place_type_t<DynamicArray>{});
        } else if (choice == "DynamicList") {
            figures_.emplace(std::in_place_type_t<DynamicList>{});
        }
    } else {
        QMessageBox::warning(this, "Ошибка", "Контейнер не выбран. Приложение будет закрыто.");
        exit(0);
    }
}

void MainWindow::CreateRandomFigures() {
    size_t count = static_cast<size_t>(ui->lineEdit_count->text().toInt());

    if (count == 0) {
        QMessageBox::warning(this, "Ошибка", "Укажите количество фигур.");
        return;
    }

    std::vector<FigureType> all_figure_types = {
        FigureType::ellipse_,
        FigureType::circle_,
        FigureType::rectangle_,
        FigureType::square_,
        FigureType::ring_,
        FigureType::house_,
        FigureType::trapezoid_,
        FigureType::rhomb_
    };

    for (size_t i = 0; i < count; ++i) {
        size_t index = GetRandomNumber(0, all_figure_types.size() - 1);

        switch (index) {
        case 0:
            current_figure_ = std::make_unique<Ellipse>();
            current_figure_.get()->SetFigureType(FigureType::ellipse_);
            break;
        case 1:
            current_figure_ = std::make_unique<Circle>();
            current_figure_.get()->SetFigureType(FigureType::circle_);
            break;
        case 2:
            current_figure_ = std::make_unique<Rectangle>();
            current_figure_.get()->SetFigureType(FigureType::rectangle_);
            break;
        case 3:
            current_figure_ = std::make_unique<Square>();
            current_figure_.get()->SetFigureType(FigureType::square_);
            break;
        case 4:
            current_figure_ = std::make_unique<Ring>();
            current_figure_.get()->SetFigureType(FigureType::ring_);
            break;
        case 5:
            current_figure_ = std::make_unique<House>();
            current_figure_.get()->SetFigureType(FigureType::house_);
            break;
        case 6:
            current_figure_ = std::make_unique<Trapezoid>();
            current_figure_.get()->SetFigureType(FigureType::trapezoid_);
            break;
        case 7:
            current_figure_ = std::make_unique<Rhomb>();
            current_figure_.get()->SetFigureType(FigureType::rhomb_);
            break;
        }

        // Случайный выбор типа фигуры
        FigureType randomType = all_figure_types[index];

        // Генерация случайных координат и размеров
        auto [x, y, w, h] = GetCorrectFigure();

        try {
            if (!CoordsIsCorrect(x, y) || !SizeIsCorrect(w, h)) {
                QMessageBox::warning(this, "Ошибка", "Фигура выходит за пределы холста.");
                continue;
            }

            auto figure = CreateFigure(randomType, x, y, w, h);
            figure->Show();
            std::visit([&](auto& container) {
                container.push_back(std::move(figure));
            }, figures_.value());
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Ошибка", e.what());
        }
    }
    current_figure_ = nullptr;
}

std::unique_ptr<Figure> MainWindow::CreateFigure(FigureType type, int x, int y, int w, int h){
    switch (type) {
    case FigureType::ellipse_:
        return std::make_unique<Ellipse>(scene.get(), x, y, w / 2, h / 2);
    case FigureType::circle_:
        return std::make_unique<Circle>(scene.get(), x, y, w / 2, w / 2);
    case FigureType::rectangle_:
        return std::make_unique<Rectangle>(scene.get(), x, y, w, h);
    case FigureType::square_:
        return std::make_unique<Square>(scene.get(), x, y, std::min(w, h));
    case FigureType::line_:
        return std::make_unique<Line>(scene.get(), x, y, w, h);
    case FigureType::ring_:
        return std::make_unique<Ring>(scene.get(), x, y, w / 2, w / 4);
    case FigureType::house_:
        return std::make_unique<House>(scene.get(), x, y, std::min(w, h));
    case FigureType::trapezoid_:
        return std::make_unique<Trapezoid>(scene.get(), x, y, w, w / 2, h);
    case FigureType::rhomb_:
        return std::make_unique<Rhomb>(scene.get(), x, y, w, h);
    default:
        throw std::invalid_argument("Unknown figure type");
    }
}

bool MainWindow::CoordsIsCorrect(const int x, const int y) const{
    return x >= 0 && x <= ui->graphicsView->width() &&
           y >= 0 && y <= ui->graphicsView->height();
}
bool MainWindow::SizeIsCorrect(const int w, const int h) const{
    return w > 0 && h > 0 &&
           w <= ui->graphicsView->width() &&
           h <= ui->graphicsView->height();
}

bool MainWindow::MoveIsCorrect(const int x, const int y, const int w, const int h, const int dx, const int dy) const {
    // Новые координаты после перемещения
    int new_x = x + dx;
    int new_y = y + dy;

    // Проверяем, что новые координаты не выходят за пределы сцены
    bool is_x_valid = new_x >= 0 && (new_x + w) <= scene->width();
    bool is_y_valid = new_y >= 0 && (new_y + h) <= scene->height();

    return is_x_valid && is_y_valid;
}

std::tuple<int, int, int, int> MainWindow::GetCorrectFigure() const {
    const int minSize = 10;
    const int maxWidth = ui->graphicsView->width();
    const int maxHeight = ui->graphicsView->height();

    int x = 0;
    int y = 0;
    int w = 0;
    int h = 0;

    // Генерация случайных размеров
    switch (current_figure_->GetFigureType()) {
    case FigureType::square_:
        w = h = GetRandomNumber(minSize, std::min(maxWidth, maxHeight) / 2);
        break;
    case FigureType::ring_:
    case FigureType::circle_:
        w = h = GetRandomNumber(minSize, std::min(maxWidth, maxHeight) / 2);
        break;
    case FigureType::house_:
        w = GetRandomNumber(minSize, maxWidth);
        h = GetRandomNumber(minSize, maxHeight / 2);
        break;
    default:
        w = GetRandomNumber(minSize, maxWidth / 3);
        h = GetRandomNumber(minSize, maxHeight / 3);
        break;
    }

    // Генерация случайных координат
    int maxX = ui->graphicsView->width() - w;
    int maxY = ui->graphicsView->height() - h;

    // Для дома учитываем высоту крыши
    if (current_figure_->GetFigureType() == FigureType::house_) {
        int roofHeight = h / 2;
        maxY = std::max(0, ui->graphicsView->height() - (h + roofHeight));
    }

    x = GetRandomNumber(0, maxX);
    y = GetRandomNumber(0, maxY);

    return {x, y, w, h};
}

// Если из выпадающего списка выбран любой элемент, кроме пункта «Не выбрано»,
// то разрешаем перейти к окнам создания, редактирования размеров и координат
void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    ClearLineEdit();
    ui->checkBox_all_size->setCheckState(Qt::Unchecked);
    ui->checkBox_all_rotate->setCheckState(Qt::Unchecked);

    if (index >= 0) {
        ui->stackedWidget->setCurrentIndex(1);
    }

    // Используем std::make_unique для создания объекта
    switch (index) {
    case 0:
        current_figure_.reset();
        current_figure_ = nullptr;
        break;
    case 1:
        current_figure_ = std::make_unique<Ellipse>();
        current_figure_.get()->SetFigureType(FigureType::ellipse_);
        break;
    case 2:
        current_figure_ = std::make_unique<Circle>();
        current_figure_.get()->SetFigureType(FigureType::circle_);
        break;
    case 3:
        current_figure_ = std::make_unique<Rectangle>();
        current_figure_.get()->SetFigureType(FigureType::rectangle_);
        break;
    case 4:
        current_figure_ = std::make_unique<Square>();
        current_figure_.get()->SetFigureType(FigureType::square_);
        break;
    case 5:
        current_figure_ = std::make_unique<Line>();
        current_figure_.get()->SetFigureType(FigureType::line_);
        break;
    case 6:
        current_figure_ = std::make_unique<Ring>();
        current_figure_.get()->SetFigureType(FigureType::ring_);
        break;
    case 7:
        current_figure_ = std::make_unique<House>();
        current_figure_.get()->SetFigureType(FigureType::house_);
        break;
    case 8:
        current_figure_ = std::make_unique<Trapezoid>();
        current_figure_.get()->SetFigureType(FigureType::trapezoid_);
        break;
    case 9:
        current_figure_ = std::make_unique<Rhomb>();
        current_figure_.get()->SetFigureType(FigureType::rhomb_);
        break;
    }
}

void MainWindow::on_pushButton_random_create_clicked() {
    auto [x, y, w, h] = GetCorrectFigure();
    ui->lineEdit_count->setText(QString::number(GetRandomNumber(2, 20)));
    ui->lineEdit_x->setText(QString::number(x));
    ui->lineEdit_y->setText(QString::number(y));
    ui->lineEdit_w->setText(QString::number(w));
    if (current_figure_.get()->GetFigureType() == FigureType::circle_ || current_figure_.get()->GetFigureType() == FigureType::square_){
        ui->lineEdit_h->setText(QString::number(w));
    }
    else{
        ui->lineEdit_h->setText(QString::number(h));
    }
}

void MainWindow::on_pushButton_ok_create_clicked() {
    if (current_figure_ != nullptr) {
        size_t count = static_cast<size_t>(ui->lineEdit_count->text().toInt());

        bool coords_and_size_ = !ui->lineEdit_x->text().isEmpty() && !ui->lineEdit_y->text().isEmpty() && !ui->lineEdit_w->text().isEmpty() && !ui->lineEdit_h->text().isEmpty();

        if (count > 0 && coords_and_size_) {
            bool has_been_mistakes = false;
            for (size_t i = 0; i < count; ++i) {
                int x = ui->lineEdit_x->text().toInt();
                int y = ui->lineEdit_y->text().toInt();
                int w = ui->lineEdit_w->text().toInt();
                int h = ui->lineEdit_h->text().toInt();

                try {
                    auto new_figure = CreateFigure(current_figure_->GetFigureType(), x, y, w, h);

                    if (MoveIsCorrect(x, y, w, h, 0, 0)) {
                        new_figure->Show();
                        std::visit([&](auto& container) {
                            container.push_back(std::move(new_figure));
                        }, figures_.value());
                    } else {
                        has_been_mistakes = true;
                    }
                }
                catch (const std::exception& e) {
                    QMessageBox::critical(this, "Ошибка", e.what());
                    return;
                }
            }

            if (has_been_mistakes) {
                QMessageBox::warning(this, "Ошибка", "Некоторые фигуры с некорректными координатами не были отображены.");
            }
        }
        else if (count > 0 && !coords_and_size_) {
            for (size_t i = 0; i < count; ++i) {
                auto [x, y, w, h] = GetCorrectFigure();

                try {
                    auto new_figure = CreateFigure(current_figure_->GetFigureType(), x, y, w, h);
                    new_figure->Show();
                    std::visit([&](auto& container) {
                        container.push_back(std::move(new_figure));
                    }, figures_.value());
                }
                catch (const std::exception& e) {
                    QMessageBox::critical(this, "Ошибка", e.what());
                    return;
                }
            }
        }
    }
    else {
        CreateRandomFigures();
    }
    ClearLineEdit();
}

void MainWindow::on_pushButton_trash_clicked() {
    std::visit([&](auto& container) {
        container.Iterate(ActionType::CLEAR);
        // if (!container.empty()) {
        //     bool anyDeleted = false;
        //     for (size_t i = 0; i < container.size(); ++i) {
        //         if (current_figure_ == nullptr || container.at(i).GetFigureType() == current_figure_->GetFigureType()) {
        //             container.at(i).RemoveFromScene();
        //             container.erase(i);
        //             --i;
        //             anyDeleted = true;
        //             ui->checkBox_all_size->setCheckState(Qt::Unchecked);
        //         }
        //     }
        //     if (!anyDeleted) {
        //         QMessageBox::information(this, "Информация", "Фигуры указанного типа отсутствуют для удаления.");
        //     }
        // }
        // else {
        //     QMessageBox::critical(this, "Ошибка", "Массив фигур пуст. Добавьте фигуры для удаления.");
    }, figures_.value());
}

void MainWindow::on_pushButton_eye_clicked() {
    std::visit([&](auto& container) {
        if (!container.empty()) {
            for (size_t i = 0; i < container.size(); ++i) {
                // Если current_figure_ == nullptr, обрабатываем все фигуры, иначе только фигуры того же типа
                if (current_figure_ == nullptr || container.at(i).GetFigureType() == current_figure_.get()->GetFigureType()) {
                    container.at(i).SetVisible(!container.at(i).GetVisible());
                    container.at(i).Show();
                }
            }
        } else {
            QMessageBox::critical(this, "Ошибка", "Массив фигур пуст. Добавьте фигуры для обработки.");
        }
    }, figures_.value());
}

void MainWindow::on_pushButton_search_size_clicked() {
    std::visit([&](auto& container) {
        if (!container.empty()) {
            QString index_string = ui->lineEdit_index_size->text();
            if (!index_string.isEmpty()) {
                bool is_found = false;
                size_t target_index = static_cast<size_t>(index_string.toInt() - 1);
                size_t current_type_count = 0;  // Счетчик для индекса конкретного типа

                // Если current_figure_ не установлен, просто выберем из всех фигур
                for (size_t i = 0; i < container.size(); ++i) {
                    container.at(i).SetPen(QColor(QString("#7b6f5d")), 3);

                    // Проверяем, если current_figure_ установлен, фильтруем по типу текущей фигуры
                    if (current_figure_ == nullptr || container.at(i).GetFigureType() == current_figure_.get()->GetFigureType()) {
                        if (current_type_count == target_index) {
                            ui->lineEdit_current_x->setText(QString::number(container.at(i).GetX()));
                            ui->lineEdit_current_y->setText(QString::number(container.at(i).GetY()));
                            ui->lineEdit_current_w->setText(QString::number(container.at(i).GetW()));
                            ui->lineEdit_current_h->setText(QString::number(container.at(i).GetH()));
                            container.at(i).SetPen(QColor(QString("#e9a000")), 5);
                            is_found = true;
                        }
                        current_type_count++;  // Увеличиваем счетчик для этого типа или общего списка
                    }
                    container.at(i).Show();
                }

                if (!is_found) {
                    QMessageBox::warning(this, "Ошибка", "Фигура с данным индексом не найдена.");
                }
            } else {
                QMessageBox::warning(this, "Ошибка", "Введите корректный индекс.");
            }
        } else {
            QMessageBox::critical(this, "Ошибка", "Массив фигур пуст. Добавьте фигуры для поиска.");
        }
    }, figures_.value());
}

void MainWindow::on_pushButton_random_size_clicked()
{
    auto [x, y, w, h] = GetCorrectFigure();
    ui->lineEdit_dx->setText(QString::number(x));
    ui->lineEdit_dy->setText(QString::number(y));
    ui->lineEdit_new_w->setText(QString::number(w));
    ui->lineEdit_new_h->setText(dynamic_cast<Circle*>(current_figure_.get()) ? QString::number(w) : QString::number(h));
}

void MainWindow::on_pushButton_ok_size_clicked()
{
    std::visit([&](auto& container) {
        if (current_figure_ != nullptr or (current_figure_ == nullptr and !container.empty())){
            if (container.empty()) {
                QMessageBox::critical(this, "Ошибка", "Значение поля «Индекс» не может быть пустым.");
                return;
            }

            // Проверка заполненности полей размеров
            bool size_fields_filled = !ui->lineEdit_new_w->text().isEmpty() && !ui->lineEdit_new_h->text().isEmpty();
            if (!size_fields_filled && (!ui->lineEdit_new_w->text().isEmpty() || !ui->lineEdit_new_h->text().isEmpty())) {
                QMessageBox::warning(this, "Ошибка", "Для изменения полей Width и Height необходимо указать значение каждого из них.");
                return;
            }

            // Проверка заполненности полей смещения dx и dy
            bool coord_fields_filled = !ui->lineEdit_dx->text().isEmpty() && !ui->lineEdit_dy->text().isEmpty();
            if (!coord_fields_filled && (!ui->lineEdit_dx->text().isEmpty() || !ui->lineEdit_dy->text().isEmpty())) {
                QMessageBox::warning(this, "Ошибка", "Для изменения полей dx и dy необходимо указать значение каждого из них.");
                return;
            }

            // Если поля заполнены, считываем их значения
            int dx = coord_fields_filled ? ui->lineEdit_dx->text().toInt() : 0;
            int dy = coord_fields_filled ? ui->lineEdit_dy->text().toInt() : 0;
            int new_w = size_fields_filled ? ui->lineEdit_new_w->text().toInt() : container.at(0).GetW();
            int new_h = size_fields_filled ? ui->lineEdit_new_h->text().toInt() : container.at(0).GetH();

            // Если сейчас работаем над кругом, кольцом или квадратом, то
            // приравниваем новую ширину к новой высоте. Таким образом,
            // нам неважно, что пользователь указал в new h,
            // так как если это одна из перечисленных трёх фигур,
            // то new_h будет равен new_w, так как у таких фигур должны быть равные диаметры/высоты.
            if (current_figure_ != nullptr) {
                FigureType tmp = current_figure_.get()->GetFigureType();
                if (tmp == FigureType::circle_ || tmp == FigureType::ring_ || tmp == FigureType::square_) {
                    new_h = new_w;
                }
            }

            // Проверка корректности значений
            if (size_fields_filled && !SizeIsCorrect(new_w, new_h)) {
                QMessageBox::warning(this, "Ошибка", "Некорректный ввод полей с координатами или размерами.");
                return;
            }

            bool has_been_mistakes = false;

            if (!ui->checkBox_all_size->isChecked()) {
                bool is_found = false;
                size_t index = static_cast<size_t>(ui->lineEdit_index_size->text().toInt() - 1);
                size_t current_type_count = 0;  // Счетчик для индекса конкретного типа

                for (size_t i = 0; i < container.size(); ++i) {
                    container.at(i).SetPen(QColor(QString("#7b6f5d")), 3);

                    // Проверка на совпадение индекса и типа фигуры
                    if (current_figure_ == nullptr || container.at(i).GetFigureType() == current_figure_.get()->GetFigureType()) {
                        if (current_type_count == index) {
                            if (MoveIsCorrect(container.at(i).GetX(), container.at(i).GetY(), new_w, new_h, dx, dy)){
                                if (coord_fields_filled) {
                                    container.at(i).MoveTo(dx, dy);
                                }
                                if (size_fields_filled) {
                                    container.at(i).SetSize(new_w, new_h);
                                }
                                ui->lineEdit_current_x->setText(QString::number(container.at(i).GetX()));
                                ui->lineEdit_current_y->setText(QString::number(container.at(i).GetY()));
                                ui->lineEdit_current_w->setText(QString::number(container.at(i).GetW()));
                                ui->lineEdit_current_h->setText(QString::number(container.at(i).GetH()));
                            }
                            else {
                                has_been_mistakes = true;
                            }
                            container.at(i).SetPen(QColor(QString("#e9a000")), 5);
                            is_found = true;
                        }
                        ++current_type_count;
                    }
                    container.at(i).Show();
                }

                if (!is_found) {
                    QMessageBox::warning(this, "Ошибка", "Фигура с номером " + QString::number(index + 1) + " не найдена.");
                }
            }
            else {
                for (size_t i = 0; i < container.size(); ++i) {
                    // Проверка на совпадение типа фигуры
                    if (current_figure_ == nullptr || typeid(container.at(i)) == typeid(*current_figure_)) {
                    // if (current_figure_ == nullptr || typeid(*figures_.value().at(i)) == typeid(*current_figure_)) {

                        // Проверяем, будет ли корректна конкретная фигура figures_.value().at(i),
                        // если в ней поменять X, Y, Width или Height. Если хоть один будет =false,
                        // то в конце программы выйдет уведомление, что над некоторыми фигурами не были выполнены операции из за не пройденных тестов на корректность
                        bool result1 = MoveIsCorrect(container.at(i).GetX(), container.at(i).GetY(), container.at(i).GetW(), container.at(i).GetH(), dx, dy);
                        bool result2 = MoveIsCorrect(container.at(i).GetX(), container.at(i).GetY(), new_w, new_h, dx, dy);

                        if (coord_fields_filled and result1) {
                            container.at(i).MoveTo(dx, dy);
                        }
                        if (size_fields_filled and result2) {
                            container.at(i).SetSize(new_w, new_h);
                        }
                        if (!result1 || !result2){
                            continue;
                        }
                    }
                }
            }

            if (has_been_mistakes) {
                QMessageBox::warning(this, "Ошибка", "Некоторые фигуры с некорректными координатами не были отображены.");
            }
        }
        else {
            QMessageBox::critical(this, "Ошибка", "Невозможно выполнить создание. Выберите тип фигуры.");
        }
    }, figures_.value());
}

void MainWindow::on_checkBox_all_size_stateChanged(int arg1)
{
    std::visit([&](auto& container) {
        bool is_found = false;
        switch (arg1) {
        case Qt::Checked:
            for (size_t i = 0; i < container.size(); ++i) {
                auto figure = container.Get(i);

                // Если current_figure_ равен nullptr, выделяем все фигуры
                if (current_figure_ == nullptr) {
                    figure->SetPen(QColor(QString("#e9a000")), 5);
                    is_found = true;
                }
                // Иначе выделяем только те фигуры, которые соответствуют типу current_figure_
                else if (typeid(*figure) == typeid(*current_figure_)) {
                    figure->SetPen(QColor(QString("#e9a000")), 5);
                    is_found = true;
                }

                figure->Show();
            }
            // Если выбран чек-бокс «Все», значит запрещаем осуществлять ввод индекса конкретной фигуры
            // до тех пор, пока чек-бокс не перейдёт в состояние Qt::Unchecked
            ui->lineEdit_index_size->setReadOnly(true);
            ClearLineEdit();

            if (!is_found){
                QMessageBox::warning(this, "Фигуры не выделены", "Проверьте схождение выбранного типа фигуры с тем типом, что в данный момент находится на холсте.");
                ui->checkBox_all_size->setCheckState(Qt::Unchecked);
            }
            break;

        case Qt::Unchecked:
            // Сбрасываем стиль для всех фигур
            for (size_t i = 0; i < container.size(); ++i) {
                container.at(i).SetPen(QColor(QString("#7b6f5d")), 3);
                container.at(i).Show();
            }
            // Снова разрешаем ввод в индекс фигуры для поиска, так как работа идёт не над всеми фигурами в массиве,
            // а над конкретной
            ui->lineEdit_index_size->setReadOnly(false);
            break;
        }
    }, figures_.value());
}

void MainWindow::on_pushButton_search_for_rotate_clicked()
{
    std::visit([&](auto& container) {
        if (!container.empty()) {
            QString index_string = ui->lineEdit_rotate->text();
            if (!index_string.isEmpty()) {
                bool is_found = false;
                size_t target_index = static_cast<size_t>(index_string.toInt() - 1);
                size_t current_type_count = 0;  // Счетчик для индекса конкретного типа

                // Если current_figure_ не установлен, просто выберем из всех фигур
                for (size_t i = 0; i < container.size(); ++i) {
                    container.at(i).SetPen(QColor(QString("#7b6f5d")), 3);

                    // Проверяем, если current_figure_ установлен, фильтруем по типу текущей фигуры
                    if (current_figure_ == nullptr || container.at(i).GetFigureType() == current_figure_.get()->GetFigureType()) {
                        if (current_type_count == target_index) {
                            container.at(i).SetPen(QColor(QString("#e9a000")), 5);
                            is_found = true;
                        }
                        current_type_count++;  // Увеличиваем счетчик для этого типа или общего списка
                    }
                    container.at(i).Show();
                }

                if (!is_found) {
                    QMessageBox::warning(this, "Ошибка", "Фигура с данным индексом не найдена.");
                }
            } else {
                QMessageBox::warning(this, "Ошибка", "Введите корректный индекс.");
            }
        } else {
            QMessageBox::critical(this, "Ошибка", "Массив фигур пуст. Добавьте фигуры для поиска.");
        }
    }, figures_.value());
}

void MainWindow::on_checkBox_all_rotate_stateChanged(int arg1)
{
    std::visit([&](auto& container) {
        bool is_found = false;
        switch (arg1) {
        case Qt::Checked:
            for (size_t i = 0; i < container.size(); ++i) {
                auto figure = container.Get(i);

                // Если current_figure_ равен nullptr, выделяем все фигуры
                if (current_figure_ == nullptr) {
                    figure->SetPen(QColor(QString("#e9a000")), 5);
                    is_found = true;
                }
                // Иначе выделяем только те фигуры, которые соответствуют типу current_figure_
                else if (typeid(*figure) == typeid(*current_figure_)) {
                    figure->SetPen(QColor(QString("#e9a000")), 5);
                    is_found = true;
                }

                figure->Show();
            }
            // Если выбран чек-бокс «Все», значит запрещаем осуществлять ввод индекса конкретной фигуры
            // до тех пор, пока чек-бокс не перейдёт в состояние Qt::Unchecked
            ui->lineEdit_rotate->setReadOnly(true);
            ClearLineEdit();

            if (!is_found){
                QMessageBox::warning(this, "Фигуры не выделены", "Проверьте схождение выбранного типа фигуры с тем типом, что в данный момент находится на холсте.");
                ui->checkBox_all_size->setCheckState(Qt::Unchecked);
            }
            break;

        case Qt::Unchecked:
            // Сбрасываем стиль для всех фигур
            for (size_t i = 0; i < container.size(); ++i) {
                container.at(i).SetPen(QColor(QString("#7b6f5d")), 3);
                container.at(i).Show();
            }
            // Снова разрешаем ввод в индекс фигуры для поиска, так как работа идёт не над всеми фигурами в массиве,
            // а над конкретной
            ui->lineEdit_rotate->setReadOnly(false);
            break;
        }
    }, figures_.value());
}

void MainWindow::on_pushButton_rotate_left_clicked() {
    std::visit([&](auto& container) {
        if (container.empty()) {
            QMessageBox::critical(this, "Ошибка", "Массив фигур пуст. Добавьте фигуры для поворота.");
            return;
        }

        // Если выбран чек-бокс "Все фигуры"
        if (ui->checkBox_all_rotate->isChecked()) {
            for (size_t i = 0; i < container.size(); ++i) {
                // Проверяем, совпадает ли тип фигуры с текущим выбранным типом (если current_figure_ не nullptr)
                if (current_figure_ == nullptr || container.at(i).GetFigureType() == current_figure_->GetFigureType()) {
                    container.at(i).Rotate(-90);
                }
            }
        }
        // Если выбран конкретный индекс
        else if (!ui->lineEdit_rotate->text().isEmpty()) {
            size_t target_index = static_cast<size_t>(ui->lineEdit_rotate->text().toInt() - 1);
            size_t current_type_count = 0;  // Счетчик для индекса конкретного типа

            for (size_t i = 0; i < container.size(); ++i) {
                // Проверяем, совпадает ли тип фигуры с текущим выбранным типом (если current_figure_ не nullptr)
                if (current_figure_ == nullptr || container.at(i).GetFigureType() == current_figure_->GetFigureType()) {
                    if (current_type_count == target_index) {
                        container.at(i).Rotate(-90);
                        break;
                    }
                    current_type_count++;
                }
            }
        }
    }, figures_.value());
}

void MainWindow::on_pushButton_rotate_right_clicked()
{
    std::visit([&](auto& container) {
        if (container.empty()) {
            QMessageBox::critical(this, "Ошибка", "Массив фигур пуст. Добавьте фигуры для поворота.");
            return;
        }

        // Если выбран чек-бокс "Все фигуры"
        if (ui->checkBox_all_rotate->isChecked()) {
            for (size_t i = 0; i < container.size(); ++i) {
                // Проверяем, совпадает ли тип фигуры с текущим выбранным типом (если current_figure_ не nullptr)
                if (current_figure_ == nullptr || container.at(i).GetFigureType() == current_figure_->GetFigureType()) {
                    container.at(i).Rotate(90);
                }
            }
        }
        // Если выбран конкретный индекс
        else if (!ui->lineEdit_rotate->text().isEmpty()) {
            size_t target_index = static_cast<size_t>(ui->lineEdit_rotate->text().toInt() - 1);
            size_t current_type_count = 0;  // Счетчик для индекса конкретного типа

            for (size_t i = 0; i < container.size(); ++i) {
                // Проверяем, совпадает ли тип фигуры с текущим выбранным типом (если current_figure_ не nullptr)
                if (current_figure_ == nullptr || container.at(i).GetFigureType() == current_figure_->GetFigureType()) {
                    if (current_type_count == target_index) {
                        container.at(i).Rotate(90);
                        break;
                    }
                    current_type_count++;
                }
            }
        }
    }, figures_.value());
}

int GetRandomNumber(const int min, const int max) {
    static std::mt19937 engine{ std::random_device{}() };
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(engine);
}
