#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MyUpgradeProgram;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    MyUpgradeProgram *up;
};

#endif // MAINWINDOW_H
