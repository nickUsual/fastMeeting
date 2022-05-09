#include "user.h"

User::User(QString name, QString password, QString myemail)
{
    user_name = name;
    user_password= password;
    email= myemail;
}

int User::getUser_id() const
{
    return user_id;
}

void User::setUser_id(int value)
{
    user_id = value;
}

QString User::getUser_name() const
{
    return user_name;
}

void User::setUser_name(const QString &value)
{
    user_name = value;
}

QString User::getUser_password() const
{
    return user_password;
}

void User::setUser_password(const QString &value)
{
    user_password = value;
}

int User::getType() const
{
    return type;
}

void User::setType(int value)
{
    type = value;
}

int User::getStatus() const
{
    return status;
}

void User::setStatus(int value)
{
    status = value;
}

QString User::getUser_meeting() const
{
    return user_meeting;
}

void User::setUser_meeting(const QString &value)
{
    user_meeting = value;
}

QDate User::getCreate_time() const
{
    return create_time;
}

void User::setCreate_time(const QDate &value)
{
    create_time = value;
}

QDate User::getUpdate_time() const
{
    return update_time;
}

void User::setUpdate_time(const QDate &value)
{
    update_time = value;
}

QString User::getEmail() const
{
    return email;
}

void User::setEmail(const QString &value)
{
    email = value;
}


