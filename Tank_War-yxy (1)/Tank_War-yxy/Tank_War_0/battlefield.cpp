#include "battlefield.h"
#include "ui_battlefield.h"

Battlefield::Battlefield(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Battlefield)
{
    ui->setupUi(this);

    //加载红绿坦克
    srand((unsigned)time(NULL));
    myTank[GREEN]=new CTank(this,GREEN);
    myTank[RED]=new CTank(this,RED);
    while(true){
        if(CTank::tankCrashed(myTank[GREEN],myTank[RED])){
            delete myTank[GREEN];
            delete myTank[RED];
            myTank[GREEN]=new CTank(this,GREEN);
            myTank[RED]=new CTank(this,RED);
        }else{
            break;
        }
    }
    myTank[GREEN]->setPixmap(
        QPixmap::fromImage(*myTank[GREEN]->getImage()).transformed(QTransform().rotate(myTank[GREEN]->getangle())));
    myTank[RED]->setPixmap(
        QPixmap::fromImage(*myTank[RED]->getImage()).transformed(QTransform().rotate(myTank[RED]->getangle())));
    myTank[GREEN]->setAlignment(Qt::AlignCenter);
    myTank[RED]->setAlignment(Qt::AlignCenter);
    myTank[GREEN]->setGeometry(myTank[GREEN]->getx(),myTank[GREEN]->gety(),60,60);
    myTank[RED]->setGeometry(myTank[RED]->getx(),myTank[RED]->gety(),60,60);
    myTank[GREEN]->show();
    myTank[RED]->show();

    //设置坦克与子弹的timer
    timerForTank=new QTimer(this);
    timerForTank->setInterval(3);
    connect(timerForTank,SIGNAL(timeout()),this,SLOT(tankTimeout()));
    connect(this, SIGNAL(tankKeyPressed()), timerForTank, SLOT(start()));
    connect(this, SIGNAL(tankKeyReleased()), timerForTank, SLOT(stop()));

    timerForBullet=new QTimer(this);
    timerForBullet->setInterval(3);
    connect(timerForBullet,SIGNAL(timeout()),this,SLOT(bulletTimeout()));
    connect(this,SIGNAL(bulletKeyPressed()),timerForBullet,SLOT(start()));
    connect(this,SIGNAL(allBulletDestroyed()),timerForBullet,SLOT(stop()));

    //设置检查游戏情况的timer
    timerForChecking=new QTimer(this);
    timerForChecking->setInterval(3);
    connect(timerForChecking,SIGNAL(timeout()),this,SLOT(gameCheck()));
    timerForChecking->start();

    //construct valid walls
    walls=new CWall(this);
    walls->removerW(myTank[RED]->getPoints()[0],myTank[GREEN]->getPoints()[0]);

    int tmpcolor[2]={GREEN,RED};
    bool wallsValid=true;
    while(true){
        wallsValid=true;
        for(auto color:tmpcolor){
            if(walls->tankCrashOnWall(myTank[color])){
                delete walls;
                walls=new CWall(this);
                wallsValid=false;
                break;
            }
        }
        if(wallsValid){
            break;
        }
    }
    walls->removerW(myTank[RED]->getPoints()[0],myTank[GREEN]->getPoints()[0]);
}

