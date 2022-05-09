#include "chattingwidget.h"
#include "ui_chattingwidget.h"

ChattingWidget::ChattingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChattingWidget)
{
    ui->setupUi(this);
}

ChattingWidget::~ChattingWidget()
{
    delete ui;
}
