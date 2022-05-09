#ifndef CONTROLLABEL_H
#define CONTROLLABEL_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>

class ControlLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ControlLabel(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);			//滚轮事件
    void keyReleaseEvent(QKeyEvent *event); //键盘松开事件
    void keyPressEvent(QKeyEvent *event); //键盘按下事件
signals:
    void mouse_clicked(int, bool);
signals:
    void mouse_move(double x, double y);
signals:
    void wheel(int);
signals:
    void key_clicked(int, bool);
};

#endif // CONTROLLABEL_H
