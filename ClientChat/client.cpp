#include "client.h"
#include <QHostAddress>

Client::Client(QObject* parent): QObject(parent)
{
    connect(&client, SIGNAL(connected()), this, SLOT(startTransfer()));
    connect(&client, SIGNAL(readyRead()), this, SLOT(onNewData()));
}

Client::~Client()
{
    client.close();
}

void Client::start(QString address, quint16 port, QString nick)
{
    QHostAddress addr(address);
    client.connectToHost(addr, port);
    this->nick = nick;
}

void Client::receivedData(QStringList &data)
{
    data = received;
}

void Client::sendData(QString data)
{
    QByteArray qba = data.toLocal8Bit();
    client.write(data.toLocal8Bit(), qba.length());
}

void Client::startTransfer()
{
    client.write(nick.toLocal8Bit(), nick.length());
}

void Client::onNewData()
{
    QStringList list;
    char *c = client.readLine().data();
    QString data = QString::fromLocal8Bit(c);
    received.append(data);
    emit newData();
}

