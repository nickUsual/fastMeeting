#ifndef USER_H
#define USER_H

#include <QApplication>
#include <QString>
#include <QDebug>
#include <QStringList>
#include <QDate>
class User
{
private:
    int user_id;
    QString user_name;
    QString user_password;
    QString email;
    int  type;//用户的类型,type为0的时候为管理员，type为1的时候为普通用户
    int  status;//用户的状态，用户的状态，后台可以显示用户当前的状态是处于登录还是离线
    QDate create_time;//创建用户的时间，用于后台的访问记录
    QDate update_time;//更新用户的时间，用于后台的访问记录
    QString user_meeting;//用户用于创建的会议号的id,初始的时候分配一个会议号,处于空状态的时候会议号为0
public:
    User(QString name,QString password,QString email);
    int getUser_id() const;
    void setUser_id(int value);
    QString getUser_name() const;
    void setUser_name(const QString &value);
    QString getUser_password() const;
    void setUser_password(const QString &value);
    int getType() const;
    void setType(int value);
    int getStatus() const;
    void setStatus(int value);
    QString getUser_meeting() const;
    void setUser_meeting(const QString &value);
    QDate getCreate_time() const;
    void setCreate_time(const QDate &value);
    QDate getUpdate_time() const;
    void setUpdate_time(const QDate &value);
    QString getEmail() const;
    void setEmail(const QString &value);
};

#endif // USER_H
