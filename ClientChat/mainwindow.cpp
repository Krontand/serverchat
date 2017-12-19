#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    client = new Client();
    connect(client, SIGNAL(newData()), this, SLOT(showNewData()));
}

MainWindow::~MainWindow()
{
    delete client;
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    client->start(ui->edtAddr->text(), ui->edtPort->text().toInt(), "[" + ui->edtNick->text() + "] ");
}

void MainWindow::showNewData()
{
    foreach (const QString &str, client->received)
        ui->edtChat->append(str);
    client->received.clear();
}

void MainWindow::on_edtMsg_returnPressed()
{
      ui->edtChat->append(ui->edtMsg->text());
      client->sendData(ui->edtMsg->text());
      ui->edtMsg->clear();
}
