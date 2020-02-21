#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QTcpSocket>

class TcpSocket:public QObject
{
    Q_OBJECT

public:
    TcpSocket();
    ~TcpSocket();

public slots:
    void recvTcpData(void);
    void registerUserByTcp();

private:
   QTcpSocket *tcp;
};

#endif // TCPSOCKET_H
