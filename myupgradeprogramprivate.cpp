#include "MyUpgradeProgramPrivate.h"
#include <QDebug>
#include <QThread>
#include <QSettings>

MyUpgradeProgramPrivate::MyUpgradeProgramPrivate(QObject *parent) : QObject(parent)
{    
    connect(this, &MyUpgradeProgramPrivate::startTask,
            this, &MyUpgradeProgramPrivate::slotStartTask);
}

void MyUpgradeProgramPrivate::slotStartTask()
{    
    qDebug()<< "start" ;
}
