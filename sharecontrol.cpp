#include "sharecontrol.h"
#include "ui_sharecontrol.h"
#include <QPushButton>
#include <QFrame>
#include <QLineEdit>
#include <QMessageBox>
#include <QLabel>
ShareControl::ShareControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShareControl)
{
    ui->setupUi(this);
    QStringList nameList;
    useridList =kern->get_user();
    for(auto i:useridList)
    {
        nameList<<kern->get_name(i);
    }
    QMap<QString, QList<QPushButton *>> *Buttonlist = new  QMap<QString, QList<QPushButton*>>();

    int j = 0;
    for(int i =0;i < nameList.length();i++){
        QPushButton *controlButton = new QPushButton("请求远控对方");
        //设置button的样式表
        controlButton->setStyleSheet("background-color: rgb(0, 170, 255);font: 9pt \"小米兰亭\";color: white;");

        temp = useridList[i];
        connect(controlButton,&QPushButton::clicked,[=](){
             this->hide();
            temp = kern->get_user()[i];
            kern->ask_control(temp);
            QMessageBox::information(this,tr("消息"),"你正在请求控制"+kern->get_name(temp)+"的电脑，正待对方的同意",QMessageBox::Yes);
            this->close();
        });
        QPushButton *controledButton = new QPushButton("请求对方远控");
        connect(controledButton,&QPushButton::clicked,[=](){
            this->hide();
            temp = kern->get_user()[i];
            kern->ask_controlled(temp);
            QMessageBox::information(this,tr("消息"),"你正在请求"+kern->get_name(temp)+"控制你的的电脑，正在等待对方的响应",QMessageBox::Yes);
            this->close();
        });
        QList<QPushButton *> *tempButtonList = new  QList<QPushButton*>();

        tempButtonList->append(controlButton);
        tempButtonList->append(controledButton);
        Buttonlist->insert(nameList[j],*tempButtonList);
        QFrame *tempFrame = new QFrame();
        QLabel *edit=new QLabel(tempFrame);
        edit->setText(nameList[j]);
        ui->gridLayout->addWidget(tempFrame,j,0);
        ui->gridLayout->addWidget(controlButton,j,1);
        ui->gridLayout->addWidget(controledButton,j++,2);
    }


}

ShareControl::~ShareControl()
{
    delete ui;
}
