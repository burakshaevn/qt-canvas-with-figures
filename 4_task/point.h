#ifndef POINT_H
#define POINT_H

#include <QDebug>

class Point {
public:
    Point(const int x = 0, const int y = 0)
        : x_(x)
        , y_(y)
    {
        qDebug() << "Создана точка: X=" << x << ", Y=" << y;
    }

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

    inline void MoveToX(const int x) {
        x_ += x;
    }
    inline void MoveToY(const int y) {
        y_ += y;
    }

private:
    int x_;
    int y_;
};


#endif // POINT_H
