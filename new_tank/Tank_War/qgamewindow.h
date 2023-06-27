#ifndef QGAMEWINDOW_H
#define QGAMEWINDOW_H

#include <QMainWindow>

namespace Ui {
class QGameWindow;
}
//qgamewindow负责处理游戏事件且显示游戏画面
//其成员应有坦克，子弹等游戏要素的指针
class QGameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit QGameWindow(QWidget *parent = nullptr,int _gamemode=0);
    ~QGameWindow();
    static const int NORMALMODE=0;
    static const int ITEMMODE=1;
private:
    Ui::QGameWindow *ui;
    int gamemode;
public:
    void gameStart();//处理游戏事件的函数
};

#endif // QGAMEWINDOW_H
