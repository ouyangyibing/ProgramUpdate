#include "MyUpgradeProgramPrivate.h"
#include <QDebug>
#include <QSettings>
#include <windows.h>

MyUpgradeProgramPrivate::MyUpgradeProgramPrivate(QObject *parent) : QObject(parent)
{    
    connect(this, &MyUpgradeProgramPrivate::startTask,
            this, &MyUpgradeProgramPrivate::slotStartTask);
}

void MyUpgradeProgramPrivate::slotStartTask()
{    
    qDebug()<< "start" ;
}
