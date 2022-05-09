#ifndef NETCLIET_H
#define NETCLIET_H
#include <QObject>
#include <QTcpSocket>
#include "form.h"

class netcliet:public QObject
{
    Q_OBJECT
private:
    QTcpSocket *socket;
    QByteArray IP_rem;
    int port_rem;
public:
    netcliet();
    void login_ip(QByteArray, int);
    void login_domain(QByteArray, int);
    void send_msg(QByteArray);
    void dislink();
    void signalsend_dislink_send();//用来发送信号的函数，也就是实现信号的函数
    void signalsend_recv_msg_send();//用来发送信号的函数，也就是实现信号的函数
signals:
    void signal_dislink();//这个信号怎么实现//信号只要发送。//就像调用函数
signals:
    void recv_msg(QByteArray);
signals:
    void get_link();
signals:
    void result_link(RESULT);   //连接之后发送这个信号，这个信号有一个参数，成功或失败。
};

#endif // NETCLIET_H
