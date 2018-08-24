#include "MyUdpCommunication.h"
#include "doc_Json.h"
#include <windows.h>
#include <QDebug>
#include <QSettings>
#include <QUdpSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include <QHostInfo>

const qint16 Port = 23232;
//const qint16 connectPort = 23233;

MyUdpCommunication::MyUdpCommunication(QObject *parent) : QObject(parent)
{
    udp = new QUdpSocket;
    udp->bind(Port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    connect(udp, &QUdpSocket::readyRead, this, &MyUdpCommunication::slotProcessPendingDatagrams);
    sndMsg(HeartBeat);
}

MyUdpCommunication::~MyUdpCommunication()
{

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

void MyUdpCommunication::sndMsg(MsgType type)
{
    QJsonObject json;
    json.insert(MsgKey::Terminal, Client);
    //json.insert(MsgKey::Tytp, type);

    switch (type) {
    case HeartBeat:
        json.insert(MsgKey::User,        getUserName());
        json.insert(MsgKey::Host,        getHostName());
        json.insert(MsgKey::Product,     getProduct());
        json.insert(MsgKey::StationName, getStationName());
        json.insert(MsgKey::StationID,   getStationID());
        json.insert(MsgKey::Password,    getPassword());

        break;
    default:
        break;
    }

    srvIp = "192.168.31.236";
    if (srvIp.isEmpty()) {
        //udp->writeDatagram(JS::jsonToDoc(json, QJsonDocument::Compact), QHostAddress::Broadcast, Port);
        udp->writeDatagram(JS::jsonToDoc(json), QHostAddress::Broadcast, Port);
    } else {
        //udp->writeDatagram(JS::jsonToDoc(json, QJsonDocument::Compact), QHostAddress(srvIp), Port);
        udp->writeDatagram(JS::jsonToDoc(json), QHostAddress(srvIp), Port);
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
            //将ip 写入ini，方便下次使用
            //占位符
        }
    }

    QJsonObject json;
    JS::donToJsObj(datagram, json);

    //只处理服务端的数据，客户端的数据直接退出不处理
    switch (json.value(MsgKey::Terminal).toInt()) {
    case Client:
        return ;

    case Serve:
        break ;

    default:
        qDebug()<< "void MyUdpCommunication::slotProcessPendingDatagrams()\n"
                   "这不应该出现第三种情况";
    }

    //各类消息的处理
    switch (json.value(MsgKey::Tytp).toInt()) {
    case HeartBeat:

        break;
    default:
        break;
    }
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
