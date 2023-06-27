#include "qgamewindow.h"
#include "ui_qgamewindow.h"

QGameWindow::QGameWindow(QWidget *parent,int _gamemode) :
    QMainWindow(parent),
    ui(new Ui::QGameWindow),
    gamemode(_gamemode)
{
    ui->setupUi(this);
}

QGameWindow::~QGameWindow()
{
    delete ui;
}

void QGameWindow::gameStart()
{
    this->show();


}
