#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QUdpSocket;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


public slots:
    void slotProcessPendingDatagrams();

private:
    Ui::MainWindow *ui;

    QString srvIp;
    QUdpSocket *udp;
};

#endif // MAINWINDOW_H
