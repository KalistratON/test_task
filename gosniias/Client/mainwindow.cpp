#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    widget(new QWidget(this)),
    connectionSetting(new QWidget()),
    msg(new QMessageBox(this))
{
    qDebug() << "init : Client";

    pack.reserve(qsizetype(4));
    pack.resize(qsizetype(4));

    setUi();
    initConnection();
}

MainWindow::~MainWindow()
{
}

void MainWindow::recvFrom()
{
    qDebug() << "recvFrom() : Client";

    QByteArray data;
    data.resize(socket->pendingDatagramSize());

    socket->readDatagram(data.data(), data.size());

    QDataStream datagram(&data, QIODevice::ReadOnly);
    bool flag;
    datagram >> flag;

    if (flag)
        msg->setText(QString("Correct data"));
    else
        msg->setText(QString("Incorrect data"));

    msg->show();
}

void MainWindow::sendTo()
{
    qDebug() << "sendTo : Client";

    QByteArray data;
    QDataStream datagram(&data, QIODevice::WriteOnly);

    //Take values fron lines
    packing();
    for (const auto& iter : pack)
        datagram << iter;

    socket->writeDatagram(data, host, port);
}

void MainWindow::packing()
{
    qDebug() << "packing : Client";

    //Make realisation

    pack[0] = static_cast<quint16>(lines.at(1)->text().toUShort()) +
                   (static_cast<quint16>(lines.at(2)->text().toInt() + 32) << 8) ;

    pack[1] = static_cast<quint16>(lines.at(3)->text().toUShort()) +
                   (static_cast<quint16>(lines.at(4)->text().toUShort()) << 8) +
                   (static_cast<quint16>(lines.at(5)->text().toUShort()) << 12);

    pack[2] = static_cast<quint16>(lines.at(6)->text().toDouble() * 10 + 127) +
                   (static_cast<quint16>(lines.at(7)->text().toUShort()) << 8);

    pack[3] = static_cast<quint16>(lines.at(8)->text().toUShort(nullptr, 2));

    qDebug() << QString::number(pack[0], 2) << '\t' << QString::number(pack[1], 2) << '\t' <<
        QString::number(pack[2], 2) << '\t' << QString::number(pack[3], 2);
}

void MainWindow::initConnection()
{
    qDebug() << "initConnection : Client";

    socket = new QUdpSocket(this);

    connect(socket, SIGNAL(readyRead()), this, SLOT(recvFrom()));
    connect(push, &QPushButton::clicked, this,  &MainWindow::sendTo);
    connect(connection, &QPushButton::clicked, this,  [=]() {
        this->connectionSetting->show();
        this->hide();
    });

    connect(connectionAccept, &QPushButton::clicked, this,  [=]() {
        this->connectionSetting->hide();
        this->show();

        host.setAddress(linesSetting.at(0)->text());
        port = linesSetting.at(1)->text().toInt();
    });
}

void MainWindow::setUi()
{
    msg->hide();

    labels.reserve(qsizetype(9));
    lines.reserve(qsizetype(9));

    QGridLayout* layout = new QGridLayout(this);
    QVector<QString> marks = { "X", "Y", "V", "M", "S", "A", "P", "R" };

    for (size_t i = 0; i < count; i++)
    {
        labels.push_back(new QLabel(this));
        lines.push_back(new QLineEdit(this));

        if (i)
            labels[i]->setText(marks.at(i - 1));
        else
            labels[i]->setText(QString("Mark"));

        layout->addWidget(labels.at(i), i + 1, 0);
        layout->addWidget(lines.at(i), i + 1, 1);
    }

    push = new QPushButton(this);
    push->setText(QString("Submit"));
    layout->addWidget(push, 10, 0, 1, 2);

    connection = new QPushButton(this);
    connection->setText(QString("Connection"));
    layout->addWidget(connection, 11, 0, 1, 2);

    connectionAccept = new QPushButton(this);
    connectionAccept->setText(QString("Accept"));

    lines.at(0)->setReadOnly(true);
    lines.at(1)->setValidator(new QRegularExpressionValidator(QRegularExpression("1?[0-9]?[0-9]|2[0-4][0-9]|25[0-5]"), this));
    lines.at(2)->setValidator(new QRegularExpressionValidator(QRegularExpression("-[1-2]?[0-9]|-3[0-2]|1?[0-9]?[0-9]|2[0-1][0-9]|22[0-3]"), this));
    lines.at(3)->setValidator(new QRegularExpressionValidator(QRegularExpression("1?[0-9]?[0-9]|2[0-4][0-9]|25[0-5]"), this));
    lines.at(4)->setValidator(new QRegularExpressionValidator(QRegularExpression("1[0-5]|[0-9]"), this));
    lines.at(5)->setValidator(new QRegularExpressionValidator(QRegularExpression("1[0-5]|[0-9]"), this));

    lines.at(6)->setValidator(new QRegularExpressionValidator(QRegularExpression("-?[0-9]\\.[0-9]|-?1[0-1]\\.[0-9]|-?12\\.[0-7]|12\\.8"), this));

    lines.at(7)->setValidator(new QRegularExpressionValidator(QRegularExpression("1?[0-9]?[0-9]|2[0-4][0-9]|25[0-5]"), this));
    lines.at(8)->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-1]{16}"), this));

    linesSetting.reserve(2);
    labelsSetting.reserve(2);
    QGridLayout* layoutSetting = new QGridLayout(this);
    for (int i = 0; i < 2; i++)
    {
        linesSetting.push_back(new QLineEdit(this));
        labelsSetting.push_back(new QLabel(this));

        layoutSetting->addWidget(labelsSetting.at(i), i, 0);
        layoutSetting->addWidget(linesSetting.at(i), i, 1);
    }

    linesSetting.at(0)->setValidator(new QRegularExpressionValidator(QRegularExpression("^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$"), this));

    linesSetting.at(0)->setText("127.0.0.1");
    linesSetting.at(1)->setText(QString::number(port));

    labelsSetting.at(0)->setText(QString("Host"));
    labelsSetting.at(1)->setText(QString("Port"));

    layoutSetting->addWidget(connectionAccept, 2, 0, 1, 2);
    connectionSetting->setLayout(layoutSetting);

    connectionSetting->hide();

    widget->setLayout(layout);
    setCentralWidget(widget);
}

