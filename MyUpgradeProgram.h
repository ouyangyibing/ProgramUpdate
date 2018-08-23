#ifndef MYUPGRADEPROGRAM_H
#define MYUPGRADEPROGRAM_H

#include <QObject>

class QThread;
class MyUpgradeProgramPrivate;

class MyUpgradeProgram : public QObject
{
    Q_OBJECT
public:
    explicit MyUpgradeProgram(QObject *parent = nullptr);
    ~MyUpgradeProgram();

    static bool isUpdataEnabled();

signals:

public slots:

private:
    bool isClean = false;
    QThread *thread;
    MyUpgradeProgramPrivate *task;

    void creationUpdataThread();
};

#endif // MYUPGRADEPROGRAM_H
