#include "netmanage.h"
#include "qsettings.h"
#include "QCoreApplication"
#include "QHostInfo"
//这个测试完，可以连接和发送消息。
//这个test8工程里面的客户端和服务器都实现了连接，发送消息，接收消息的功能而且都经过了测试
//现在是要来完成qbytearray和大部分的函数。
netmanage::netmanage()
{

    QObject::connect(&client,&netcliet::signal_dislink,this,&netmanage::dislink);//需要这个线程来监听，
    QObject::connect(&client, &netcliet::recv_msg, this, &netmanage::recv_msg);
    QObject::connect(&client, &netcliet::get_link, this, [=]() {
        QByteArray data;
        int namelen = name_rem.count();
        data.resize(sizeof(namelen));
        memcpy(data.data(), &namelen, sizeof(namelen));
        send(mationType::link, data + name_rem + pass_rem);
        });
    
    qDebug("调用构造函数新建了一个socket\n\n\n");
}


//客户端不需要转发，服务器才需要转发
 void netmanage::send(mationType type, QByteArray msg)// // // //////////////////////////////////
 {
     QByteArray data;

     data.resize(sizeof(type));
     memcpy(data.data(), &type, sizeof(type));
     client.send_msg(data + msg);
 }

//感觉这里的连接也需要socket，也需要ip和端口号
void netmanage::login(QByteArray name, QByteArray password)
{
    //获取ip和post
    name_rem = name;
    pass_rem = password;
    qDebug("调用了login函数");
    QSettings set(/*QCoreApplication::applicationDirPath()+*/":/Config.ini", QSettings::IniFormat);
    qDebug() << QCoreApplication::applicationDirPath()+"/Config.ini";
    if (set.value("ip/enable").toBool())
    {
        ip = set.value("ip/ip").toString().toLatin1();
        port = set.value("ip/port").toInt();
        client.login_ip(ip, port);
    }
    else if (set.value("host/enable").toBool())
    {
        QByteArray host;
        host = set.value("host/host").toByteArray();
        port = set.value("ip/port").toInt();
        client.login_domain(host, port);
    }
    else
    {
        ip = "0:0:0:0:0:0:0:1";
        port = 8000;
        client.login_ip(ip, port);
    }
}




//发送消息接收。分配编号。连接（连接成功失败的原因，密码错误还是什么，然后就是分配编号（分配编号用一个单独的函数来做，无脑加一））。连接数据库。
//发送消息和接收消息，这两个函数要写好。要先测试这两个函数
//其实测试这个函数对不对很简单的，实在不行，把这个函数写道netclient文件里面去，用那个对象来调用这个函数，看看能不能发送消息。
//改成qbytearray

//对外的接口
void netmanage::send_msg(UserId ID, MsgType type,QByteArray msg)
{
    QByteArray data;
    data.resize(sizeof(ID) + sizeof(MsgType));
    memcpy(data.data(), &ID, sizeof(ID));
    memcpy(data.data() + sizeof(ID), &type, sizeof(type));
    send(mationType::send, data + msg);
    //memccpy(&ID, data.data(), sizeof(ID));
    //msg = data.right(data.count() - sizeof(ID) - sizeof(type));
}

void netmanage::send_server(mationType type, QByteArray data)
{
    send(type, data);
}



