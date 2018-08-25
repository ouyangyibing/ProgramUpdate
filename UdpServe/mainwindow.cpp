#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QUdpSocket>
#include <QHostAddress>
#include "doc_Json.h"

//udp 端口
const qint16 srvPort = 23232;
const qint16 cltPort = 23233;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    udp = new QUdpSocket;
    udp->bind(cltPort, QUdpSocket::DontShareAddress | QUdpSocket::ReuseAddressHint);
    connect(udp, &QUdpSocket::readyRead, this, &MainWindow::slotProcessPendingDatagrams);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotProcessPendingDatagrams()
{
    QByteArray datagram;
    QHostAddress srvAddr;
    quint16 clientPort;

    while (udp->hasPendingDatagrams()) {
        datagram.resize(udp->pendingDatagramSize());
        udp->readDatagram(datagram.data(), datagram.size(), &srvAddr, &clientPort);
        if (srvIp != QHostAddress(srvAddr.toIPv4Address()).toString()) {
            srvIp = QHostAddress(srvAddr.toIPv4Address()).toString();
            //将ip 写入ini，方便下次使用
            //占位符
        }
    }

    QJsonObject json_;
    JS::donToJsObj(datagram, json_);
    switch (json_.value(MsgKey::Terminal).toInt()) {
    case Serve:
        //return;

    case Client:
        break;

    default:
        break;
    }

    ui->textBrowser->append("srv ip:" + srvIp);
    ui->textBrowser->append("srv port:" + QString::number(clientPort));
    ui->textBrowser->append(QString::fromLocal8Bit(datagram) + "\n");

    //setWindowState(Qt::WindowMinimized);
    //setWindowState(Qt::WindowActive);
    raise();
    activateWindow();

    QJsonObject json;
    json.insert(MsgKey::Terminal, Serve);
    json.insert(MsgKey::Tytp, HeartBeat);
    udp->writeDatagram(JS::jsonToDoc(json), QHostAddress(srvIp), srvPort);
}
