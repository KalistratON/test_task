#include "mainwindow.h"

#include <QApplication>
#include <QIODevice>
#include <QFile>
#include <QTextStream>

QString styleString(const QString& path)
{
    QFile file(path);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        return file.readAll();
    }
    return QString("");
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QString css = styleString(":/style/style.css");
    if (!css.isEmpty()) a.setStyleSheet(css);
    w.show();
    return a.exec();
}
