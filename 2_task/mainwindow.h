#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once

#include "ellipse.h"
#include "rectangle.h"
#include "square.h"
#include "line.h"
#include "ring.h"
#include "circle.h"
#include "domain.h"

#include <random>
#include <variant>
#include <QMainWindow>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // using FigureVariant = std::variant<Rectangle, Square, Ellipse, Line, Ring>;
    using FigureVariant = std::variant<Rectangle, Square, Ellipse, Line, Ring, Circle>;

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_random_create_clicked();

    void on_pushButton_ok_create_clicked();

    void on_pushButton_search_size_clicked();

    void on_pushButton_random_size_clicked();

    void on_pushButton_ok_size_clicked();

    void on_checkBox_all_size_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;

    std::unique_ptr<QGraphicsScene> scene;
    FigureType current_figure_ = FigureType::not_defined_;

    // Здесь хранятся фигуры для изменения уже созданных объектов
    std::vector<FigureVariant> figures_;

    void FillComboBox();
    void SetLineEditSettings();
    void ClearLineEdit();

    void MoveFigure(FigureVariant& figure, int dx, int dy) {
        std::visit([dx, dy](auto& fig) { fig.MoveTo(dx, dy); }, figure);
    }

    void SetFigureSize(FigureVariant& figure, int w, int h) {
        std::visit([w, h](auto& fig) {
            // if constexpr (std::is_same_v<std::decay_t<decltype(fig)>, Triangle>) {
                // fig.SetSize(w, h, {fig.GetX(), fig.GetY()}); // Используем SetSize для Polygon
            // }
            // else {
                fig.SetSize(w, h); // Для остальных фигур используем стандартный SetSize
            // }
        }, figure);
    }

    void ShowFigure(FigureVariant& figure, QGraphicsScene* scene) {
        std::visit([scene](auto& fig) { fig.Show(scene); }, figure);
    }

    int GetRandomNumber(const int min, const int max) const;

    FigureVariant CreateFigure(FigureType type, int x, int y, int w, int h);

    bool CoordsIsCorrect(const int x, const int y) const;
    bool SizeIsCorrect(const int w, const int h) const;
    bool MoveIsCorrect(const int x, const int y, const int w, const int h, const int dx, const int dy) const;

    bool NumberIsCorrect(const int num) const;

    bool ApplyChangesToFigure(FigureVariant& figure, int dx, int dy, int new_w, int new_h, bool size_fields_filled, bool coord_fields_filled);

    std::tuple<int, int, int, int> GetCorrectFigure() const;
};
#endif // MAINWINDOW_H
