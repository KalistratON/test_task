#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QWidget>
#include <QtCore>
#include <QTextEdit>
#include <QMenuBar>
#include <QGridLayout>
#include <QPushButton>

#include <QUdpSocket>
#include <QDataStream>
#include <QByteArray>
#include <QVector>
#include <QMessageBox>

#include <QLabel>
#include <QLineEdit>

#include <QValidator>
#include <QRegularExpressionValidator>
#include <QRegularExpression>

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:

    QWidget* widget = nullptr;
    QWidget* connectionSetting = nullptr;
    QMessageBox *msg = nullptr;

    QVector<QLabel*> labels;
    QVector<QLineEdit*> lines;
    QPushButton* push;
    QPushButton* connection;
    QPushButton* connectionAccept;

    QVector<QLabel*> labelsSetting;
    QVector<QLineEdit*> linesSetting;

    QUdpSocket* socket = nullptr;
    QVector<quint16> pack;

    const size_t count = 9;

    QHostAddress host = QHostAddress::LocalHost;
    quint16 port = 1234;

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void recvFrom();
    void sendTo();
    //void setSetting();

private:

    void setUi();
    void initConnection();
    void packing();
};
#endif // MAINWINDOW_H
