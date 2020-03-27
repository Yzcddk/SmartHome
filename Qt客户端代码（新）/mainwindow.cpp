#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<QTime>
#include<QString>
#include<QDate>
#include"room.h"
#include"tcpsocket.h"
#include<QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>





MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    camera=new Widget;
    roomWin=new room;
    music=new musicWindow;

    connect(roomWin,SIGNAL(controlDevice(int,int)),this,SLOT(controlDeviceSlot(int,int)));
    tcp = new TcpSocket;
    
    networkManager=new QNetworkAccessManager;
    QString httpUrl="http://www.tianqiapi.com/api/";
    QNetworkRequest request(httpUrl);//获取网络请求
    request.setRawHeader("version","v1");//设置头

    networkReply= networkManager->get(request);//发送请求
    connect(networkReply,SIGNAL(finished()),this,SLOT(displayReplyData()));

    this->startTimer(1000);

}

MainWindow::~MainWindow()
{
    delete ui;
    //delete Room;

}

void MainWindow::timerEvent(QTimerEvent *event)
{
    //qDebug()<<"timeEvent";
    QTime time=QTime::currentTime();
    ui->timelabel->setText(time.toString("hh:mm:ss"));
    //QTime data=QTime::currentTime();

    QDate date=QDate::currentDate();
    ui->datalabel->setText(date.toString("yyyy-MM-dd dddd"));
}
void MainWindow::on_dvicebutton_clicked()
{
roomWin->show();
}
void MainWindow::controlDeviceSlot(int deviceId, int statu)
{
    //通过tcp发出控制指令
    tcp->controlDeviceByTcp(deviceId,statu,clienId);
}
QString MainWindow::getClienId() const
{
    return clienId;
}

void MainWindow::setClienId(const QString &value)
{
    clienId = value;
}


void MainWindow::on_pushButton_2_clicked()
{
    music->show();
}

void MainWindow::displayReplyData()
{
    QByteArray jsonData=networkReply->readAll();

    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData,&jsonError);
    if(jsonDoc.isEmpty()||jsonError.error!=QJsonParseError::NoError){
         qDebug() << "aa"  << jsonError.errorString();
         return;
    }
    QJsonObject jsonObject=jsonDoc.object();//通过jsonDoc()获取json文本对象
    QJsonArray dataArray=jsonObject["data"].toArray();
    QJsonObject firstObject=dataArray[0].toObject();
    int humidity=firstObject["humidity"].toInt();
    QString tem=firstObject["tem"].toString();
    int wea=firstObject["wea"].toInt();
    
    QString temText=QString("%1:%2").arg(ui->temlabel->text()).arg(tem);
    ui->temlabel->setText(temText);

    QString humidityText=QString("%1:%2").arg(ui->humiditylabel->text()).arg(humidity);
    ui->humiditylabel->setText(humidityText);


    QString weaText=QString("%1:%2").arg(ui->wealabel->text()).arg(wea);
    ui->wealabel->setText(weaText);
}

void MainWindow::on_pushButton_clicked()
{
    camera->show();
}



void MainWindow::on_pushButton_4_clicked()
{

}
