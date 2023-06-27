#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"qgamewindow.h"
#include<QLabel>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(600,600);
    ui->normalMode->resize(100,60);
    ui->itemMode->resize(100,60);
    ui->normalMode->move(250,300);
    ui->itemMode->move(250,400);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_normalMode_clicked()
{
    gamewindow=new QGameWindow(this,QGameWindow::NORMALMODE);
    this->close();
    gamewindow->gameStart();
}

void MainWindow::on_itemMode_clicked()
{
    gamewindow=new QGameWindow(this,QGameWindow::ITEMMODE);
    this->close();
    gamewindow->gameStart();
}
