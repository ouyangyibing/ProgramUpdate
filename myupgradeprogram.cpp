#include "MyUpgradeProgram.h"
#include "MyUpgradeProgramPrivate.h"
#include <QThread>
#include <QDebug>
#include <QSettings>

MyUpgradeProgram::MyUpgradeProgram(QObject *parent) : QObject(parent)
{    
    if (isUpdataEnabled()) {
        creationUpdataThread();
    }
}

MyUpgradeProgram::~MyUpgradeProgram()
{    
    if (isClean) {
        task->deleteLater();

        thread->exit(0);
        thread->wait(100);
        thread->deleteLater();
    }
}

bool MyUpgradeProgram::isUpdataEnabled()
{
    bool enabled = true;

    QSettings setting("./Setup/IsUpdataEnabled.ini", QSettings::IniFormat);

    if (setting.contains("Updata/Enabled")) {
        enabled = setting.value("Updata/Enabled").toBool();

    } else {
        setting.setValue("Updata/Enabled", enabled);
    }

    return enabled;
}

void MyUpgradeProgram::creationUpdataThread()
{
    //结束时清理对象
    isClean = true;
    //建立线程
    thread = new QThread();
    //建立任务
    task = new MyUpgradeProgramPrivate();
    //移动任务至次线程
    task->moveToThread(thread);
    //开始线程
    thread->start();
    //开始任务
    task->startTask();
}
