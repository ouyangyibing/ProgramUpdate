#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QUdpSocket>
#include <QHostAddress>
#include "doc_Json.h"

const qint16 Port = 23232;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    udp = new QUdpSocket;
    udp->bind(Port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
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
    ui->textBrowser->append("srv ip:" + srvIp);
    ui->textBrowser->append("srv port:" + QString::number(clientPort));
    ui->textBrowser->append(QString::fromLocal8Bit(datagram) + "\n");

    setWindowState(Qt::WindowMinimized);
    setWindowState(Qt::WindowActive);
    raise();
    activateWindow();
}
