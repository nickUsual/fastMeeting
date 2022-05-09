#ifndef CONTROLWIDGET_H
#define CONTROLWIDGET_H

#include <QWidget>
#include "ExternVariable.h"
#include <QLabel>
#include <controllabel.h>
namespace Ui {
class ControlWidget;
}

class ControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ControlWidget(QWidget *parent = nullptr,UserId id = 0);
    virtual void resizeEvent(QResizeEvent *event);
    void keyReleaseEvent(QKeyEvent *event); //键盘松开事件
    void keyPressEvent(QKeyEvent *event); //键盘按下事件
    ~ControlWidget();

private slots:
    void on_exitControlBtn_clicked();

private:
    UserId otherId;
    int lengthW;
    int lengthH;
    Ui::ControlWidget *ui;
};

#endif // CONTROLWIDGET_H
