#include "myDao.h"
#include<QMessageBox>
/*
    此部分主要用于创建后端部分的数据库连接的部分，部分集合了关于数据库的操作的模块
*/

MyDao::MyDao()
{
    //数据初始化是成功的
   db =  new QSqlDatabase(QSqlDatabase::addDatabase("QODBC"));
   db->setHostName("127.0.0.1");
   db->setPort(3306);
   db->setDatabaseName("mysql");
   db->setUserName("root");
   db->setPassword("1234");
   bool ok = db->open();
   if (ok){
      qDebug()<<"能够连接";
      //在能够连接数据库的前提下,将user表中的数据绑定到指定的数据库中
     //对用户数据库中文件进行维护
      user_query = new QSqlQuery(*db);
   }
   else {
       qDebug()<< "不能连接";
   }

}

User MyDao::selectById(int id)
{

//    query.exec("select ");
}

//往数据库中添加一个用户
int MyDao::insertUser(User user)
{
  user_query->prepare("insert into T_USER( username,password,email) values(?,?,?);");
  user_query->addBindValue(user.getUser_name());
  QByteArray str;
  str = QCryptographicHash::hash(user.getUser_password().toLatin1(),QCryptographicHash::Md5);
  //对输入的密码进行MD5加密，注意MD5加密是不可逆的，对于数据库管理人员来说这种连接是
  user_query->addBindValue(str.toHex());
  user_query->addBindValue(user.getEmail());
  user_query->exec();
  //下面是连续田间对应的列表文件
//  //给字段设置内容 list
//  QVariantList nameList;
//  nameList<<user.getUser_name();
//  QVariantList passList;
//  ageList<<11<<22<<33;
//  QVariantList scoreList;
//  scoreList<<59<<69<<79;
//  //给字段绑定相应的值，按顺序绑定
//  user_query->addBindValue(nameList);
//  query.addBindValue(ageList);
//  query.addBindValue(scoreList);
  //执行预处理命令
//  query.execBatch();

}
