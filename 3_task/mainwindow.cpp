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
    ui->comboBox->addItem("Круг");
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

bool MainWindow::CoordsIsCorrect(const int x, const int y) const{
    return x >= 0 && x <= ui->graphicsView->width() &&
           y >= 0 && y <= ui->graphicsView->height();
}
bool MainWindow::SizeIsCorrect(const int w, const int h) const{
    return w > 0 && h > 0 &&
           w <= ui->graphicsView->width() &&
           h <= ui->graphicsView->height();
}
bool MainWindow::MoveIsCorrect(Figure* figure, const int x, const int y, const int w, const int h, const int dx, const int dy) const {
    if (figure->GetFigureType() == FigureType::circle_ or figure->GetFigureType() == FigureType::ring_) {
        return (x + dx) >= 0 && (y + dy) >= 0 &&
               ((x + w) + dx) <= scene->width() &&
               ((y + w) + dy) <= scene->height();
    }
    else if (figure->GetFigureType() == FigureType::ellipse_) {
        return (x + dx) >= 0 && (y + dy) >= 0 &&
               ((x + w) + dx) <= scene->width() &&
               ((y + h) + dy) <= scene->height();
    }
    else if (figure->GetFigureType() == FigureType::rectangle_) {
        return (x + dx) >= 0 && (y + dy) >= 0 &&
               ((x + w) + dx) <= scene->width() &&
               ((y + h) + dy) <= scene->height();
    }
    else if (figure->GetFigureType() == FigureType::square_) {
        return (x + dx) >= 0 && (y + dy) >= 0 &&
               ((x + w) + dx) <= scene->width() &&
               ((y + w) + dy) <= scene->height();
    }
    else if (figure->GetFigureType() == FigureType::line_) {
        int x1_new = x + dx;
        int y1_new = y + dy;
        int x2_new = x + w + dx;
        int y2_new = y + h + dy;
        return x1_new >= 0 && x1_new <= scene->width() &&
               y1_new >= 0 && y1_new <= scene->height() &&
               x2_new >= 0 && x2_new <= scene->width() &&
               y2_new >= 0 && y2_new <= scene->height();
    }
    return false; // если тип фигуры неизвестен
}

