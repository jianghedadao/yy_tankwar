#include "cwall.h"

CWall::CWall(QWidget *parent)
    : QLabel{parent}
{
    int x=parent->width();
    int y=parent->height();
    //先添加边框
    walls.push_back(QPolygon(QRect(QPoint(0,0),QPoint(x,10))));
    walls.push_back(QPolygon(QRect(QPoint(0,0),QPoint(10,y))));
    walls.push_back(QPolygon(QRect(QPoint(x-10,0),QPoint(x,y))));
    walls.push_back(QPolygon(QRect(QPoint(0,y-10),QPoint(x,y))));
    //再随机生成墙壁
    std::memset(used,0,sizeof(used));
    const int L=100;
    for(int i=1;i<12;++i)
    {
        for(int j=1;j<6;++j){
            if(used[i][j]) continue;
            used[i][j]=1;
            int numOfLine=0;
            for(int k=0;k<4;++k){
                bool R=rand()%2;
                if(R){
                    int ii=i+direction[k][0],jj=j+direction[k][1];
                    used[ii][jj]=1;
                    ++numOfLine;
                    int adi=std::max(-direction[k][0],0);
                    int adii=std::max(direction[k][0],0);
                    int adj=std::max(-direction[k][1],0);
                    int adjj=std::max(direction[k][1],0);
                    walls.push_back(QPolygon(QRect(QPoint(i*L+adi*10,j*L+adj*10),
                            QPoint(ii*L+std::abs(direction[k][1]*10)+adii*10,
                                                          jj*L+std::abs(direction[k][0]*10)+adjj*10))));
                }
            }
        }
    }

}
CWall::~CWall(){
    walls.clear();
}

void CWall::removerW(QPoint start,QPoint end){
    for(int x=start.x();x<=end.x();x+=1){
        int y=start.y();
        QPoint myTest(x,y);
        int count = walls.size();
        for (int i = 0; i < count;i++)
        {
            if(walls[i].containsPoint(myTest,Qt::WindingFill)){
                walls.erase(walls.begin()+i);
                count = walls.size();
                --i;
            }
        }
    }
    for(int x=start.x();x>=end.x();x-=1){
        int y=start.y();
        QPoint myTest(x,y);
        int count = walls.size();
        for (int i = 0; i < count;i++)
        {
            if(walls[i].containsPoint(myTest,Qt::WindingFill)){
                walls.erase(walls.begin()+i);
                count = walls.size();
                --i;
            }
        }
    }
    for(int y=start.y();y<=end.y();y+=1){
        int x=end.x();
        QPoint myTest(x,y);
        int count = walls.size();
        for (int i = 0; i < count;i++)
        {
            if(walls[i].containsPoint(myTest,Qt::WindingFill)){
                walls.erase(walls.begin()+i);
                count = walls.size();
                --i;
            }
        }
    }
    for(int y=start.y();y>=end.y();y-=1){
        int x=end.x();
        QPoint myTest(x,y);
        int count = walls.size();
        for (int i = 0; i < count;i++)
        {
            if(walls[i].containsPoint(myTest,Qt::WindingFill)){
                walls.erase(walls.begin()+i);
                count = walls.size();
                --i;
            }
        }
    }

}

const std::vector<QPolygon>& CWall::getWalls(){
    return walls;
}

bool CWall::tankCrashOnWall(CTank* tank){
    //传入坦克 判断坦克是否撞墙
    QPolygon tankPolygon;
    QPoint* points=tank->getPoints();
    for(int i=0;i<4;i++){
        tankPolygon<<points[i];
    }
    for(auto it:walls){
        if(it.intersects(tankPolygon)){
            return true;
        }
    }
    return false;
}
