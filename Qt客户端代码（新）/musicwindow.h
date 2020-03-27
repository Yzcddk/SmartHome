#ifndef MUSICWINDOW_H
#define MUSICWINDOW_H
#include <QMediaPlayer>
#include <QMainWindow>
#include<QMediaPlaylist>

namespace Ui {
class musicWindow;
}

class musicWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit musicWindow(QWidget *parent = 0);
    ~musicWindow();
    static int z;
signals:

private slots:

    void showProcess(qint64 process); //将音乐播放以进度条的形式显示。
    void changeProcess(int process);  //改变播放进度

    void on_play_clicked();

    void on_next_clicked();

    void on_prev_clicked();

    void on_pause_clicked();

    void on_add_clicked();

    void on_mode_clicked();

    void on_sound_valueChanged(int value);

private:
    Ui::musicWindow *ui;
    QMediaPlayer *play;//播放器
    QMediaPlaylist *playlist; //播放列表

    bool add;
};

#endif // MUSICWINDOW_H
