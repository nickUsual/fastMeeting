#include "settingwidget.h"
#include "ui_settingwidget.h"
#include <QDebug>
#include <qtabbar.h>
SettingWidget::SettingWidget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SettingWidget)
{
    ui->setupUi(this);
    //创建初始的系统窗口

    /*或者下面的代码*/

    sysetting = new SysSetting();
    redioSetting = new RedioSetting();
    meetingInformation = new MeetingInfor();
    aboutUs = new AboutUs();
    ui->tabWidget->addTab(sysetting, "系统设置");
    ui->tabWidget->addTab(redioSetting, "音频设置");
    ui->tabWidget->addTab(meetingInformation, "会议信息");
    ui->tabWidget->addTab(aboutUs, "关于我们");
    //ui->tableWidget->addTab();
    sysetting->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    //ui->tabWidget->tabBar()->setMaximumWidth(ui->tabWidget->width());


//    ui->gridLayout->addWidget(sysetting);
//    //将有限状态自动机的状态置为系统设置阶段,表示当前状态为系统设置阶段
//    state  = SYSTEM_SET;

    connect(sysetting,&SysSetting::sysClose,[=](){
        //sysetting->close();
        qDebug() << "sysClose运行了";
        this->close();
    });
    //连接redioSetting窗口的关闭和当前窗口的关闭联动
    connect(redioSetting,&RedioSetting::redioSettingClose,[=](){
            redioSetting->close();
            qDebug() << "Close运行了";
           this->close();
    });

    //连接meetingInfor窗口和当前窗口的信息
    connect(meetingInformation,&MeetingInfor::meetinginforClose,[=](){
            meetingInformation->close();
            qDebug() << "Close运行了";
            this->close();
     });
    //连接aboutus窗口的关闭和当前窗口的关闭联动
    connect(aboutUs,&AboutUs::aboutUsClose,[=](){
        aboutUs->close();
        qDebug() << "Close运行了";
       this->close();
    });
    //连接redioSetting的关闭和当前窗口的关闭联动
    connect(redioSetting,&RedioSetting::redioSettingClose,[=](){
        redioSetting->close();
        qDebug() << "Close运行了";
       this->close();
    });



}

SettingWidget::~SettingWidget()
{
    delete ui;
}

//void SettingWidget::on_sysSetBtn_clicked()
//{
////    //将状态切换为系统设置阶段
////   state  = SYSTEM_SET;
////   QLayoutItem *child;
////   while ((child = ui->gridLayout->takeAt(0)) != 0) {
////       if(child->widget())
////           delete child->widget();
////       delete child;
////   }
////   //设置当前的窗口为系统设置窗口的父窗口
////   sysetting = new SysSetting();
////   connect(sysetting,&SysSetting::sysClose,[=](){
////       //sysetting->close();
////       qDebug() << "sysClose运行了";
////       this->close();
////   });
////   sysetting->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
////   ui->gridLayout->addWidget(sysetting);
//}

//void SettingWidget::on_redioSetBtn_clicked()
//{
////    //将状态切换为声音设置阶段
////    state  = REDIO_SET;
////    QLayoutItem *child;
////    while ((child = ui->gridLayout->takeAt(0)) != 0) {
////        if(child->widget())
////            delete child->widget();
////        delete child;
////    }
////    redioSetting = new RedioSetting();
////    connect(redioSetting,&RedioSetting::redioSettingClose,[=](){
////        redioSetting->close();
////        qDebug() << "Close运行了";
////       this->close();
////    });

////    redioSetting->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
////    ui->gridLayout->addWidget(redioSetting);
//}

//void SettingWidget::on_MeetMessageSetBtn_clicked()
//{
////    //将状态切换为会议信息窗口阶段
////    state  = MEETING_INFOR;
////    QLayoutItem *child;
////    while ((child = ui->gridLayout->takeAt(0)) != 0) {
////        if(child->widget())
////            delete child->widget();
////        delete child;
////    }
////    meetingInformation = new MeetingInfor();

////    connect(meetingInformation,&MeetingInfor::meetinginforClose,[=](){
////        meetingInformation->close();
////        qDebug() << "Close运行了";
////        this->close();
////    });
////    meetingInformation->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
////    ui->gridLayout->addWidget(meetingInformation);
//}

//void SettingWidget::on_aboutUsBtn_clicked()
//{
//    //将状态切换为关于我们窗口
//    state  = ABOUT_US;
//    QLayoutItem *child;
//    while ((child = ui->gridLayout->takeAt(0)) != 0) {
//        if(child->widget())
//            delete child->widget();
//        delete child;
//    }
//    aboutUs = new AboutUs();

//    connect(aboutUs,&AboutUs::aboutUsClose,[=](){
//        aboutUs->close();
//        qDebug() << "Close运行了";
//       this->close();
//    });
//    aboutUs->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
//    ui->gridLayout->addWidget(aboutUs);
//}



