#include "Widget.h"
#include "ui_widget.h"
#include <QDataStream>
#include <QMessageBox>
#include <QDateTime>

Widget::Widget(QWidget *parent,UserId name)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //选择的发送对象


    for(auto i: kern->get_user())
    {
        ui->comboBox->addItem(kern->get_name(i));
    }

    connect(ui->sendBtn,&QPushButton::clicked,[=](){
        if(ui->comboBox->currentIndex() != 0)
        selectId = kern->get_user()[ui->comboBox->currentIndex()-1];
        else selectId = 0;
        if(ui->msgEdit->toPlainText() == "") {
                   QMessageBox::warning(this,"警告","发送内容不能为空");
                   return;
        }
            QString msg = ui->msgEdit->toPlainText();
           kern->send_msg(selectId,msg);
           QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
           ui->msgBrowser->setTextColor(Qt::red);
           ui->msgBrowser->append("[me]" + time);
           ui->msgBrowser->append(msg);
        ui->msgEdit->clear();

    });

    connect(kern,&Kernel::recv_msg,this, &Widget::ReceiveMessagePrivate);
    connect(kern,&Kernel::recv_msg_all,this, &Widget::ReceiveMessage);
    connect(kern, &Kernel::user_change, this, [=](){

        for(auto i: kern->get_user())
        {
            ui->comboBox->addItem(kern->get_name(i));
        }
    });

}

void Widget::ReceiveMessagePrivate(UserId id,QString msg){

        //获取当前的时间
        QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        ui->msgBrowser->setTextColor(Qt::blue);
        ui->msgBrowser->append("[" + kern->get_name(id) + "  私 聊]" + time);
        ui->msgBrowser->append(msg);
}

void Widget::ReceiveMessage(UserId id,QString msg){

        //获取当前的时间
        QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        ui->msgBrowser->setTextColor(Qt::blue);
        ui->msgBrowser->append("[" + kern->get_name(id) + "  全 体]" + time);
        ui->msgBrowser->append(msg);
}




void Widget::fresh()
{
    for(auto i: kern->get_user())
    {
        ui->comboBox->addItem(kern->get_name(i));
    }
}





//    udpSocket = new QUdpSocket(this);
//    //用户名的获取,这里可以通过数据库的方法得到用户名和ip和name,
//    uName = name;
//    //端口号
//    this->port = 9999;
//    //绑定端口号
//    //采用ShareAddress模式，即允许其他的服务连接到相同的地址和端口，特别是在多个客户端监听同一哥服务端口时特别有效
//    //ReuseAddressHint模式，断线的话重新连接服务器
//    udpSocket->bind(port,QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
//    //发送新用户进入
////    sndMsg(UsrEnter);
//    connect(ui->sendBtn,&QPushButton::clicked,[=](){
//        sndMsg(Msg);
//    });
//    //监听别人发送的数据
//    connect(udpSocket,&QUdpSocket::readyRead,this,&Widget::ReceiveMessage);















//void Widget::closeEvent(QCloseEvent *){
//    //接收到关闭窗口的信号后
//    emit this->closeWidget();
//}
////广播udp消息
//void Widget::sndMsg(MsgType type){
//    //发送的消息分为三种类型
//    //发送的数据，做分段处理 第一段（类型），第二段（用户名），第三段（具体内容）
//    //通过数据流的操作实现对于数据的分段操作
//    QByteArray array;
//    QDataStream stream(&array,QIODevice::WriteOnly);
//    stream << type << getUsr();
//    switch(type){
//    case Msg:       //普通消息发送
//        //如果输入的消息为空的话直接不发送任何消息
//        if(ui->msgEdit->toPlainText() == "") {
//            QMessageBox::warning(this,"警告","发送内容不能为空");
//            return;
//        }
//        //第三段的数据
//        stream << getMsg();
//        break;
//    case UsrEnter:      //新用户进入消息发送
//        break;
//    case UsrLeft:       //用户离开消息发送
//        break;
//    default:
//        break;
//    }
//    //书写报文,广播发送
//    udpSocket->writeDatagram(array,QHostAddress::Broadcast,port);
//}
//QString Widget::getMsg(){
//    QString str = ui->msgEdit->toHtml();
//    //清空输入框
//    ui->msgEdit->clear();
//    //光标回到输入框内
//    ui->msgEdit->setFocus();
//    return str;
//}
//QString Widget::getUsr(){
//    return uName;
//}




//void Widget::ReceiveMessage(){
//    //获取数据的长度
//    qint64 my_size = udpSocket->pendingDatagramSize();
//    //读入数据
//    QByteArray array = QByteArray(my_size,0);
//    udpSocket->readDatagram(array.data(),my_size);
//    //解析数据
//    QDataStream stream(&array,QIODevice::ReadOnly);
//    int msgType;
//    QString otherUsername;
//    QString msg;
//    //获取当前的时间
//    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
//    stream >> msgType;
//    switch(msgType){
//    case Msg:
//        stream >> otherUsername >> msg;
//        //追加聊天记录
//        ui->msgBrowser->setTextColor(Qt::blue);
//        ui->msgBrowser->append("[" + otherUsername + "]" + time);
//        ui->msgBrowser->append(msg);
//        break;
//    default:
//        break;
// }


Widget::~Widget()
{
    delete ui;
}

