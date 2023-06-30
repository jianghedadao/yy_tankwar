#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QImage>
#include <QPixmap>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->startButton,&QPushButton::clicked,[=](){
        mybattlefield=new Battlefield(this);
        mybattlefield->setWindowFlags(Qt::Window);
        mybattlefield->show();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mybattlefield;
}





