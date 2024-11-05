#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once

#include "figure.h"
#include "circle.h"
#include "ellipse.h"
#include "rectangle.h"
#include "square.h"
#include "line.h"

#include <random>
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

private:
    Ui::MainWindow *ui;

    std::unique_ptr<QGraphicsScene> scene;
    std::unique_ptr<Figure> current_figure_;
    std::vector<std::unique_ptr<Figure>> figures_;

    void FillComboBox();
    void SetLineEditSettings();
    void ClearLineEdit();

    int GetRandomNumber(const int min, const int max) const;

    bool CoordsIsCorrect(const int x, const int y) const;
    bool SizeIsCorrect(const int w, const int h) const;
    bool MoveIsCorrect(Figure* figure, const int x, const int y, const int w, const int h, const int move_x, const int move_y) const;
    bool NumberIsCorrect(const int num) const;
    std::tuple<int, int, int, int> GetCorrectFigure() const;
};
#endif // MAINWINDOW_H
