#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QMainWindow>
#include "syssetting.h"
#include "rediosetting.h"
#include "meetinginfor.h"
#include "aboutus.h"
#include "ken/form.h"
#include "rediosetting.h"
namespace Ui {
class SettingWidget;
}

class SettingWidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit SettingWidget(QWidget *parent = nullptr);
    ~SettingWidget();
    void systemSet();
    void redioSet();
    void meetingInfor();
    void aboutUsSet();

//private slots:
//    void on_sysSetBtn_clicked();

//    void on_redioSetBtn_clicked();

//    void on_MeetMessageSetBtn_clicked();

//    void on_aboutUsBtn_clicked();





private:
    QWidget *mywidget;
    SysSetting *sysetting;
    RedioSetting *redioSetting;
    MeetingInfor * meetingInformation;
    AboutUs * aboutUs;
    Ui::SettingWidget *ui;
    RedioSetting *redio_widget;
    //存储状态切换的有限状态自动机
    SettingState state;

    //存储系统设置的信号参数
    //入会开启摄像头设置
    bool camera_set;
    //入会开启麦克风设置
    bool micro_set;
    //入会使用电脑音频
    bool redio_set;

    //音频系统设置的信号参数


};

#endif // SETTINGWIDGET_H