//感觉这里的接收消息，还是要多做一些事情，因为像连接结果，客户端变动这些消息，都是服务器向客户端发送的
//这个时候，发送过来的消息，肯定都是特定的消息类型，所以这种消息的发送方是服务器，
//发现一个问题，那就是，我要向一个用户发送消息，那么我肯定是要把用户id弄成目标id，那么接收方的客户端
//他那边现实的应该是谁发来的，那么也就是说，服务器，在转发的时候，需要把这条消息的id改一下。
void netmanage::recv_msg(QByteArray msg)
{  

    mationType type;
    memcpy(&type, msg.data(), sizeof(type));
    msg = msg.right(msg.count() - sizeof(type));

    UserId id;
    QByteArray name;
    MsgType msgtype;
    QByteArray data;

    LOGIN_RESULT result;
    ClientChange change;

    int len;
    int str_len;
    int count_len = 0;
    bool enable;
    switch (type) {
    case mationType::send:
        memcpy(&id, msg.data(), sizeof(id));
        memcpy(&msgtype, msg.data() + sizeof(id), sizeof(msgtype));
        data = msg.right(msg.count() - sizeof(id) - sizeof(msgtype));
        emit signal_recvmsg(id, msgtype, data);                         //我明白了，这里是收到了别人发的消息，所以不需要再发出去
        break;
    case mationType::link:
        memcpy(&result, msg.data(), sizeof(result));
        
        if(result == LOGIN_RESULT::SUCCESS)
        {
            getlist();
        }
        emit result_link(result);
        break;
    case mationType::client_change:

        memcpy(&id, msg.data(), sizeof(id));
        memcpy(&change, msg.data() + sizeof(id), sizeof(change));
        if(change)
        {
            name = msg.right(msg.count() - sizeof(id) - sizeof(change));
            list[id].name = name;
        }
        else
        {
            list.remove(id);
        }

        emit client_change(id, change);
        break;
    case mationType::userlist:                                  // ///////////////////////很好奇，哪个函数会来发这个类型的消息
        list.clear();
        memcpy(&len, msg.data(), sizeof(len));                  //这里先获取有几个用户
        count_len += sizeof(len);                               //这里count_len记录读取位置
        while(len--)
        {
            memcpy(&id, msg.data() + count_len, sizeof(id));//msg.data(),是一个指针，+count_len就是移动了这个指针
            count_len += sizeof(id);
            memcpy(&str_len, msg.data() + count_len, sizeof(str_len));//
            count_len += sizeof(str_len);
            name = msg.mid(count_len, str_len);                       //获取中间的字符串

            //qstring统计长度不准是什么意思
            count_len += str_len;
            list[id] = *new userdata;
            list[id].name = name;                                          //这里
            memcpy(&enable, msg.data() + count_len, sizeof(enable));
            count_len += sizeof(enable);
            list[id].camera = enable;
            memcpy(&enable, msg.data() + count_len, sizeof(enable));
            count_len += sizeof(enable);
            list[id].mic = enable;
            memcpy(&enable, msg.data() + count_len, sizeof(enable));
            count_len += sizeof(enable);
            list[id].screen = enable;
        }
        emit get_userlist();
        break;
    case mationType::enable_camera:
        memcpy(&id, msg.data(), sizeof(id));
        memcpy(&enable, msg.data() + sizeof(id), sizeof(enable));
        list[id].camera = enable;
        break;
    case mationType::enable_mic:
        memcpy(&id, msg.data(), sizeof(id));
        memcpy(&enable, msg.data() + sizeof(id), sizeof(enable));
        list[id].mic = enable;
        break;
    case mationType::enable_screen:
        memcpy(&id, msg.data(), sizeof(id));
        memcpy(&enable, msg.data() + sizeof(id), sizeof(enable));
        list[id].screen = enable;

        break;
    default:
        break;
    }

}

void netmanage::dislink()
{
    emit signal_dislink();
    //断开连接，需要发送这个信号
}

QByteArray netmanage::get_name(UserId id)
{
    if(!list.contains(id))qDebug()<<"test 111";
    return list[id].name;
}

bool netmanage::get_camera(UserId id)
{
     if(!list.contains(id))qDebug()<<"test 222";
    return list[id].camera;
}
bool netmanage::get_mic(UserId id)
{
     if(!list.contains(id))qDebug()<<"test 333";
    return list[id].mic;
}
bool netmanage::get_screen(UserId id)
{
     if(!list.contains(id))qDebug()<<"test 444";
    return list[id].screen;
}

QList<UserId> netmanage::get_user()
{
    QList<UserId> userlist;
    for(auto each : list.toStdMap()) {
        userlist.append(each.first);
    };
    return userlist;
}
