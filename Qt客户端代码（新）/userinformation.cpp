#include "userinformation.h"

UserInformation::UserInformation(const QString &username, const QString &password, const QString &email, const QString &phone)
{
  this->username=username;
    this->password=password;
    this->email=email;
    this->phone=phone;
}

QString UserInformation::getEmail() const
{
    return email;
}

void UserInformation::setEmail(const QString &value)
{
    email = value;
}

QString UserInformation::getPhone() const
{
    return phone;
}

void UserInformation::setPhone(const QString &value)
{
    phone = value;
}

QString UserInformation::getUsername() const
{
    return username;
}

void UserInformation::setUsername(const QString &value)
{
    username = value;
}

QString UserInformation::getPassword() const
{
    return password;
}

void UserInformation::setPassword(const QString &value)
{
    password = value;
}
