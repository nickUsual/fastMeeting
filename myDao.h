#ifndef MYDAO_H
#define MYDAO_H
#include <QApplication>
#include <QSqlDatabase>
#include <QDebug>
#include <QStringList>
#include <QSqlQuery>
#include <QSqlError>
#include "user.h"
#include <QCryptographicHash>
/**
 * @brief The MyDao class
 * 本层主要用于创建连接数据库的方法，先集成了连接数据库的各种的使用的包括查询，插入，
 */
class MyDao
{
private:
    QSqlDatabase *db;//连接数据库的接口,初始化出现内存错误，需注意
    QSqlQuery *user_query;//绑定数据库中user表的文件
public:
    MyDao();
    User selectById(int id);
    User selectByName(QString name);
    User selectByEmail(QString email);
    int insertUser(User user);//往数据库当中插入一个用户，用户对象中含有用户名，密码和邮箱，密码采用md5加密的方式
    int updatePassword(QString name,QString password);
    int updateEmail(QString name,QString email);
};




#endif // MYDAO_H
