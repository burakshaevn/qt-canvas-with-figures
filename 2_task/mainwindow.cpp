#include "mainwindow.h"
#include "./ui_mainwindow.h"

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

    FillComboBox();
    SetLineEditSettings();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Заполняем выпадающий список доступными фигурами для выбора
void MainWindow::FillComboBox(){
    ui->comboBox->addItem("Не выбрано");
    ui->comboBox->setCurrentText("Не выбрано");
    ui->comboBox->addItem("Эллипс");
    ui->comboBox->addItem("Прямоугольник");
    ui->comboBox->addItem("Квадрат");
    ui->comboBox->addItem("Линия");
    ui->comboBox->addItem("Кольцо");
}

void MainWindow::SetLineEditSettings() {
    QList<QLineEdit*> lineEdits = findChildren<QLineEdit*>();

    for (QLineEdit* lineEdit : lineEdits) {
        if (lineEdit->parentWidget() == ui->page_2) { // Убедитесь, что родитель - это page_2
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
        if (lineEdit->parentWidget() == ui->page_2) {
            lineEdit->clear();
        }
    }
}

int MainWindow::GetRandomNumber(const int min, const int max) const {
    static std::mt19937 engine{ std::random_device{}() };
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(engine);
}

MainWindow::FigureVariant MainWindow::CreateFigure(FigureType type, int x, int y, int w, int h) {
    switch (type) {
    case FigureType::ellipse_:
        return FigureVariant(Ellipse(x, y, w / 2, h / 2)); // Явно создаем std::variant с Ellipse
    case FigureType::rectangle_:
        return FigureVariant(Rectangle(x, y, w, h)); // Явно создаем std::variant с Rectangle
    case FigureType::square_:
        return FigureVariant(Square(x, y, std::min(w, h))); // Явно создаем std::variant с Square
    case FigureType::line_:
        return FigureVariant(Line(x, y, w, h)); // Явно создаем std::variant с Line
    case FigureType::ring_:
        return FigureVariant(Ring(x, y, w / 2, h / 2, w / 4, h / 4)); // Явно создаем std::variant с Line
    default:
        throw std::invalid_argument("Unknown figure type");
    }
}

bool MainWindow::CoordsIsCorrect(const int x, const int y) const {
    return x >= 0 && x <= ui->graphicsView->width() &&
           y >= 0 && y <= ui->graphicsView->height();
}
bool MainWindow::SizeIsCorrect(const int w, const int h) const {
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

// Возвращает корректные размеры и координаты для текущего типа фигуры
std::tuple<int, int, int, int> MainWindow::GetCorrectFigure() const {
    const int minSize = 10;
    const int maxWidth = ui->graphicsView->width();
    const int maxHeight = ui->graphicsView->height();

    int x = 0;
    int y = 0;
    int w = 0;
    int h = 0;

    while (true) {
        if (current_figure_ == FigureType::square_) {
            w = h = GetRandomNumber(minSize, std::min(maxWidth, maxHeight) / 2);
            int maxX = ui->graphicsView->width() - w;
            int maxY = ui->graphicsView->height() - h;
            x = GetRandomNumber(0, maxX);
            y = GetRandomNumber(0, maxY);
        }
        else {
            w = GetRandomNumber(minSize, maxWidth);
            h = GetRandomNumber(minSize, maxHeight);
            int maxX = (ui->graphicsView->width() - w) / 2;
            int maxY = (ui->graphicsView->height() - h) / 2;
            x = GetRandomNumber(0, maxX);
            y = GetRandomNumber(0, maxY);
        }
        if (MoveIsCorrect(x, y, w, h, 0, 0)){
            return {x, y, w, h};
        }
        else{
            continue;
        }
    }
    return {0, 0, 0, 0};
}

// Если из выпадающего списка выбран любой элемент, кроме пункта «Не выбрано»,
// то разрешаем перейти к окнам создания, редактирования размеров и координат
void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    ClearLineEdit();  // Очистка всех Input-полей

    current_figure_ = FigureType::not_defined_; // Сброс текущего типа фигуры

    switch (index) {
    case 0: // «Не выбрано»
        current_figure_ = FigureType::not_defined_;
        break;
    case 1: // «Эллипс»
        current_figure_ = FigureType::ellipse_;
        break;
    case 2: // «Прямоугольник»
        current_figure_ = FigureType::rectangle_;
        break;
    case 3: // «Квадрат»
        current_figure_ = FigureType::square_;
        break;
    case 4: // «Линия»
        current_figure_ = FigureType::line_;
        break;
    case 5: // «Кольцо»
        current_figure_ = FigureType::ring_;
        break;
    default:
        QMessageBox::warning(this, "Ошибка", "Неизвестный тип фигуры.");
        break;
    }

    // Если выбран конкретный тип, дополнительно активируем StackWidget
    if (current_figure_ != FigureType::not_defined_) {
        ui->stackedWidget->setCurrentIndex(1);  // Переключение к отображению создания/редактирования
    }
}

void MainWindow::on_pushButton_random_create_clicked() {
    auto [x, y, w, h] = GetCorrectFigure();
    // ui->lineEdit_count->setText(QString::number(GetRandomNumber(2, 20)));
    ui->lineEdit_x->setText(QString::number(x));
    ui->lineEdit_y->setText(QString::number(y));
    ui->lineEdit_w->setText(QString::number(w));
    if (current_figure_ == FigureType::square_){
        ui->lineEdit_h->setText(QString::number(w));
    }
    else{
        ui->lineEdit_h->setText(QString::number(h));
    }
}

void MainWindow::on_pushButton_ok_create_clicked() {
    if (current_figure_ != FigureType::not_defined_) {
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
                    FigureVariant new_figure = CreateFigure(current_figure_, x, y, w, h);

                    if (MoveIsCorrect(x, y, w, h, 0, 0)) {
                        ShowFigure(new_figure, scene.get());
                        figures_.push_back(new_figure);
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
            ClearLineEdit();
        }

        else if (count > 0 && !coords_and_size_){
            for (size_t i = 0; i < count; ++i) {
                auto [x, y, w, h] = GetCorrectFigure();

                try {
                    FigureVariant new_figure = CreateFigure(current_figure_, x, y, w, h);
                    ShowFigure(new_figure, scene.get());
                    figures_.push_back(new_figure);
                }
                catch (const std::exception& e) {
                    QMessageBox::critical(this, "Ошибка", e.what());
                    return;
                }
            }
            ClearLineEdit();
        }

    }
    else {
        QMessageBox::critical(this, "Ошибка", "Невозможно выполнить операцию. Выберите тип фигуры.");
    }
}

void MainWindow::on_pushButton_search_size_clicked() {
    // Проверяем, есть ли фигуры в массиве
    if (figures_.empty()) {
        QMessageBox::critical(this, "Ошибка", "Массив фигур пуст. Добавьте фигуры для поиска.");
        return;
    }

    // Получаем индекс из поля ввода
    QString index_string = ui->lineEdit_index_size->text();
    if (index_string.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите корректный индекс.");
        return;
    }

    bool is_found = false;
    size_t target_index = static_cast<size_t>(index_string.toInt() - 1); // Индексация с 0
    size_t current_type_count = 0; // Счётчик для индекса конкретного типа

    // Проходим по всем фигурам
    for (size_t i = 0; i < figures_.size(); ++i) {
        // Устанавливаем стандартный цвет пера для всех фигур
        std::visit([this](auto& fig) { fig.SetPen(QColor(QString("#7b6f5d")), 3); }, figures_[i]);

        // Проверяем, соответствует ли фигура выбранному типу (если тип выбран)
        bool is_type_match = (current_figure_ == FigureType::not_defined_) ||
                             (std::visit([](auto& fig) { return fig.GetFigureType(); }, figures_[i]) == current_figure_);

        if (is_type_match) {
            // Если текущий счётчик совпадает с целевым индексом
            if (current_type_count == target_index) {
                // Устанавливаем значения в поля ввода
                std::visit([this](auto& fig) {
                    ui->lineEdit_current_x->setText(QString::number(fig.GetX()));
                    ui->lineEdit_current_y->setText(QString::number(fig.GetY()));
                    ui->lineEdit_current_w->setText(QString::number(fig.GetW()));
                    ui->lineEdit_current_h->setText(QString::number(fig.GetH()));
                }, figures_[i]);

                // Устанавливаем выделенный цвет пера
                std::visit([this](auto& fig) { fig.SetPen(QColor(QString("#e9a000")), 5); }, figures_[i]);
                is_found = true;
            }
            current_type_count++; // Увеличиваем счётчик для этого типа или общего списка
        }

        // Отображаем фигуру на сцене
        std::visit([this](auto& fig) { fig.Show(scene.get()); }, figures_[i]);
    }

    // Если фигура не найдена, выводим сообщение об ошибке
    if (!is_found) {
        QMessageBox::warning(this, "Ошибка", "Фигура типа " + ui->comboBox->currentText() +" с номером " + QString::number(target_index + 1) + " не найдена.");
    }
}

void MainWindow::on_pushButton_random_size_clicked()
{
    auto [x, y, w, h] = GetCorrectFigure();
    ui->lineEdit_dx->setText(QString::number(x));
    ui->lineEdit_dy->setText(QString::number(y));
}

void MainWindow::on_pushButton_ok_size_clicked() {
    // Проверяем, есть ли фигуры в массиве
    if (figures_.empty()) {
        QMessageBox::critical(this, "Ошибка", "Список фигур пуст.");
        return;
    }

    // Проверяем, заполнены ли поля для изменения размеров
    bool size_fields_filled = !ui->lineEdit_new_w->text().isEmpty() && !ui->lineEdit_new_h->text().isEmpty();
    // Проверяем, заполнены ли поля для смещения
    bool coord_fields_filled = !ui->lineEdit_dx->text().isEmpty() && !ui->lineEdit_dy->text().isEmpty();

    // Считываем значения из полей ввода
    int dx = coord_fields_filled ? ui->lineEdit_dx->text().toInt() : 0;
    int dy = coord_fields_filled ? ui->lineEdit_dy->text().toInt() : 0;
    int new_w = size_fields_filled ? ui->lineEdit_new_w->text().toInt() : 0;
    int new_h = size_fields_filled ? ui->lineEdit_new_h->text().toInt() : 0;

    // Проверяем, выбран ли чек-бокс "Все"
    bool is_all_figures_selected = ui->checkBox_all_size->isChecked();

    if (is_all_figures_selected) {
        // Обрабатываем все фигуры
        for (auto& figure : figures_) {
            // Если выбрано "Не выбрано", обрабатываем все фигуры
            // Иначе обрабатываем только фигуры выбранного типа
            if (current_figure_ == FigureType::not_defined_ ||
                std::visit([](auto& fig) { return fig.GetFigureType(); }, figure) == current_figure_) {
                if (ApplyChangesToFigure(figure, dx, dy, new_w, new_h, size_fields_filled, coord_fields_filled)) {
                    ShowFigure(figure, scene.get());
                }
            }
        }
    } else {
        // Обрабатываем только одну фигуру по индексу
        QString index_string = ui->lineEdit_index_size->text();
        if (index_string.isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Введите корректный индекс.");
            return;
        }

        size_t index = static_cast<size_t>(index_string.toInt() - 1);

        // Фильтруем фигуры по типу, если тип выбран
        std::vector<size_t> filtered_indices;
        for (size_t i = 0; i < figures_.size(); ++i) {
            if (current_figure_ == FigureType::not_defined_ ||
                std::visit([](auto& fig) { return fig.GetFigureType(); }, figures_[i]) == current_figure_) {
                filtered_indices.push_back(i);
            }
        }

        // Проверяем, что индекс находится в пределах отфильтрованного списка
        if (index < filtered_indices.size()) {
            size_t actual_index = filtered_indices[index];
            auto& figure = figures_.at(actual_index);

            if (ApplyChangesToFigure(figure, dx, dy, new_w, new_h, size_fields_filled, coord_fields_filled)) {
                ShowFigure(figure, scene.get());
            }
        } else {
            QMessageBox::warning(this, "Ошибка", "Фигура типа " + ui->comboBox->currentText() + " с номером " + QString::number(index + 1) + " не найдена.");
        }
    }
}

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

QVector<int> ParseIndices(const QString& input) {
    QVector<int> indices;
    QStringList parts = input.split(",");

    for (const QString& part : parts) {
        bool ok;
        int index = part.toInt(&ok);
        if (ok) {
            indices.append(index);
        }
    }

    return indices;
}
