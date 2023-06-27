#ifndef QSTOPWINDOW_H
#define QSTOPWINDOW_H

#include <QMainWindow>

namespace Ui {
class QStopWindow;
}
//按下暂停按钮后出现的界面
class QStopWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit QStopWindow(QWidget *parent = nullptr);
    ~QStopWindow();

private:
    Ui::QStopWindow *ui;
};

#endif // QSTOPWINDOW_H
