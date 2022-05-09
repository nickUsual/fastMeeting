#include "controlwidget.h"
#include "ui_controlwidget.h"

ControlWidget::ControlWidget(QWidget *parent,UserId id) :
    QWidget(parent),
    ui(new Ui::ControlWidget)
{
    ui->setupUi(this);
    otherId = id;
    lengthW = this ->size().width();
    lengthH = this ->size().height();
    //连接
    ui->label->setAlignment(Qt::AlignCenter);
    connect(kern, &Kernel::recv_desktop_pri, this, [=](UserId id, QImage img){

        setWindowTitle(kern->get_name(id)+"当前正在共享屏幕");
        ui->label->setPixmap(QPixmap::fromImage(img).scaled(this->ui->label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        //如果当前没有用户在展示，则证明窗口不存在需要将窗口显示出来
    });
    connect(ui->label, &ControlLabel::mouse_clicked, kern, &Kernel::remote_mouse_cliked);
    //connect(ui->label, &ControlLabel::wheel, kern, &Kernel::remo);
    //connect(ui->label, &ControlLabel::key_clicked, kern, &Kernel::remote_key);
    connect(ui->label, &ControlLabel::mouse_move, kern, &Kernel::remote_mouse_move);
    this->show();
}
void ControlWidget::resizeEvent(QResizeEvent *event){
    QWidget::resizeEvent(event);
    lengthW = this ->size().width();
    lengthH = this ->size().height();
    ui->label->setGeometry(0,0,lengthW,lengthH);
    ui->pushButton->setGeometry(lengthW-120 > 0 ? lengthW-120 : 0,lengthH-40 > 0 ? lengthH-40 :0,90,30);
    ui->exitControlBtn->setGeometry(lengthW-360 > 0 ? lengthW-360 : 0,lengthH-40 > 0 ? lengthH-40 :0,90,30);
}

void ControlWidget::keyReleaseEvent(QKeyEvent *event)
{
    qDebug()<<event->key()<<' '<< false;
    kern->remote_key(event->key(), false);
}
void ControlWidget::keyPressEvent(QKeyEvent *event)
{
    qDebug()<<event->key()<<' '<< true;
    kern->remote_key(event->key(), true);
}

ControlWidget::~ControlWidget()
{
    delete ui;
}

void ControlWidget::on_exitControlBtn_clicked()
{
    kern->disconnect_control();

}
