#include "tcpsocket.h"
#include<QHostAddress>
#include<QMessageBox>
#include"severaddress.h"
#include"protol.h"
TcpSocket::TcpSocket()
{
   tcp= new QTcpSocket;
   connect(tcp,SIGNAL(readyRead()),this,SLOT(recvTcpData()));
}

TcpSocket::~TcpSocket(){
    delete tcp;
}

void TcpSocket::recvTcpData()
{
    QString errorString;
    QByteArray tcpData=tcp->readAll();
    Protol Protol(tcpData);
    if(Protol.getSmartProtocolStatu()==true){
        errorString="";

    }else{
        errorString=Protol.getSmartProtocolError();

    }
    switch(Protol.getSmartProtocolFunctionId()){
    case Protol::USER_REGISTER:
    emit registerStatu(errorString);
    break;
    case Protol::USER_LOGIN:
        emit loginStatu(errorString,Protol.getSmartProtocolClientId());
        break;

    }return;
}

void TcpSocket::TcpSeverset(const UserInformation &user)
{

    QString serverIp=severAddress::getServerIp();
    short serverPort=severAddress::getServerPort();
    if(serverIp.isEmpty()||serverPort==0){
        QMessageBox::warning(NULL,"错误:","请输入服务器信息之后注册",QMessageBox::Yes,QMessageBox::Yes);

        return;
    }
    if(tcp->state()==QTcpSocket::UnconnectedState){
        tcp->connectToHost(QHostAddress(serverIp),serverPort);
    }

   Protol Protol(user);
   Protol.addFunctionId(Protol::USER_REGISTER);
    tcp->write(Protol.toProtocolData());

    return;
}

void TcpSocket::loginUserByTcp(const QString &username,const QString &password)
{    QString serverIp=severAddress::getServerIp();
     short serverPort=severAddress::getServerPort();

     if(serverIp.isEmpty()||serverPort==0){
         QMessageBox::warning(NULL,"错误:","请输入服务器信息之后登陆",QMessageBox::Yes,QMessageBox::Yes);

         return;
     }
     if(tcp->state()==QTcpSocket::UnconnectedState){
         tcp->connectToHost(QHostAddress(serverIp),serverPort);
     }
 Protol rotol(username,password);

 rotol.addFunctionId(Protol::USER_LOGIN);
  tcp->write(rotol.toProtocolData());
     return;

}

void TcpSocket::controlDeviceByTcp(int deviceId, int statu,const QString &clientId)
{
    QString serverIp   = severAddress::getServerIp();
    short   serverPort = severAddress::getServerPort();

    if(serverIp.isEmpty() || serverPort == 0){
         QMessageBox::warning(NULL,"没有服务器端地址信息","请输入服务器端地址信息以后再登录",QMessageBox::Yes,QMessageBox::Yes);
         return;
    }

    if(tcp->state() == QTcpSocket::UnconnectedState){
       tcp->connectToHost(QHostAddress(serverIp),serverPort);
    }

   Protol Protol(clientId,deviceId,statu);
    Protol.addFunctionId(Protol::USER_DEVICE_CONTROL);
    tcp->write(Protol.toProtocolData());

    return;
}
