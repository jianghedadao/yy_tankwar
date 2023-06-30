#ifndef CTANK_H
#define CTANK_H

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

const int RED=1;
const int GREEN=0;
const int RIGHT=0;
const int UP=1;
const int DOWN=2;
const int LEFT=3;
const double pi = acos(-1);
//坦克的速度、角度的改变量、子弹数量
const double TANKVELOCITY=0.5;
const double DELTA_ANGLE=0.5;
const int BULLETSNUM=5;

class myRect{
private:
    QPoint points[4];
public:
    myRect();
    //给出中心，长，宽，旋转角度
    myRect(QPoint&& center,int length,int width,int angle);
    //Copy constructor
    myRect(const myRect& r);
    ~myRect();
    //以中心、旋转角度、长、宽为参数更新矩形
    void updateRect(QPoint&& center,int length,int width,int angle);
//    //判断一个点是否在矩形内部
//    bool checkInside(QPoint& p);
//    //把坐标转换成QString,用于debug
    QString getPointstr();
    QPoint* getPoints();

};

class CTank : public QLabel
{
    Q_OBJECT
public:
    explicit CTank(QWidget *parent = nullptr,int color_=GREEN);
    ~CTank();
    //改变按钮被按下的情况
    void changeKeyPressed(bool *newcondition);
    //改变坦克的位置
    void changePosition();
    void changePosition(double x,double y,double angle);
    //改变坦克的子弹数量
    void changeNumOfBullets(int delta);
    //获取坦克的颜色坐标,旋转角度,按钮按下情况
    int getcolor();
    int getNumOfBullets();
    double getx();
    double gety();
    double getangle();
    bool* getKeyPressed();
    //获取图片
    QImage* getImage();
    //获取矩形信息，用于debug
    QString getRect();
    //获取四个坐标
    QPoint* getPoints();
    //获取子弹发射的坐标
    QPointF getBulletPos();
    //判断两艘坦克是否相撞
    static bool tankCrashed(CTank* t1,CTank* t2);
private:
    double angle;//角度
    //上下左右按钮是否按下
    bool keyPressedCondition[4];
    //坦克的坐标、速度、颜色、所占据的矩形方框、拥有的子弹数量等参数
    double x;
    double y;
    const double v;
    int color;
    myRect tankRect;
    int numOfBullets;
    //QPoint[4];
    //坦克图片
    QImage* image;

signals:
private slots:

};

#endif // CTANK_H
