#ifndef COMPASS_H
#define COMPASS_H

#include <QObject>

#include <string>


class Compass : public QObject
{
    Q_OBJECT
public:
    explicit Compass (QObject *parent = nullptr);

    Q_INVOKABLE void calculateAverageSlot (const QString& theNumberLine);

signals:
    void lineSumberReadySignal (double theAvarage);

};

#endif // COMPASS_H
