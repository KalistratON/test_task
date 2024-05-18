#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QUdpSocket>
#include <QDataStream>
#include <QByteArray>
#include <QVector>

class Server : public QObject
{
    Q_OBJECT

private:
    QUdpSocket* socket = nullptr;

    const size_t count = 9;

    QVector<quint16> pack;

    QHostAddress host = QHostAddress::LocalHost;
    quint16 port = 1234;

    QHostAddress clientHost = QHostAddress::LocalHost;
    quint16 clientPort = 1234;


public:
    explicit Server(QObject *parent = nullptr);

signals:

private:
    void initConnection();
    void process();
    void sendTo(bool);

private slots:
    void recvFrom();
};

#endif // SERVER_H
