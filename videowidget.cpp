#include "videowidget.h"
#include "ui_videowidget.h"

VideoWidget::VideoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoWidget)
{
    ui->setupUi(this);
    lable = new QLabel();
    ui->gridLayout->addWidget(lable);
    lable->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
}

VideoWidget::~VideoWidget()
{
    delete ui;
}

QLabel *VideoWidget::getlable()
{
    return lable;
}
