#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QLabel>
#include"qgamewindow.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
//MainWindow是一打开之后的窗口
//在里面选择游戏模式
//选择后跳转至qgamewindow
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_normalMode_clicked();//进入普通模式
    void on_itemMode_clicked();//进入道具模式


private:
    Ui::MainWindow *ui;
    QGameWindow * gamewindow;


};
#endif // MAINWINDOW_H
