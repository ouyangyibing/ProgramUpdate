#include "MyUdpCommunication.h"
#include <QUdpSocket>

MyUdpCommunication::MyUdpCommunication(QObject *parent) : QObject(parent)
{
    udp = new QUdpSocket;
}

MyUdpCommunication::~MyUdpCommunication()
{

}
