#include "cbullet.h"

CBullet::CBullet(QWidget *parent,CTank *tank)
    : QLabel(parent),v(BULLETVELOCITY)
{
    color=tank->getcolor();
    angle=tank->getangle();
    x=tank->getBulletPos().x()-5;
    y=tank->getBulletPos().y()-5;
    image=new QImage;
    image->load("C:/Tank_War-yxy (1)/Tank_War-yxy/Tank_War_0/images/bullet.png");
}

int CBullet::getcolor(){
    return color;
}
double CBullet::getx(){
    return x;
}
double CBullet::gety(){
    return y;
}
QImage* CBullet::getimage(){
    return image;
}
void CBullet::changePosition(){
    y+=v*sin(angle/180*pi);
    x+=v*cos(angle/180*pi);
}
void CBullet::rebound(std::vector<QPolygon> Walls){
    int direction[4][2]={{0,-5},{5,0},{0,5},{-5,0}};
//    int direction2[4][2]={{-3,3},{3,-3},{3,3},{-3,-3}};
    QPoint Center((int)x+5,(int)y+5);
    for(int i=0;i<4;++i){
        QPoint tar;
        tar.setX(Center.x()+direction[i][0]);
        tar.setY(Center.y()+direction[i][1]);
        bool in=false;
        for(auto it:Walls){
            if(it.containsPoint(tar,Qt::WindingFill)){
                in=true;
                break;
            }
        }
        if(in){
            switch (i) {
            case 1:
                angle=180-angle;
                break;
            case 2:
                angle=-angle;
                break;
            case 3:
                angle=180-angle;
                break;
            case 4:
                angle=-angle;
                break;
            default:
                break;
            }
        }
        if(angle>360){
            angle-=360;
        }
        if(angle<0){
            angle=360+angle;
        }
    }
}
