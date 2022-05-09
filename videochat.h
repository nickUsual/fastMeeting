#ifndef VIDEOCHAT_H
#define VIDEOCHAT_H

#include <QWidget>
#include "videowidget.h"
#include "sharewidget.h"
#include <QMessageBox>
#include "recvcontrolwidget.h"
#include "controlwidget.h"
namespace Ui {
class VideoChat;
}

class VideoChat : public QWidget
{
    Q_OBJECT

public:
    explicit VideoChat(QWidget *parent = nullptr,QString myname =nullptr);
    ~VideoChat();
    void frashCameraBtn();
    void frashRedioBtn();
    void frashMicroBtn();
    void frashVideo();

private slots:
    void on_microButton_clicked();

    void on_videoButton_clicked();

    void on_redioButton_clicked();

    void on_screenShareButton_clicked();

    void on_manListButton_clicked();

    void on_chatButton_clicked();

    void on_settingButton_clicked();

    void on_overButton_clicked();

    void on_remoteButton_clicked();

    //设置窗口变化时需要对窗口控件进行调整
    virtual void resizeEvent(QResizeEvent *event);

    void on_previouPageBtn_clicked();

    void on_nextPageBtn_clicked();



private:
    Ui::VideoChat *ui;
    //设置有限状态机
    //摄像头是否打开
    bool camera;
    //麦克风状态信号
    bool mic;
    //系统声音信号
    bool sys_voice;
    //有人在共享屏幕的信号,为true代表正在分型屏幕
    bool issharing;
   //当前自己在分享屏幕
    bool myIsSharing;
    //当前的宽度
    int currentW;
    //当前的高度
    int currentH;
    QString myname;

    //设置接受远控的信号函数
    RecvControlWidget *recvControlWidget;
    //设置控制窗口
    ControlWidget *conWidget;
     VideoWidget * videoWidget1;
     QList<QLabel*> labelList;
     int page = 0;
     ShareWidget *shareWidget;
     int conlum = 3;
     int row = 2;
     int geshu= conlum * row;

};

#endif // VIDEOCHAT_H
