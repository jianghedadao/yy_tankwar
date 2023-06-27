 #include"cbullet.h"

Bullet::Bullet(QWidget *parent,int angle_,int x_, int y_,int _color):
    QLabel(parent),angle(angle_),x(x_-5),y(y_-5),color(_color){
};

//还缺少析构！！！！！！！！！！

void Bullet::rebound(){
    return;
};

void Bullet::myMove(){
    y+=v*sin((double)angle/180*pi);
    x+=v*cos((double)angle/180*pi);
    setGeometry(x,y,size,size);
    rebound();
};
