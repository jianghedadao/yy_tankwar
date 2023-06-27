#include "ctank.h"
myRect::myRect():points{QPoint(0,0),QPoint(0,0),QPoint(0,0),QPoint(0,0)}{}
myRect::~myRect(){}
void myRect::updateRect(QPoint&& center,int length,int width,int angle){
    double d1[4]={0.5,0.5,-0.5,-0.5};
    double d2[4]={-0.5,0.5,-0.5,0.5};
    for(int i=0;i<4;i++){
        QPointF tmpP=QPointF(QPointF(center)+QPointF(d1[i]*double(length),d2[i]*double(width)));
        double px=tmpP.rx();
        double py=tmpP.ry();
        points[i]=center+QPoint((px-double(center.rx()))*cos((double)angle/180*pi)-(py-double(center.ry()))*sin((double)angle/180*pi)
                           ,(px-double(center.rx()))*sin((double)angle/180*pi)+(py-double(center.ry()))*cos((double)angle/180*pi));
    }
}
bool myRect::checkInside(QPoint&p){
    //
    return false;
}
QString myRect::getPoints(){
    QString str="Rect:";
    for(int i=0;i<4;i++){
        str+="(";
        str+=QString::number(points[i].rx());
        str+=",";
        str+=QString::number(points[i].ry());
        str+=") ";
    }
    return str;
}

CTank::CTank(QWidget *parent,int color_)
    : QLabel(parent),v(1),tankRect()
{
    //初始化坦克的角度，坐标，速度,所占据的矩形
    angle=0;
    x=rand()%(parent->width()-60);
    y=rand()%(parent->height()-60);
    tankRect.updateRect(QPoint(x+30,y+30),50,30,angle);
    //初始化坦克按钮按下的情况
    for(int i=0;i<4;i++){
        keyPressedCondition[i]=false;
    }
    //加载性感坦克图
    color=color_;
    image=new QImage;
    if(color_==GREEN){
       image->load("C:\\new_tank\\Tank_War_0\\images\\greentank.png");
    }else if(color_==RED){
        image->load("C:\\new_tank\\Tank_War_0\\images\\redtank.png");
    }

}
QImage* CTank::getImage(){
    return image;
}
QString CTank::getRect(){
    return tankRect.getPoints()+"angle:"+QString::number(angle);
}
int CTank::getx(){
    return x;
}
int CTank::gety(){
    return y;
}
int CTank::getangle(){
    return angle;
}
bool* CTank::getKeyPressed(){
    return keyPressedCondition;
}
CTank::~CTank(){
    delete image;
}
void CTank::changeKeyPressed(bool *newcondition){
    for(int i=0;i<4;i++){
        keyPressedCondition[i]=newcondition[i];
    }
}
void CTank::changePosition(){
    //调用这个函数，根据键盘按钮的情况更新坦克的方向和位置
    if((keyPressedCondition[RIGHT]&&!keyPressedCondition[DOWN])
        ||(keyPressedCondition[LEFT]&&keyPressedCondition[DOWN])){
        angle+=0.5;
    }
    if((keyPressedCondition[LEFT]&&!keyPressedCondition[DOWN])
        ||(keyPressedCondition[RIGHT]&&keyPressedCondition[DOWN])){
        angle-=0.5;
    }
    if(keyPressedCondition[UP]){
        y+=v*sin((double)angle/180*pi);
        x+=v*cos((double)angle/180*pi);
    }
    if(keyPressedCondition[DOWN]){
        y-=v*sin((double)angle/180*pi);
        x-=v*cos((double)angle/180*pi);
    }
    if(angle>360)angle=angle-360;
    if(angle<0){
        angle=360+angle;
    }
    tankRect.updateRect(QPoint(x+30,y+30),50,30,angle);
}

int CTank::get_X_B(){
    return (tankRect.points[0].x()+tankRect.points[1].x())/2;
}
int CTank::get_Y_B(){
    return (tankRect.points[0].y()+tankRect.points[1].y())/2;
}
