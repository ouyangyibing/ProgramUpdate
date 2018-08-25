#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QUdpSocket;

namespace MsgKey {
const QString Terminal    = "Terminal";
const QString Tytp        = "Type";
const QString Host        = "HostName";
const QString User        = "UserName";
const QString Product     = "Product";
const QString StationName     = "StationName";
const QString StationID   = "StationID";
const QString Password    = "Password";
const QString Msg         = "Msg";
const QString SrvAddr     = "SrvAddr";
const QString RequestHeart= "SrvAddr";
}

/**************************
 * Terminal
 * Client:客户端
 * Serve:服务端
 **************************
 * Tytp
 * HeartBeat:心跳
 * Msg:消息
 * LogIn:登录
 * LogOut:登出
 * Version:版本
 *************************/
enum MsgType{Client, Serve, HeartBeat, Msg, LogIn, LogOut, Version};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


public slots:
    void slotProcessPendingDatagrams();

private:
    Ui::MainWindow *ui;

    QString srvIp;
    QUdpSocket *udp;
};

#endif // MAINWINDOW_H
