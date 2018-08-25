#include "MyUdpCommunication.h"
#include "doc_Json.h"
#include <windows.h>
#include <QDebug>
#include <QSettings>
#include <QUdpSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include <QHostInfo>
#include <QTimer>
#include <QTime>

//udp 端口
const qint16 srvPort = 23232;
const qint16 cltPort = 23233;

MyUdpCommunication::MyUdpCommunication(QObject *parent) : QObject(parent)
{
    udp = new QUdpSocket(this);
    udp->bind(srvPort, QUdpSocket::QUdpSocket::DontShareAddress | QUdpSocket::ReuseAddressHint);
    connect(udp, &QUdpSocket::readyRead, this, &MyUdpCommunication::slotProcessPendingDatagrams);
    sndMsg(LogIn);

    //定时发送本机的登录信息，直到本机登录成功
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [&](){ sndMsg(LogIn);} );
    timer->start(1000);
}

MyUdpCommunication::~MyUdpCommunication()
{

}

void MyUdpCommunication::sndMsg(MsgType type)
{
    QJsonObject json;
    json.insert(MsgKey::Terminal, Client);
    json.insert(MsgKey::Tytp, type);

    switch (type) {
    case HeartBeat:
        //心跳包暂时由服务器发，客服端返回，所以不主动发送
        //服务端可以获取到发送端的ip，所以不记录其他消息，发空包过去即可
        break;

    case LogIn:
        //登录时，将所有信息全部发送出去
        json.insert(MsgKey::User,        getUserName());
        json.insert(MsgKey::Host,        getHostName());
        json.insert(MsgKey::Product,     getProduct());
        json.insert(MsgKey::StationName, getStationName());
        json.insert(MsgKey::StationID,   getStationID());
        json.insert(MsgKey::Password,    getPassword());
        json.insert(MsgKey::Version,     getVersion());
        break;

    case LogOut:
        //登出只需要让服务器知道本ip登出，所以也不需要记录其他消息
        break;

    default:
        break;
    }

    if (srvIp.isEmpty()) {
        //udp->writeDatagram(JS::jsonToDoc(json, QJsonDocument::Compact), QHostAddress::Broadcast, Port);
        udp->writeDatagram(JS::jsonToDoc(json), QHostAddress::Broadcast, cltPort);
    } else {
        //udp->writeDatagram(JS::jsonToDoc(json, QJsonDocument::Compact), QHostAddress(srvIp), Port);
        udp->writeDatagram(JS::jsonToDoc(json), QHostAddress(srvIp), cltPort);
    }
}

void MyUdpCommunication::slotProcessPendingDatagrams()
{
    QByteArray datagram;
    while (udp->hasPendingDatagrams()) {
        datagram.resize(udp->pendingDatagramSize());

        QHostAddress srvAddr;
        quint16 clientPort;
        udp->readDatagram(datagram.data(), datagram.size(), &srvAddr, &clientPort);
        if (srvIp != QHostAddress(srvAddr.toIPv4Address()).toString()) {
            srvIp = QHostAddress(srvAddr.toIPv4Address()).toString();
            //将服务器ip 写入ini，方便下次使用
            //占位符
        }
    }

    QJsonObject json;
    JS::donToJsObj(datagram, json);

    //只处理服务端的数据，客户端的数据直接退出不处理
    if ( !isServe( json.value(MsgKey::Terminal).toInt()) ) {
        return;
    }

    //各类消息的处理
    switch (json.value(MsgKey::Tytp).toInt()) {
    case LogIn:
        //发送登录消息后，服务器同样将登录消息返回回来
        //返回消息以后，就停止重复发送登录消息
        timer->stop();
        break;

    default:
        break;
    }
}

bool MyUdpCommunication::isServe(int _tpye)
{
    switch (_tpye) {
    case Client:
        return false;

    case Serve:
        return true ;

    default:
        qDebug()<< "void MyUdpCommunication::slotProcessPendingDatagrams()\n"
                   "这不应该出现第三种情况";
    }
    return false;
}

QString MyUdpCommunication::getVersion() const
{
    return version;
}

void MyUdpCommunication::setVersion(const QString &value)
{
    version = value;
}

QString MyUdpCommunication::getStationName() const
{
    return stationName;
}

void MyUdpCommunication::setStationName(const QString &value)
{
    stationName = value;
}

QString MyUdpCommunication::getPassword() const
{
    return password;
}

void MyUdpCommunication::setPassword(const QString &value)
{
    password = value;
}

QString MyUdpCommunication::getStationID() const
{
    return stationID;
}

void MyUdpCommunication::setStationID(const QString &value)
{
    stationID = value;
}

QString MyUdpCommunication::getSrvIp() const
{
    return srvIp;
}

void MyUdpCommunication::setSrvIp(const QString &value)
{
    srvIp = value;
}

QString MyUdpCommunication::getProduct() const
{
    return product;
}

void MyUdpCommunication::setProduct(const QString &value)
{
    product = value;
}

QByteArray MyUdpCommunication::_getUserName()
{
    char strBuffer[256] ={0};
    DWORD dwSize = 256;
    ::GetUserNameA(strBuffer,&dwSize);
    return strBuffer;
}

QString MyUdpCommunication::getUserName()
{
    //由于静态变量只初始化一次，所以第一句话也只运行一次，妙！！！
    static QString userName = _getUserName();
    return userName;
}

QString MyUdpCommunication::getHostName()
{
    //由于静态变量只初始化一次，所以第一句话也只运行一次，妙！！！
    static QString localHostName = QHostInfo::localHostName();
    return localHostName;
}
