#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QChar>
#include"room.h"
#include "tcpsocket.h"
#include"musicwindow.h"
#include<QNetworkAccessManager>
#include<QNetworkReply>
#include<QNetworkRequest>
#include<widget.h>




namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void timerEvent(QTimerEvent *event);


    QString getClienId() const;
    void setClienId(const QString &value);

private slots:
    void on_dvicebutton_clicked();
        void controlDeviceSlot(int deviceId,int statu);
        void on_pushButton_2_clicked();
        void displayReplyData();

        void on_pushButton_clicked();

       // void on_pushButton_4_clicked();

        void on_pushButton_4_clicked();

private:
      Ui::MainWindow *ui;
      musicWindow *music;
      room *roomWin;
      QString clienId;
      TcpSocket *tcp;
      QNetworkAccessManager *networkManager;
      QNetworkReply *networkReply;
      Widget  *camera;




};

#endif // MAINWINDOW_H
