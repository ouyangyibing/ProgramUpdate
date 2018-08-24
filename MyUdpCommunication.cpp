#include "MyUdpCommunication.h"
#include "doc_Json.h"
#include <windows.h>
#include <QDebug>
#include <QSettings>
#include <QUdpSocket>
#include <QJsonObject>
#include <QJsonDocument>

const qint16 port = 23232;

MyUdpCommunication::MyUdpCommunication(QObject *parent) : QObject(parent)
{
    udp = new QUdpSocket;
    udp->bind(port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    connect(udp, &QUdpSocket::readyRead, this, &MyUdpCommunication::slotProcessPendingDatagrams);
}

MyUdpCommunication::~MyUdpCommunication()
{

}

QByteArray MyUdpCommunication::gitUserName()
{
    static bool firstTime = true;
    static QByteArray userName;

    //如果是第一次，就获取用户名
    if (firstTime) {
        firstTime = false;
        char strBuffer[256] ={0};
        DWORD dwSize = 256;
        ::GetUserNameA(strBuffer,&dwSize);
        userName = strBuffer;
        return userName;

        //不是第一次的话，直接返回之前获取的用户名
    } else {
        return userName;
    }
}

void MyUdpCommunication::slotProcessPendingDatagrams()
{
    QByteArray datagram;
    while (udp->hasPendingDatagrams()) {
        datagram.resize(udp->pendingDatagramSize());
        QHostAddress client;
        quint16 clientPort;

        udp->readDatagram(datagram.data(), datagram.size(), &client, &clientPort);
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