std::tuple<int, int, int, int> MainWindow::GetCorrectFigure() const {
    const int minSize = 10;
    const int maxWidth = ui->graphicsView->width();
    const int maxHeight = ui->graphicsView->height();

    int x = 0;
    int y = 0;
    int w = 0;
    int h = 0;

    while (true) {
        if (current_figure_.get()->GetFigureType() == FigureType::circle_ or current_figure_.get()->GetFigureType() == FigureType::ring_) {
            int minRadius = minSize / 2;
            int maxRadius = std::min(maxWidth, maxHeight) / 4;
            int radius = GetRandomNumber(minRadius, maxRadius);
            w = h = radius * 2;
            int maxX = maxWidth - w;
            int maxY = maxHeight - h;
            x = GetRandomNumber(0, maxX);
            y = GetRandomNumber(0, maxY);
        }
        else if (current_figure_.get()->GetFigureType() == FigureType::square_) {
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
        if (MoveIsCorrect(current_figure_.get(), x, y, w, h, 0, 0)){
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
    ClearLineEdit();
    ui->checkBox_all_size->setCheckState(Qt::Unchecked);

    // Используем std::make_unique для создания объекта
    switch (index) {
    case 0:
        current_figure_.reset();
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
    }

    if (index > 0) {
        ui->stackedWidget->setCurrentIndex(1);
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

void MainWindow::on_pushButton_ok_create_clicked()
{
    if (current_figure_ != nullptr){
        size_t count = static_cast<size_t>(ui->lineEdit_count->text().toInt());

        int x{};
        int y{};
        int w{};
        int h{};

        // Изначально считаем, что все фигуры отрисовались с корректными размерами и позициями.
        // Если переменная будет равна true, по завершение цикла разово выведем сообщение об ошибках, если они были
        bool has_been_mistakes = false;
        for (size_t i = 0; i < count; ++i) {
            if (count == 1) {
                x = ui->lineEdit_x->text().toInt();
                y = ui->lineEdit_y->text().toInt();
                w = ui->lineEdit_w->text().toInt();
                h = ui->lineEdit_h->text().toInt();
            }
            else {
                auto [x_, y_, w_, h_] = GetCorrectFigure();
                x = x_;
                y = y_;
                w = w_;
                h = h_;
            }
            std::unique_ptr<Figure> new_figure_;
            switch (current_figure_.get()->GetFigureType()) {
            case FigureType::not_defined_:
                new_figure_ = nullptr;
                break;
            case FigureType::circle_:
                new_figure_ = std::make_unique<Circle>(x, y, w / 2);
                break;
            case FigureType::ellipse_:
                new_figure_ = std::make_unique<Ellipse>(x, y, w / 2, h / 2);
                break;
            case FigureType::rectangle_:
                new_figure_ = std::make_unique<Rectangle>(x, y, w, h);
                break;
            case FigureType::square_:
                new_figure_ = std::make_unique<Square>(x, y, w);
                break;
            case FigureType::line_:
                new_figure_ = std::make_unique<Line>(x, y, w, h);
                break;
            case FigureType::ring_:
                new_figure_ = std::make_unique<Ring>(x, y, w / 2);
                break;
            }

            if (MoveIsCorrect(new_figure_.get(), new_figure_->GetX(), new_figure_->GetY(), new_figure_->GetW(), new_figure_->GetH(), 0, 0)) {
                new_figure_->MoveTo(0, 0);
                new_figure_->Show(scene.get());
                figures_.push_back(std::move(new_figure_));
            }
            else {
                has_been_mistakes = true;
            }
        }
        if (has_been_mistakes){
            QMessageBox::warning(this, "Ошибка", "Некоторые фигуры с некорректными координатами не были отображены.");
        }
        ClearLineEdit();
    }
    else{
        QMessageBox::critical(this, "Ошибка", "Невозможно выполнить операцию. Выберите тип фигуры.");
    }
}

void MainWindow::on_pushButton_trash_clicked() {
    if (!figures_.empty()) {
        auto it = figures_.begin();
        bool anyDeleted = false;

        while (it != figures_.end()) {
            if (current_figure_ == nullptr || typeid(**it) == typeid(*current_figure_)) {
                (it->get())->RemoveFromScene(scene.get()); // Удаление из сцены
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

void MainWindow::on_pushButton_eye_clicked() {
    if (!figures_.empty()) {
        for (auto& figure : figures_) {
            // Если current_figure_ == nullptr, обрабатываем все фигуры, иначе только фигуры того же типа
            if (current_figure_ == nullptr || figure.get()->GetFigureType() == current_figure_.get()->GetFigureType()) {
                figure->SetVisible(!figure->GetVisible());
                figure->Show(scene.get());
            }
        }
    } else {
        QMessageBox::critical(this, "Ошибка", "Массив фигур пуст. Добавьте фигуры для обработки.");
    }
}

void MainWindow::on_pushButton_search_size_clicked() {
    if (!figures_.empty()) {
        QString index_string = ui->lineEdit_index_size->text();
        if (!index_string.isEmpty()) {
            bool is_found = false;
            size_t target_index = static_cast<size_t>(index_string.toInt() - 1);
            size_t current_type_count = 0;  // Счетчик для индекса конкретного типа

            // Если current_figure_ не установлен, просто выберем из всех фигур
            for (size_t i = 0; i < figures_.size(); ++i) {
                figures_.at(i)->SetPen(QColor(QString("#7b6f5d")), 3);

                // Проверяем, если current_figure_ установлен, фильтруем по типу текущей фигуры
                if (current_figure_ == nullptr || figures_.at(i).get()->GetFigureType() == current_figure_.get()->GetFigureType()) {
                    if (current_type_count == target_index) {
                        ui->lineEdit_current_x->setText(QString::number(figures_.at(i)->GetX()));
                        ui->lineEdit_current_y->setText(QString::number(figures_.at(i)->GetY()));
                        ui->lineEdit_current_w->setText(QString::number(figures_.at(i)->GetW()));
                        ui->lineEdit_current_h->setText(QString::number(figures_.at(i)->GetH()));
                        figures_.at(i)->SetPen(QColor(QString("#e9a000")), 5);
                        is_found = true;
                    }
                    current_type_count++;  // Увеличиваем счетчик для этого типа или общего списка
                }
                figures_.at(i)->Show(scene.get());
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
    if (current_figure_ != nullptr or (current_figure_ == nullptr and !figures_.empty())){
        if (figures_.empty()) {
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
        int new_w = size_fields_filled ? ui->lineEdit_new_w->text().toInt() : figures_.at(0)->GetW();
        int new_h = size_fields_filled ? ui->lineEdit_new_h->text().toInt() : figures_.at(0)->GetH();

        // Если сейчас работаем над кругом, кольцом или квадратом, то
        // приравниваем новую ширину к новой высоте. Таким образом,
        // нам неважно, что пользователь указал в new h,
        // так как если это одна из перечисленных трёх фигур,
        // то new_h будет равен new_w, так как у таких фигур должны быть равные диаметры/высоты.
        if (current_figure_ != nullptr) {
            FigureType tmp = current_figure_.get()->GetFigureType();
            if (tmp == FigureType::circle_ ||
                tmp == FigureType::ring_ ||
                tmp == FigureType::square_) {
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

            for (size_t i = 0; i < figures_.size(); ++i) {
                figures_.at(i)->SetPen(QColor(QString("#7b6f5d")), 3);

                // Проверка на совпадение индекса и типа фигуры
                if (current_figure_ == nullptr || figures_.at(i).get()->GetFigureType() == current_figure_.get()->GetFigureType()) {
                    if (current_type_count == index) {
                        if (MoveIsCorrect(figures_.at(i).get(), figures_.at(i).get()->GetX(), figures_.at(i).get()->GetY(), new_w, new_h, dx, dy)){
                            if (coord_fields_filled) {
                                figures_.at(i)->MoveTo(dx, dy);
                            }
                            if (size_fields_filled) {
                                figures_.at(i)->SetSize(new_w, new_h);
                            }
                            ui->lineEdit_current_x->setText(QString::number(figures_.at(i)->GetX()));
                            ui->lineEdit_current_y->setText(QString::number(figures_.at(i)->GetY()));
                            ui->lineEdit_current_w->setText(QString::number(figures_.at(i)->GetW()));
                            ui->lineEdit_current_h->setText(QString::number(figures_.at(i)->GetH()));
                        }
                        else {
                            has_been_mistakes = true;
                        }
                        figures_.at(i)->SetPen(QColor(QString("#e9a000")), 5);
                        is_found = true;
                    }
                    ++current_type_count;
                }
                figures_.at(i)->Show(scene.get());
            }

            if (!is_found) {
                QMessageBox::warning(this, "Ошибка", "Фигура с номером " + QString::number(index + 1) + " не найдена.");
            }
        }
        else {
            for (size_t i = 0; i < figures_.size(); ++i) {
                // Проверка на совпадение типа фигуры
                if (current_figure_ == nullptr || typeid(*figures_.at(i)) == typeid(*current_figure_)) {

                    // Проверяем, будет ли корректна конкретная фигура figures_.at(i),
                    // если в ней поменять X, Y, Width или Height. Если хоть один будет =false,
                    // то в конце программы выйдет уведомление, что над некоторыми фигурами не были выполнены операции из за не пройденных тестов на корректность
                    bool result1 = MoveIsCorrect(figures_.at(i).get(), figures_.at(i)->GetX(), figures_.at(i)->GetY(),
                                                figures_.at(i)->GetW(), figures_.at(i)->GetH(),
                                                dx, dy);
                    bool result2 = MoveIsCorrect(figures_.at(i).get(), figures_.at(i)->GetX(), figures_.at(i)->GetY(), new_w, new_h, dx, dy);

                    if (coord_fields_filled and result1) {
                        figures_.at(i)->MoveTo(dx, dy);
                        figures_.at(i)->Show(scene.get());
                    }
                    if (size_fields_filled and result2) {
                        figures_.at(i)->SetSize(new_w, new_h);
                        figures_.at(i)->Show(scene.get());
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
}

void MainWindow::on_checkBox_all_size_stateChanged(int arg1)
{
    bool is_found = false;
    switch (arg1) {
    case Qt::Checked:
        for (size_t i = 0; i < figures_.size(); ++i) {
            auto figure = figures_.at(i).get();

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

            figure->Show(scene.get());
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
        for (size_t i = 0; i < figures_.size(); ++i) {
            figures_.at(i)->SetPen(QColor(QString("#7b6f5d")), 3);
            figures_.at(i)->Show(scene.get());
        }
        // Снова разрешаем ввод в индекс фигуры для поиска, так как работа идёт не над всеми фигурами в массиве,
        // а над конкретной
        ui->lineEdit_index_size->setReadOnly(false);
        break;
    }
}

