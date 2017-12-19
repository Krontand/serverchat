#ifndef CLIENT_H
#define CLIENT_H

#include <QtNetwork>
#include <QObject>
#include <QString>
#include <QTcpSocket>

class Client: public QObject
{
Q_OBJECT
public:
    Client(QObject* parent = 0);
    ~Client();
    void start(QString address, quint16 port, QString nick);
    void receivedData(QStringList &data);
    void sendData(QString data);

    QStringList received;

public slots:
  void onNewData();
  void startTransfer();

signals:
  void newData();

private:
  QTcpSocket client;
  QString nick;

};

#endif // CLIENT_H
