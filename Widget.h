#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QUdpSocket>
#include <QToolButton>
#include "ExternVariable.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
    enum MsgType {Msg,UsrEnter,UsrLeft};
public:
//    //广播udp消息
//    void sndMsg(MsgType type);
//    //新用户加入
//    void usrEnter(QString username);
//    //处理用户离开
//    void usrLeft(QString usrname,QString time);
//    //获取用户名
//    QString getUsr();
//    //获取聊天信息
//    QString getMsg();
private:
//    QUdpSocket *udpSocket; //udp套接字
//    qint16 port;            //端口
//    QString uName;  //用户名
    void ReceiveMessage(UserId id,QString msg);  //接收UDP的消息
   void ReceiveMessagePrivate(UserId id,QString msg);
public:
    Widget(QWidget *parent,UserId name);
    void fresh();
    void changeId(UserId);
    ~Widget();
    //关闭的事件
//    void closeEvent(QCloseEvent *);

private:
    int selectId;
    Ui::Widget *ui;
     QVector<QToolButton *> buttonList;
signals:
    //关闭窗口发送的信号
    void closeWidget();

};
#endif // WIDGET_H
