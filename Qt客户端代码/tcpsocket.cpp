#include "tcpsocket.h"
#include <QHostAddress>
#include "serveraddressdialog.h"
#include <QMessageBox>

TcpSocket::TcpSocket()
{
    tcp = new QTcpSocket;
    connect(tcp,SIGNAL(readyRead()),this,SLOT(recvTcpData()));
}

TcpSocket::~TcpSocket()
{
    delete tcp;
}

void TcpSocket::recvTcpData()
{
    QByteArray tcpData = tcp->readAll();
    qDebug() << tcpData;
}

void TcpSocket::registerUserByTcp()
{
    QString serverIp   = ServerAddressDialog::getServerIP();
    short   serverPort = ServerAddressDialog::getServerPort();

    if(serverIp.isEmpty() || serverPort == 0){
         QMessageBox::warning(NULL,"没有服务器端地址信息","请输入服务器端地址信息以后再注册",QMessageBox::Yes,QMessageBox::Yes);
         return;
    }

    tcp->connectToHost(QHostAddress(serverIp),serverPort);
    QString data = "Hello World";
    tcp->write(data.toUtf8());

    return;
}
