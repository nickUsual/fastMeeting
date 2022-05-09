#include "normal.h"
QPixmap namePicture(QString name)
{
    QPixmap image(280, 232);//QImage::Format_ARGB32背景是透明
    QPainter p(&image);
    p.fillRect(0,0,280,232, QBrush(Qt::black));

     //p.setRenderHint(QPainter::Antialiasing, true);
      p.setBrush(QBrush(Qt::blue, Qt::SolidPattern));

    p.drawEllipse(QPoint(140,116),70,70);
    QPen pen;
     pen.setColor( Qt::black );
     p.setPen(pen);
      //p.;
     p.setFont(QFont("宋体",60,14));
    p.drawText(QPoint(105,135),name);
    return image;
}
