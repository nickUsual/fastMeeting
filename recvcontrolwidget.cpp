#include "recvcontrolwidget.h"
#include "ui_recvcontrolwidget.h"
RecvControlWidget::RecvControlWidget(QWidget *parent,UserId id) :
    QWidget(parent),
    ui(new Ui::RecvControlWidget)
{
    ui->setupUi(this);
    ui->labelphoto->setPixmap(QPixmap::fromImage(QImage(":/imge/myIcon/warn_orange.png")).scaled(ui->labelphoto->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    setWindowTitle("请求连接");
    ui->label_text->setText(kern->get_name(id)+"想要控制你的设备,请选择接受或者拒绝该请求");
    otherId = id;
}

RecvControlWidget::~RecvControlWidget()
{
    delete ui;
}

void RecvControlWidget::on_agreeControl_clicked()

{

    QMessageBox::information(this, tr("消息"),"你正在请求"+kern->get_name(otherId)+"控制你的的电脑，请等待对方的回应...", QMessageBox::Yes);
    kern->accept_control(otherId ,true);
    kern->start_show_pri(true);
    this->close();


}

void RecvControlWidget::on_disagreeControl_clicked()
{
    kern->accept_control(otherId ,false);
    this->close();
}
