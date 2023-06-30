#include "ctank.h"

myRect::myRect():points{QPoint(0,0),QPoint(0,0),QPoint(0,0),QPoint(0,0)}{}
//Construct a rectangle given its center, length, width,and rotation angle.
myRect::myRect(QPoint&& center,int length,int width,int angle){
    double d1[4]={0.4,0.4,-0.5,-0.5};
    double d2[4]={-0.5,0.5,-0.5,0.5};
    for(int i=0;i<4;i++){
        QPointF tmpP=QPointF(QPointF(center)+QPointF(d1[i]*double(length),d2[i]*double(width)));
        double px=tmpP.rx();
        double py=tmpP.ry();
        points[i]=center+QPoint((px-double(center.rx()))*cos((double)angle/180*pi)-(py-double(center.ry()))*sin((double)angle/180*pi)
                                    ,(px-double(center.rx()))*sin((double)angle/180*pi)+(py-double(center.ry()))*cos((double)angle/180*pi));
    }
}
//copy constructor
myRect::myRect(const myRect& r){
    for(int i=0;i<4;i++){
        points[i]=r.points[i];
    }
}
myRect::~myRect(){}
void myRect::updateRect(QPoint&& center,int length,int width,int angle){
    double d1[4]={0.4,0.4,-0.5,-0.5};
    double d2[4]={-0.5,0.5,-0.5,0.5};
    for(int i=0;i<4;i++){
        QPointF tmpP=QPointF(QPointF(center)+QPointF(d1[i]*double(length),d2[i]*double(width)));
        double px=tmpP.rx();
        double py=tmpP.ry();
        points[i]=center+QPoint((px-double(center.rx()))*cos((double)angle/180*pi)-(py-double(center.ry()))*sin((double)angle/180*pi)
                           ,(px-double(center.rx()))*sin((double)angle/180*pi)+(py-double(center.ry()))*cos((double)angle/180*pi));
    }
}
//bool myRect::checkInside(QPoint&p){
//    //
//    return false;
//}
QString myRect::getPointstr(){
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

QPoint* myRect::getPoints(){
    return points;
}


CTank::CTank(QWidget *parent,int color_)
    : QLabel(parent),v(TANKVELOCITY),tankRect()
    ,numOfBullets(BULLETSNUM)
{
    //初始化坦克的角度，坐标，速度,所占据的矩形
    angle=rand()%360;
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
        image->load("C:/Tank_War-yxy (1)/Tank_War-yxy/Tank_War_0/images/greentank.png");
    }else if(color_==RED){
        image->load("C:/Tank_War-yxy (1)/Tank_War-yxy/Tank_War_0/images/redtank.png");
    }

}
QImage* CTank::getImage(){
    return image;
}
QString CTank::getRect(){
    return tankRect.getPointstr()+"angle:"+QString::number(angle);
}
QPoint* CTank::getPoints(){
    return tankRect.getPoints();
}
QPointF CTank::getBulletPos(){
    QPointF center(x+30,y+30);
    double d1[2]={0.6,0.6};
    double d2[2]={-0.5,0.5};
    QPointF tmppoints[2];
    for(int i=0;i<2;i++){
        QPointF tmpP=QPointF(QPointF(center)+QPointF(d1[i]*50.0,d2[i]*30.0));
        double px=tmpP.rx();
        double py=tmpP.ry();
        tmppoints[i]=center+QPoint((px-double(center.rx()))*cos((double)angle/180*pi)-(py-double(center.ry()))*sin((double)angle/180*pi)
                                    ,(px-double(center.rx()))*sin((double)angle/180*pi)+(py-double(center.ry()))*cos((double)angle/180*pi));
    }
    return (tmppoints[0]+tmppoints[1])/2;
}
int CTank::getcolor(){
    return color;
}
int CTank::getNumOfBullets(){
    return numOfBullets;
}
double CTank::getx(){
    return x;
}
double CTank::gety(){
    return y;
}
double CTank::getangle(){
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
        angle+=DELTA_ANGLE;
    }
    if((keyPressedCondition[LEFT]&&!keyPressedCondition[DOWN])
        ||(keyPressedCondition[RIGHT]&&keyPressedCondition[DOWN])){
        angle-=DELTA_ANGLE;
    }
    if(keyPressedCondition[UP]){
        y+=v*sin(angle/180*pi);
        x+=v*cos(angle/180*pi);
    }
    if(keyPressedCondition[DOWN]){
        y-=v*sin(angle/180*pi);
        x-=v*cos(angle/180*pi);
    }
    if(angle>360){
        angle-=360;
    }
    if(angle<0){
        angle=360+angle;
    }
    tankRect.updateRect(QPoint(x+30,y+30),50,30,angle);
}
void CTank::changePosition(double x,double y,double angle){
    //重载 根据给定的坐标和角度更新坦克的位置
    this->x=x;
    this->y=y;
    this->angle=angle;
    tankRect.updateRect(QPoint(x+30,y+30),50,30,angle);
}

void CTank::changeNumOfBullets(int delta){
    numOfBullets+=delta;
}

bool CTank::tankCrashed(CTank* t1,CTank* t2){
    QPoint* p1=t1->getPoints();
    QPoint* p2=t2->getPoints();
    QPolygon po1,po2;
    for(int i=0;i<4;i++){
        po1<<p1[i];
        po2<<p2[i];
    }
    return po1.intersects(po2);
}
