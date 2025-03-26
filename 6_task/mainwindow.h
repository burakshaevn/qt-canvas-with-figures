#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once

#include <QMainWindow>
#include <QMessageBox>
#include <QKeyEvent>
#include <QInputDialog>

#include "figure.h"
#include "dynamic_array.h"
#include "dynamic_list.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    using Container = std::variant<DynamicArray, DynamicList>;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_random_create_clicked();

    void on_pushButton_ok_create_clicked();

    void on_pushButton_trash_clicked();

    void on_pushButton_eye_clicked();

    void on_pushButton_search_size_clicked();

    void on_pushButton_random_size_clicked();

    void on_pushButton_ok_size_clicked();

    void on_checkBox_all_size_stateChanged(int arg1);

    void on_pushButton_search_for_rotate_clicked();

    void on_checkBox_all_rotate_stateChanged(int arg1);

    void on_pushButton_rotate_left_clicked();

    void on_pushButton_rotate_right_clicked();

private:
    Ui::MainWindow *ui;

    std::unique_ptr<QGraphicsScene> scene;
    std::unique_ptr<Figure> current_figure_;
    std::optional<Container> figures_; // Полиморфный контейнер

    void keyPressEvent(QKeyEvent *event) override;

    void FillComboBox();
    void SetLineEditSettings();
    void ClearLineEdit();

    void ChooseContainerType();

    void CreateRandomFigures();
    std::unique_ptr<Figure> CreateFigure(FigureType type, int x, int y, int w, int h);

    bool CoordsIsCorrect(const int x, const int y) const;
    bool SizeIsCorrect(const int w, const int h) const;
    bool MoveIsCorrect(const int x, const int y, const int w, const int h, const int move_x, const int move_y) const;
    bool ApplyChangesToFigure(std::unique_ptr<Figure>& figure, int dx, int dy, int new_w, int new_h, bool size_fields_filled, bool coord_fields_filled);

    std::tuple<int, int, int, int> GetCorrectFigure() const;
};

int GetRandomNumber(const int min, const int max);

#endif // MAINWINDOW_H
