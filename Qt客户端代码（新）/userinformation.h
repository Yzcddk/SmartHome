#ifndef USERINFORMATION_H
#define USERINFORMATION_H
#include<QString>
#include<QChar>


class UserInformation
{
public:
    UserInformation(const  QString &username="",const QString &password="",const  QString &email="",const  QString &phone="");

    QString getPassword() const;
    void setPassword(const QString &value);
    QString getUsername() const;
    void setUsername(const QString &value);
    QString getPhone() const;
    void setPhone(const QString &value);
    QString getEmail() const;
    void setEmail(const QString &value);
private:
    QString password;
    QString username;
    QString phone;
    QString email;
};

#endif // USERINFORMATION_H
