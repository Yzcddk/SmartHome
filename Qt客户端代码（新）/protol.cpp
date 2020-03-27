#include "protol.h"
#include<QJsonDocument>
#include<QDebug>

Protol::Protol(const UserInformation &user)
{
          content.insert("username",user.getUsername());
          content.insert("password",user.getPassword());
          content.insert("phone",user.getPhone());
          content.insert("email",user.getEmail());
}

Protol::Protol(const QByteArray &jsonData)
{
   qDebug() << jsonData;
   QJsonParseError jsonError;
   QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData,&jsonError);
   if(jsonDoc.isEmpty()||jsonError.error!=QJsonParseError::NoError){
        qDebug() << "fail to from json"  << jsonError.errorString();
   }
   content = jsonDoc.object();
}

Protol::Protol(const QString &username, const QString &password)
{
    content.insert("username",username);
    content.insert("password",password);
}
Protol::Protol(const QString &clientId, int deviceId, int statu)
{
    content["clientId"] = clientId;
    content["deviceId"] = deviceId;
    content["controlStatu"] = statu;
}

void Protol::addFunctionId(int id)
{
    content["functionId"] = id;
}


QByteArray Protol::toProtocolData()
{
    QJsonDocument jsonDoc(content);
    return jsonDoc.toJson();
}

bool Protol::getSmartProtocolStatu()
{
    //int ret = content.value("statu").toInt();

    int ret = content["statu"].toInt();
    if(ret != 0){
        return false;
    }

    return true;
}

int Protol::getSmartProtocolFunctionId()
{
    return content["functionId"].toInt();
}
QString Protol::getSmartProtocolError()
{
    QString errorString = content["error"].toString();
    return errorString;
}

QString Protol::getSmartProtocolClientId()
{
    return content["clientId"].toString();
}
