#include "MyUpgradeProgram.h"
#include "MyUpgradeProgramPrivate.h"
#include <QThread>
#include <QDebug>
#include <QSettings>
#include <QFile>

MyUpgradeProgram::MyUpgradeProgram(QObject *parent) : QObject(parent)
{    
    //检查是否启用程序自动更新的功能
    //if (!isUpdataEnabled()) {
    //    return ;
    //}

    //if (QFile::exists("Setup")) {
    //如果存在，则启动替换程序的批处理，并退出此程序
    //}

    //启动UDP检查更新



    //开始************************************************
    //1.检查缓存区是否存在待更新的应用，应该有一个文件作为缓存
    //  更新完成的标识符，不然中途退出，那就有问题
    //2.如果存在更新，启动批处理，替换主程序
    //3.重新启动程序
    //4.如果以上都没问题了，那就建立次线程，开始检查更新
    creationUpdataThread();
}

MyUpgradeProgram::~MyUpgradeProgram()
{
    if (task) {
        task->deleteLater();
        task = nullptr;
    }

    if (thread) {
        thread->exit(0);
        thread->wait(100);
        thread->deleteLater();
        thread = nullptr;
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
