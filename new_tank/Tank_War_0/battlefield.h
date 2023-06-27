#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include <QWidget>
#include "ctank.h"
#include <QKeyEvent>
#include <QTimer>
#include <QTransform>
#include "cbullet.h"



namespace Ui {
class Battlefield;
}

class Battlefield : public QWidget
{
    Q_OBJECT
public:
    explicit Battlefield::Battlefield(QWidget *parent=NULL);
    ~Battlefield();
    friend Bullet;
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void keyReleaseEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
private:
    Ui::Battlefield *ui;
    CTank* myTank[2];//存放红坦克、绿坦克的指针
    Bullet* mybullet[10];//存放子弹
    int BulletNumber=0;
    int nowDelBULLet=1;
    QTimer* timer;//时钟指针
    QTimer* B_move_timer;
    QTimer* B_delete_timer[10]={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
    void gameStart();
signals:
    void keyPressed();
    void keyReleased();
    void st();
private slots:
    void onTimeout();//每个3毫秒更新一次
    void op_bullet();
    void remove_bullet();

};

#endif // BATTLEFIELD_H
