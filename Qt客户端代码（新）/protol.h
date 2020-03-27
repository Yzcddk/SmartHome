#ifndef PROTOL_H
#define PROTOL_H
#include"userinformation.h"
#include<QJsonObject>


class Protol
{
public:
    enum{
        USER_REGISTER=1,
         USER_LOGIN = 2,
             USER_DEVICE_CONTROL = 3,

    };

    Protol(const UserInformation &user);
    Protol(const QByteArray &jsonData);
 Protol(const QString &username,const QString &password);
Protol(const QString &clientId,int deviceId,int statu);
      void addFunctionId(int id);
    QByteArray toProtocolData(void);
        bool getSmartProtocolStatu();
         int getSmartProtocolFunctionId(void);
        QString getSmartProtocolError();
         QString getSmartProtocolClientId(void);
private:
    QJsonObject content;
};

#endif // PROTOL_H
