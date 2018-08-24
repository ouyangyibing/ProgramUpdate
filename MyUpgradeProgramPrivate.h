#ifndef MYUPGRADEPROGRAMPRIVATE_H
#define MYUPGRADEPROGRAMPRIVATE_H

#include <QObject>
#include "MyUpgradeProgram.h"

class QSettings;

class MyUpgradeProgramPrivate : public QObject
{
    Q_OBJECT

private:
    friend class MyUpgradeProgram;
    explicit MyUpgradeProgramPrivate(QObject *parent = nullptr);

public:
    ~MyUpgradeProgramPrivate(){}

signals:
    void startTask();

public slots:
    void slotStartTask();

private:
    QSettings *setting = nullptr;
};

#endif // MYUPGRADEPROGRAMPRIVATE_H
