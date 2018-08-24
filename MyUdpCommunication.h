#ifndef MYUDPCOMMUNICATION_H
#define MYUDPCOMMUNICATION_H

#include <QObject>

class MyUpgradeProgram;
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

class MyUdpCommunication : public QObject
{
    Q_OBJECT

private:
    friend class MyUpgradeProgram;
    friend class MyUpgradeProgramPrivate;
    explicit MyUdpCommunication(QObject *parent = nullptr);

public:
    ~MyUdpCommunication();

    static QByteArray _getUserName();
    static QString getUserName();
    static QString getHostName();
    void sndMsg(MsgType type);


    QString getProduct() const;
    void setProduct(const QString &value);

    QString getUnicastIp() const;

    QString getSrvIp() const;
    void setSrvIp(const QString &value);

    QString getStationID() const;
    void setStationID(const QString &value);

    QString getPassword() const;
    void setPassword(const QString &value);

    QString getStationName() const;
    void setStationName(const QString &value);

signals:

public slots:
    void slotProcessPendingDatagrams();

private:
    QUdpSocket *udp;       
    QString srvIp       = "";
    QString product     = "Lewis";
    QString stationName = "FCT TEST";
    QString stationID   = "1";
    QString password    = "Password";
};

#endif // MYUDPCOMMUNICATION_H
