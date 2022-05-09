#include "netcliet.h"
//这个是test5工程里面的，目前是初步完成了第一个和第二个，并且改完了bug。就是还没有调试过
#include "QHostInfo"

netcliet::netcliet()
{
	socket = new QTcpSocket();//这里可以不断的新建socket，一个socket就是一个线程。
	QObject::connect(socket, &QTcpSocket::disconnected, this, &netcliet::signalsend_dislink_send);//需要这个线程来监听，
	//如果有disconnected信号,就会调用signalsend_dislink_send函数，来发送那个信号。

	//注意不要写成QObject::connect(socket,&QTcpSocket::disconnected(),this,&netcliet::signal_dislink_send())
	//也就是说，不要带小括号

	QObject::connect(socket, &QTcpSocket::readyRead, this, &netcliet::signalsend_recv_msg_send);
	qDebug() << "1";
}

//这个返回值我不知道是什么意思
void netcliet::login_ip(QByteArray IP, int port)
{
	IP_rem = IP;
	port_rem = port;
	qDebug() << IP;
	socket->connectToHost(IP, port);//这个函数是用来连接服务器的
	//qDebug()<<"2";
	if (!socket->waitForConnected(30000))//这个是这么用的
	{
		emit result_link(RESULT::FAIL); //发送失败的信号
		//qDebug() << "Connection failed!";
	}
	else
	{

		emit get_link();
	}
	//emit result_link(RESULT::SUCCESS);  //这里不可以·发送这个信号，应该先判断密码对不对
	//qDebug() << "login";
}

void netcliet::login_domain(QByteArray host, int port)
{
	port_rem = port;
	QHostInfo::lookupHost(host, this, [=](QHostInfo host_info) {
		if (host_info.addresses().size() > 0)
		{
			IP_rem = host_info.addresses()[0].toString().toLatin1();
		}
		else
		{
			IP_rem = "0:0:0:0:0:0:0:1";
		}
		login_ip(IP_rem, port_rem);
		});
}

void netcliet::send_msg(QByteArray msg)
{
	QByteArray data;
	int len = msg.count();
	data.resize(sizeof(len));
	memcpy(data.data(), &len, sizeof(len));
	socket->write(data + msg);//这个write函数的参数可以是一个指针？
	socket->flush();
}

void netcliet::dislink()
{
	socket->disconnectFromHost();
}

//这里的信号怎么实现，
//实现信号就是发信号，那么发信号就需要一个函数啊，那么这个函数需要在类里面写一下吗，那也就是说，每一个信号，需要一个函数
void netcliet::signalsend_dislink_send()
{
	emit signal_dislink();
}

//这个参数的问题，可以传递参数进来吗
void netcliet::signalsend_recv_msg_send()//这个函数是这么写的吗？需要写明参数吗？//需要把这个函数作为公有成员吗？
{
	static QByteArray msg;           //这里有一个问题，那就是，这里读取的数据是QByteArray类型的，但是recv_msg()信号的参数确是char*类型的
	//读取缓冲区数据
	msg += socket->readAll();
	int len;
	memcpy(&len, msg.data(), sizeof(len));
	while (msg.count() >= len + sizeof(len))
	{
		emit recv_msg(msg.mid(sizeof(len), len));
        msg += socket->readAll();
		msg = msg.right(msg.count() - sizeof(len) - len);
		memcpy(&len, msg.data(), sizeof(len));
	}

}
