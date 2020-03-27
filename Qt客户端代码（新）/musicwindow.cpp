#include "musicwindow.h"
#include "ui_musicwindow.h"
#include<QDebug>
#include<QMessageBox>

musicWindow::musicWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::musicWindow)
{
   ui->setupUi(this);

  play=new QMediaPlayer;
  playlist=new QMediaPlaylist;

  add=false;

  connect(play,SIGNAL(positionChanged(qint64)),this,SLOT(showProcess(qint64)));
  connect(ui->Slider,SIGNAL(sliderMoved(int)),this,SLOT(changeProcess(int)));
  //connect()

}
int musicWindow::z=2;

musicWindow::~musicWindow()
{
    delete ui;
}


void musicWindow::showProcess(qint64 process)
{
    ui->Slider->setMaximum(play->duration()/100);//设置滑块最大值
    ui->Slider->setValue(process/100);//设置滑块值区间
}

void musicWindow::changeProcess(int process)
{
     play->setPosition(process * 100);//更改滑块位置
}


void musicWindow::on_play_clicked()
{
    if(add!=true)
    {

       QMessageBox::information(NULL, "提示", "请先添加音乐");
    }
    else
    {
    play->play();
    }
}

void musicWindow::on_next_clicked()
{
     playlist->next();
     return;
}

void musicWindow::on_prev_clicked()
{
    playlist->previous();
    return;
}

void musicWindow::on_pause_clicked()
{
      play->pause();
}

void musicWindow::on_add_clicked()
{
    playlist->setPlaybackMode(QMediaPlaylist::Sequential);//设置列表音乐播放方式顺序播放
    playlist->addMedia(QUrl("E:/Qt-project/SmartHome/music/1.mp3"));//在播放列表中添加音乐
    playlist->addMedia(QUrl("E:/Qt-project/SmartHome/music/2.mp3"));
    playlist->addMedia(QUrl("E:/Qt-project/SmartHome/music/3.mp3"));
    playlist->addMedia(QUrl("E:/Qt-project/SmartHome/music/4.mp3"));
    play->setPlaylist(playlist);
     QMessageBox::information(NULL, "提示", "添加成功");
    add=true;
}

void musicWindow::on_mode_clicked()
{
    if(z==0)
    {
        playlist->setPlaybackMode(QMediaPlaylist::Sequential);//顺序播放
        z=2;

    }
    else if(z==1)
    {
        playlist->setPlaybackMode(QMediaPlaylist::Random);//随机播放
        z--;
    }
    else
    {
        playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);//单曲循环
        z--;
    }

}

void musicWindow::on_sound_valueChanged(int value)
{
    play->setVolume(ui->sound->value());
}
