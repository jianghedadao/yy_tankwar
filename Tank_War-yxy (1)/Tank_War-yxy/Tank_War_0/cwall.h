#ifndef CWALL_H
#define CWALL_H

#include <QObject>
#include <QLabel>
#include <QPolygon>
#include <QLine>
#include <vector>
#include "ctank.h"


class CWall : public QLabel
{
    Q_OBJECT
public:
    explicit CWall(QWidget *parent = nullptr);
    ~CWall();
    //判断坦克是否撞墙
    bool tankCrashOnWall(CTank* tank);

    void removerW(QPoint start,QPoint end);
    //返回墙
    const std::vector<QPolygon>& getWalls();
private:
    //所有的墙壁
    std::vector<QPolygon> walls;
    bool used[15][8]={0};
    const int direction[4][2]={-1,0, 0,1, 1,0, 0,-1};

signals:

};

#endif // CWALL_H
