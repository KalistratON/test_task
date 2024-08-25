#include "compass.h"

#include <QVector>

#include <algorithm>
#include <string>
#include <deque>


namespace {

double GetNumbers (std::string theNumberLine, int theCountNumber)
{
    if (theCountNumber < 1) {
        return 0.;
    }

    std::deque<int> aNumbers;
    auto anIt = std::find (theNumberLine.begin(), theNumberLine.end(), ',');
    while (anIt != theNumberLine.end()) {
        aNumbers.push_front (stoi (std::string (theNumberLine.begin(), anIt)));
        theNumberLine.erase (theNumberLine.begin(), std::next (anIt));

        anIt = std::find (theNumberLine.begin(), theNumberLine.end(), ',');
    }

    aNumbers.push_front (stoi (std::string (theNumberLine.begin(), anIt)));

    int aTargetCount = std::min (theCountNumber, static_cast <int> (aNumbers.size()));
    return std::accumulate (aNumbers.begin(), aNumbers.begin() + aTargetCount, 0) / static_cast<double> (aTargetCount);
}

}

Compass::Compass(QObject *parent)
    : QObject{parent}
{}

void Compass::calculateAverageSlot (const QString& theNumberLine, const QString& theN)
{
    double anAvarage;
    try {
        anAvarage = theNumberLine.isEmpty() || theN.isEmpty() ? 0. : GetNumbers (theNumberLine.toStdString(), theN.toInt());
    } catch (...) {
        anAvarage = 0.;
    }
    emit lineSumberReadySignal (anAvarage);
}
