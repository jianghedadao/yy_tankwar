#ifndef CBULLET_H
#define CBULLET_H

#include <QObject>
#include <QLabel>
#include <cmath>
#include <QImage>
#include <QWidget>
#include "ctank.h"

//子弹的速度
const double BULLETVELOCITY=0.6;
//子弹图片的尺寸
const int size=10;

class CBullet : public QLabel
{
    Q_OBJECT
public:
    explicit CBullet(QWidget *parent = nullptr,CTank *tank = nullptr);
    int getcolor();
    double getx();
    double gety();
    double getangle();
    QImage* getimage();
    //处理子弹的移动和反弹
    void changePosition();
    void rebound(std::vector<QPolygon> Walls);
private:
    //子弹所属何种颜色的坦克，子弹的坐标，速度，角度
    int color;
    double x;
    double y;
    double v;
    double angle;
    //子弹图片
    QImage* image;

signals:

};

#endif // CBULLET_H