void Battlefield::keyPressEvent(QKeyEvent *event)
{
    //获得之前的按钮情况
    bool* newred=new bool[4];
    bool* newgreen=new bool[4];
    bool* oldred=myTank[RED]->getKeyPressed();
    bool* oldgreen=myTank[GREEN]->getKeyPressed();
    //判断是否按下了坦克移动或者子弹发射的按键
    bool tankPressed=false,bulletPressed=false;
    for(int i=0;i<4;i++){
        newred[i]=oldred[i];
        newgreen[i]=oldgreen[i];
    }
    if (event->isAutoRepeat()) {
        event->ignore();
    } else {
        switch(event->key()){
        case Qt::Key_Right:
            newgreen[RIGHT]=true;
            tankPressed=true;
            break;
        case Qt::Key_Up:
            newgreen[UP]=true;
            tankPressed=true;
            break;
        case Qt::Key_Left:
            newgreen[LEFT]=true;
            tankPressed=true;
            break;
        case Qt::Key_Down:
            newgreen[DOWN]=true;
            tankPressed=true;
            break;
        case Qt::Key_W:
            newred[UP]=true;
            tankPressed=true;
            break;
        case Qt::Key_A:
            newred[LEFT]=true;
            tankPressed=true;
            break;
        case Qt::Key_S:
            newred[DOWN]=true;
            tankPressed=true;
            break;
        case Qt::Key_D:
            newred[RIGHT]=true;
            tankPressed=true;
            break;
        case Qt::Key_Space:
        {
            if(myTank[RED]->getNumOfBullets()){
                myTank[RED]->changeNumOfBullets(-1);
                CBullet* newBullet=new CBullet(this,myTank[RED]);
                QTimer* newDelTimer=new QTimer(this);
                newDelTimer->setInterval(6000);
                newDelTimer->start();
                connect(newDelTimer,SIGNAL(timeout()),this,SLOT(delBullet()));
                myBullets.push_back(std::make_pair(newBullet,newDelTimer));
                newBullet->setPixmap(QPixmap::fromImage(*newBullet->getimage()));
                newBullet->setAlignment(Qt::AlignCenter);
                newBullet->setGeometry(newBullet->getx(),newBullet->gety(),10,10);
                newBullet->show();
                bulletPressed=true;
            }
            break;
        }
        case Qt::Key_Return:
        {
            if(myTank[GREEN]->getNumOfBullets()){
                myTank[GREEN]->changeNumOfBullets(-1);
                CBullet* newBullet=new CBullet(this,myTank[GREEN]);
                QTimer* newDelTimer=new QTimer(this);
                newDelTimer->setInterval(6000);
                newDelTimer->start();
                connect(newDelTimer,SIGNAL(timeout()),this,SLOT(delBullet()));
                myBullets.push_back(std::make_pair(newBullet,newDelTimer));
                newBullet->setPixmap(QPixmap::fromImage(*newBullet->getimage()));
                newBullet->setAlignment(Qt::AlignCenter);
                newBullet->setGeometry(newBullet->getx(),newBullet->gety(),10,10);
                newBullet->show();
                bulletPressed=true;
            }
            break;
        }
        default:
            break;
        }
        myTank[GREEN]->changeKeyPressed(newgreen);
        myTank[RED]->changeKeyPressed(newred);
    }
    if(tankPressed){
        emit tankKeyPressed();
    }
    if(bulletPressed){
        emit bulletKeyPressed();
    }

}
void Battlefield::keyReleaseEvent(QKeyEvent *event)
{
    //获得之前的按钮情况
    bool* newred=new bool[4];
    bool* newgreen=new bool[4];
    bool* oldred=myTank[RED]->getKeyPressed();
    bool* oldgreen=myTank[GREEN]->getKeyPressed();
    for(int i=0;i<4;i++){
        newred[i]=oldred[i];
        newgreen[i]=oldgreen[i];
    }
    if (event->isAutoRepeat()) {
        event->ignore();
    } else {
        switch(event->key()){
        case Qt::Key_Right:
            newgreen[RIGHT]=false;
            break;
        case Qt::Key_Up:
            newgreen[UP]=false;
            break;
        case Qt::Key_Left:
            newgreen[LEFT]=false;
            break;
        case Qt::Key_Down:
            newgreen[DOWN]=false;
            break;
        case Qt::Key_W:
            newred[UP]=false;
            break;
        case Qt::Key_A:
            newred[LEFT]=false;
            break;
        case Qt::Key_S:
            newred[DOWN]=false;
            break;
        case Qt::Key_D:
            newred[RIGHT]=false;
            break;
        default:
            break;
        }
        myTank[GREEN]->changeKeyPressed(newgreen);
        myTank[RED]->changeKeyPressed(newred);
    }
    //如果所有的按钮都释放了，就发射tankKeyReleased()信号，从而结束计时器
    bool allReleased=true;
    for(int i=0;i<4;i++){
        if(newred[i]){
            allReleased=false;
            break;
        }
        if(newgreen[i]){
            allReleased=false;
            break;
        }
    }
    if(allReleased){
        emit tankKeyReleased();
    }
}

void Battlefield::paintEvent(QPaintEvent*){
    //draw walls filled with darkGray color
    QPainter painter(this);
    painter.setPen(Qt::black);
    QPainterPath mypath;
    QBrush mybrush(Qt::darkGray);
    for(auto polygon:(walls->getWalls())){
        mypath= QPainterPath();
        mypath.addPolygon(polygon);
        painter.fillPath(mypath,mybrush);
        //painter.drawPolygon(polygonf);
    }
}

