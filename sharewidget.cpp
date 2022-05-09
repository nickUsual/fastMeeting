#include "sharewidget.h"
#include "ui_sharewidget.h"
#include <qdebug.h>
ShareWidget::ShareWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShareWidget)
{
    ui->setupUi(this);
    int currentW = this -> size().width(); // 用以记录当前窗体宽度
    int currentH = this -> size().height(); // 用以记录当前窗体高度

    shareLabel = new QLabel();
    //设置qlabel的位置坐标
    shareLabel->setGeometry(0,0,currentW,currentH);
    ui->verticalLayout->addWidget(shareLabel);
}


ShareWidget::~ShareWidget()
{
    delete ui;
}

void ShareWidget::resizeEvent(QResizeEvent *size){
    qDebug()<<"调用了";
    currentW = this -> size().width(); // 用以记录当前窗体宽度
    currentH = this -> size().height(); // 用以记录当前窗体高度
    qDebug() << currentH;
    shareLabel->setGeometry(0,0,currentW,currentH);
//    shareLabel->resize(*size);
}
QLabel *ShareWidget::getLabel()
{
    return shareLabel;
}
