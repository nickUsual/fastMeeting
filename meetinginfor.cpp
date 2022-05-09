#include "meetinginfor.h"
#include "ui_meetinginfor.h"
#include "ExternVariable.h"
MeetingInfor::MeetingInfor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MeetingInfor)
{
    ui->setupUi(this);
    ui->textBrowser->setText("999");
    ui->textBrowser_3->setText(QString(kern->get_user().count()));
}

MeetingInfor::~MeetingInfor()
{
    delete ui;
}

void MeetingInfor::on_pushButton_clicked()
{
    this->hide();
    emit meetinginforClose();
}