void Battlefield::tankTimeout(){
    //改变坦克位置,旋转角度,并重新显示坦克
    //if crash after changing postion, go back to the old position
    double oldx,oldy; int oldangle;
    int tmpcolor[2]={GREEN,RED};
    for(auto color:tmpcolor){
        oldx=myTank[color]->getx();
        oldy=myTank[color]->gety();
        oldangle=myTank[color]->getangle();
        myTank[color]->changePosition();
        if(walls->tankCrashOnWall(myTank[color])){
            myTank[color]->changePosition(oldx,oldy,oldangle);
        }
    }
    myTank[GREEN]->setPixmap(
        QPixmap::fromImage(*myTank[GREEN]->getImage()).transformed(QTransform().rotate(myTank[GREEN]->getangle())));
    myTank[RED]->setPixmap(
        QPixmap::fromImage(*myTank[RED]->getImage()).transformed(QTransform().rotate(myTank[RED]->getangle())));
    myTank[GREEN]->setGeometry(myTank[GREEN]->getx(),myTank[GREEN]->gety(),60,60);
    myTank[RED]->setGeometry(myTank[RED]->getx(),myTank[RED]->gety(),60,60);
    //以下代码用于debug,查看坦克矩形的坐标是否显示正确
   // ui->testlabel->setText(myTank[RED]->getRect());
}
void Battlefield::bulletTimeout(){
    //遍历所有子弹，改变其位置，重新显示
    for(auto pair:myBullets){
        auto bullet=pair.first;
        //在这里需要添加一个子弹是否反弹的判断
        bullet->rebound(walls->getWalls());

        bullet->changePosition();

        bullet->setGeometry(bullet->getx(),bullet->gety(),10,10);
    }
}
void Battlefield::delBullet(){
    //删掉第一个子弹和他对应的计时器
    auto pair=myBullets.front();
    myTank[pair.first->getcolor()]->changeNumOfBullets(1);
    delete pair.first;
    delete pair.second;
    myBullets.pop_front();
    //如果所有子弹都被删除了，释放信号
    if(myBullets.empty()){
        emit allBulletDestroyed();
    }
}
void Battlefield::gameCheck(){
    //检查游戏情况
    int gameCondition=checkGame();
    if(gameCondition!=ONGOING){
        timerForChecking->stop();
        timerForChecking->disconnect();
        timerForBullet->stop();
        timerForBullet->disconnect();
        timerForTank->stop();
        timerForTank->disconnect();
        QImage explosion("C:/Tank_War-yxy (1)/Tank_War-yxy/Tank_War_0/images/explosion.png");
        QImage greenwin("C:/Tank_War-yxy (1)/Tank_War-yxy/Tank_War_0/images/greenwin.png");
        QImage redwin("C:/Tank_War-yxy (1)/Tank_War-yxy/Tank_War_0/images/redwin.png");
        if(gameCondition==TIE){
            myTank[RED]->setPixmap(QPixmap::fromImage(explosion));
            myTank[GREEN]->setPixmap(QPixmap::fromImage(explosion));
            myTank[GREEN]->setGeometry(myTank[GREEN]->getx(),myTank[GREEN]->gety(),60,60);
            myTank[RED]->setGeometry(myTank[RED]->getx(),myTank[RED]->gety(),60,60);
        }else if(gameCondition==GREENWIN){
            myTank[RED]->setPixmap(QPixmap::fromImage(explosion));
            myTank[RED]->setGeometry(myTank[RED]->getx(),myTank[RED]->gety(),60,60);
        }else if(gameCondition==REDWIN){
            myTank[GREEN]->setPixmap(QPixmap::fromImage(explosion));
            myTank[GREEN]->setGeometry(myTank[GREEN]->getx(),myTank[GREEN]->gety(),60,60);
        }
    }
}

void Battlefield::mousePressEvent(QMouseEvent *event){
//    ui->mouse->setText("("+QString::number(event->x())+","+QString::number(event->y())+")"
//                       +"leftup:("+QString::number(myTank[RED]->getx())+","+QString::number(myTank[RED]->gety())+")");
}

Battlefield::~Battlefield()
{
    delete ui;
    delete myTank[0];
    delete myTank[1];
    delete timerForTank;
    delete timerForBullet;
    delete walls;
    myBullets.clear();
}
void gameStart(){

}
int Battlefield::checkGame(){
    if(CTank::tankCrashed(myTank[GREEN],myTank[RED])){
        return TIE;
    }
    QPolygon greentank,redtank;
    QPoint* p1=myTank[GREEN]->getPoints();
    QPoint* p2=myTank[RED]->getPoints();
    for(int i=0;i<4;i++){
        greentank<<p1[i];
        redtank<<p2[i];
    }
    for(auto it:myBullets){
        CBullet* bullet=it.first;
        int bx=bullet->getx(),by=bullet->gety();
        QPolygon bulletPo;
        bulletPo<<QPoint(bx,by)<<QPoint(bx,by+10)<<QPoint(bx+10,by+10)<<QPoint(bx+10,by);
        if(bulletPo.intersects(greentank)&&bulletPo.intersects(redtank)){
            return TIE;
        }
        if(bulletPo.intersects(greentank)){
            return REDWIN;
        }
        if(bulletPo.intersects(redtank)){
            return GREENWIN;
        }
    }
    return ONGOING;
}

