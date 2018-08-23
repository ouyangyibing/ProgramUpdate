#ifndef MYUDPCOMMUNICATION_H
#define MYUDPCOMMUNICATION_H

#include <QObject>

class QUdpSocket;

class MyUdpCommunication : public QObject
{
    Q_OBJECT

private:
    friend class MyUdpCommunication;
    explicit MyUdpCommunication(QObject *parent = nullptr);

public:
    ~MyUdpCommunication();

signals:

public slots:

private:
    QUdpSocket *udp;
};

#endif // MYUDPCOMMUNICATION_H
