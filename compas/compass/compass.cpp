#include "compass.h"

#include <QVector>

#include <algorithm>
#include <string>


namespace {

double GetNumbers (std::string theNumberLine)
{
    int aSumNumber = 0;
    int aCountNumber = 1;

    auto anIt = std::find (theNumberLine.begin(), theNumberLine.end(), ',');
    while (anIt != theNumberLine.end()) {
        ++aCountNumber;

        aSumNumber +=  stoi (std::string (theNumberLine.begin(), anIt));
        theNumberLine.erase (theNumberLine.begin(), std::next (anIt));

        anIt = std::find (theNumberLine.begin(), theNumberLine.end(), ',');
    }

    aSumNumber +=  stoi (std::string (theNumberLine.begin(), anIt));
    return static_cast<double> (aSumNumber) / aCountNumber;
}

}

Compass::Compass(QObject *parent)
    : QObject{parent}
{}

void Compass::calculateAverageSlot (const QString& theNumberLine)
{
    emit lineSumberReadySignal (theNumberLine.isEmpty() ? 0. : GetNumbers (theNumberLine.toStdString()));
}
