#include "qstopwindow.h"
#include "ui_qstopwindow.h"

QStopWindow::QStopWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QStopWindow)
{
    ui->setupUi(this);
}

QStopWindow::~QStopWindow()
{
    delete ui;
}
