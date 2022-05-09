#include "controllabel.h"

ControlLabel::ControlLabel(QWidget *parent) : QLabel(parent)
{
    this->setMouseTracking(true);
}

void ControlLabel::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton || event->button() == Qt::MiddleButton || event->button() == Qt::RightButton)
    {
        mouse_clicked(event->button(), true);
    }

}
void ControlLabel::mouseReleaseEvent(QMouseEvent* event)
{
    mouse_clicked(event->button(), false);
}
void ControlLabel::mouseMoveEvent(QMouseEvent *event)
{
    int xoffset = (this->contentsRect().width()- this->pixmap()->rect().width())/2;
        int yoffset  = (this->contentsRect().height()- this->pixmap()->rect().height())/2;
        QPoint pos = event->globalPos();
        pos = this->mapFromGlobal(pos);
        int x,y;
        x= pos.x() -xoffset;
        y = pos.y() -yoffset;

        mouse_move(double(x) /this->pixmap()->rect().width(), double(y) /this->pixmap()->rect().height());
}
void ControlLabel::wheelEvent(QWheelEvent *event)
{
    wheel(event->delta());
}
void ControlLabel::keyReleaseEvent(QKeyEvent *event)
{
    key_clicked(event->key(), false);
}
void ControlLabel::keyPressEvent(QKeyEvent *event)
{
    key_clicked(event->key(), true);
}
