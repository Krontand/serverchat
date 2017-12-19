#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "client.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_pushButton_clicked();

    void showNewData();

    void on_edtMsg_returnPressed();

private:
    Ui::MainWindow *ui;
    Client *client;
};

#endif // MAINWINDOW_H
