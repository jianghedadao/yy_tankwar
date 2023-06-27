#ifndef CBULLET_H
#define CBULLET_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QImage>
#include <QPixmap>
#include <QPoint>
#include <QString>
#include <cmath>
#include <stdlib.h>
#include <time.h>

class Bullet : public QLabel
{
    Q_OBJECT
public:
/*
做一个实际位置，一个近似位置（以此判碰墙，控制位移，时间间隔调小，速度调小）

*/
    explicit Bullet(QWidget *parent = nullptr,int angle_=0,int x_=0, int y_=0,int _color=0);
    const double pi = acos(-1);
    double angle;
    const double v=0.85;
    const int size=10;
    double x;
    double y;
    int color;
    void rebound();
    void myMove();
};

#endif // CBULLET_H
