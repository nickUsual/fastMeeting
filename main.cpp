#include "Widget.h"
#include"dialoglist.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QDebug>

#include "meetlogin.h"
#include "myDao.h"
#include "chattingwidget.h"
#include "settingwidget.h"

#include "videochat.h"

#include "sharecontrol.h"
#include "ken/form.h"
#include "ken/se.h"
#include "ExternVariable.h"
#include "recvcontrolwidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    Widget w;
//    w.show();

//    DialogList dialog;
//    dialog.show();
//     return a.exec();


    //测试主程序登录接口
//    Kernel test;
    kern = new Kernel();
    meetlogin m;
    m.show();
    return a.exec();

    //测试ChattingWidget
//    ChattingWidget w;
//    w.show();
//    return a.exec();

    //测试widget
//    Widget w(0,"某用户");
//    w.show();
//    return a.exec();

    //测试DislogList
//    DialogList dialog;
//    dialog.show();
//    return a.exec();

    //测试Videochat
//    VideoChat v;
//    v.show();
//    return a.exec();


    //测试SettingWidget
//    SettingWidget s;
//    s.show();
//    return a.exec();

//测试shareControl

//    ShareControl  s;
//    s.show();
//    return a.exec();


    //测试recvControl
//    RecvControlWidget wi;
//    wi.show();
//    return a.exec();



//   qDebug()<<"Avaliable drivers;";
//        QStringList drivers = QSqlDatabase::drivers();
//        foreach(QString driver,drivers)
//            qDebug()<<driver;

   /**
    * @brief dao
    * 下面为数据库dao层的测试部分
    */
//   MyDao dao;
//   User temp_user("list2","1234","2065@123.com");
//   if(dao.insertUser(temp_user)){
//       qDebug() << "添加成功";
//   }
//   return a.exec();

}
