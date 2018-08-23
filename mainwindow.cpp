#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "MyUpgradeProgram.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    up = new MyUpgradeProgram(this);
    //ui->pushButton->setEnabled();
}

MainWindow::~MainWindow()
{
    delete ui;
}
