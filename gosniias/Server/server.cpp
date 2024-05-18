#include "Server.h"

Server::Server(QObject *parent)
    : QObject{parent}
{
    pack.reserve(qsizetype(4));
    pack.resize(qsizetype(4));

    initConnection();
}

void Server::initConnection()
{
    qDebug() << "init : Server";

    socket = new QUdpSocket(this);
    socket->bind(host, port);

    connect(socket, SIGNAL(readyRead()), this, SLOT(recvFrom()));
}

void Server::recvFrom()
{
    qDebug() << "recvFrom : Server";

    QByteArray datagram;

    while (socket->hasPendingDatagrams())
    {
        datagram.resize(qsizetype(socket->pendingDatagramSize()));
        socket->readDatagram(datagram.data(), datagram.size(), &clientHost, &clientPort);
    }

    QDataStream data(&datagram, QIODevice::ReadOnly);
    for (auto& iter : pack)
        data >> iter;

    process();
}

void Server::sendTo(bool flag)
{
    qDebug() << "sendTo : Server";

    QByteArray data;
    QDataStream datagram(&data, QIODevice::WriteOnly);
    datagram << flag;

    socket->writeDatagram(data, clientHost, clientPort);
}

void Server::process()
{
    qDebug() << "process : Server";
    for (const auto& iter : pack) qDebug() << QString::number(iter, 2);

    qDebug() << QString::number(pack.at(0) >> 8, 2);
    qDebug() << QString::number(pack.at(0) & 0b0000000011111111, 2);

    if (0b0000'111111 < (pack.at(0) >> 8) ||
        0b0000'111111 < (pack.at(0) & 0b0000000011111111))
    {
        sendTo(false);
        return;
    }

    qDebug() << QString::number(pack.at(1) & 0b0000000011111111,       2);
    qDebug() << QString::number((pack.at(1) & 0b0000111100000000) >>  8, 2);
    qDebug() << QString::number((pack.at(1) & 0b1111000000000000) >> 12, 2);

    if (0b0011'111111 < (pack.at(1) >> 8) ||
        0b00'11 < ((pack.at(1) & 0b0000111100000000) >>  8) ||
        0b00'11 < ((pack.at(1) & 0b1111000000000000) >> 12))
    {
        sendTo(false);
        return;
    }

    qDebug() << QString::number(pack.at(2) >> 8, 2);
    qDebug() << QString::number(pack.at(2) & 0b0000000011111111, 2);

    if (0b0010'000010 < (pack.at(2) >> 8) || 0b0011'111111 < (pack.at(2) & 0b0000000011111111))
    {
        sendTo(false);
        return;
    }

    sendTo(true);
}
