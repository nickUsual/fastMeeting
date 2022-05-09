#ifndef NETMANAGE_H
#define NETMANAGE_H
#include <QByteArray>
#include <QMap>
#include "netcliet.h"
#include "form.h"



class netmanage :public QObject
{
	Q_OBJECT
public:
	struct userdata
	{
		QByteArray name;
		bool camera;
		bool mic;
		bool screen;
	};
private:
	netcliet client;                   //这里不需要一个socket吗？
	QMap<UserId, struct userdata>list;      //这个map要怎么用，慢慢理解
	QByteArray name_rem, pass_rem;
	QByteArray ip;
	int port;
private:
	void send(mationType, QByteArray);
	void getlist() { send(mationType::userlist, 0); }
public:
	netmanage();
	void login(QByteArray, QByteArray);
	void send_msg(UserId, MsgType, QByteArray);
	void send_server(mationType, QByteArray);//给服务器发信息
	void recv_msg(QByteArray msg);//这个函数是用来接收消息的，是在接收到的消息里面知道，发送消息的用户的id，
	void dislink();
	QByteArray get_name(UserId);
	bool get_camera(UserId);
	bool get_mic(UserId);
	bool get_screen(UserId);
	QList<UserId> get_user();
signals:
	void result_link(LOGIN_RESULT);
signals:
	void signal_dislink();
signals:
	void signal_recvmsg(UserId, MsgType, QByteArray);
signals:
	//这个要改成枚举类型UserId
	void client_change(UserId, ClientChange);
signals:
	void failed_send();
signals:
    void get_userlist();

};

#endif // NETMANAGE_H
