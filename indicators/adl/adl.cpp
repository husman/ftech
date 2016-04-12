//
// Created by Haleeq Usman on 4/11/16.
//

#include "adl.h"

void ADL::printData() {
    std::cout << "====== " << mktData->getTickerSymbol() << " ADL DATA ======" << std::endl;
    for (std::vector<std::pair<double, double>>::const_iterator it = data.begin(); it != data.end(); ++it) {
        std::cout << "<" << it->first << ", " << it->second << ">" << std::endl;
    }
    std::cout << "=============================" << std::endl;
}

void ADL::plotADL() {
    Gnuplot gp;
    double minADL = 0;
    double maxADL = 0;
    size_t x = 0;
    std::vector<std::pair<size_t, double>> dataPoints;

    for (std::vector<std::pair<double, double>>::const_iterator it = data.begin(); it != data.end(); ++it) {
        double adlValue = it->second;

        if (adlValue < minADL) {
            minADL = adlValue;
        }

        if (adlValue > maxADL) {
            maxADL = adlValue;
        }

        dataPoints.push_back(std::make_pair(x++, adlValue));
    }

    gp << "set term x11 title 'FTech: " << mktData->getTickerSymbol() << " - ADL'\n";
    gp << "set xrange [0:" << (dataPoints.size() - 1) << "]\nset yrange [" << minADL << ":" << maxADL << "]\n";
    gp << "plot '-' with lines title 'ADL'\n";
    gp.send1d(dataPoints);
}

void ADL::buildData() {
    double adlValue = 0;
    double prevADL = 0;
    double minPrice = 0;
    double maxPrice = 0;
    double mfm = 0;
    double mfv = 0;

    for (std::vector<std::pair<double, size_t>>::const_iterator it = mktData->getDataBegin();
         it != mktData->getDataEnd(); ++it) {
        double price = it->first;
        size_t volume = it->second;

        if (price > maxPrice) {
            maxPrice = price;
        } else if (price < minPrice) {
            minPrice = price;
        }

        mfm = ((price - minPrice) - (maxPrice - price)) / (maxPrice - minPrice);
        mfv = mfm * volume;
        adlValue = prevADL + mfv;

        prevADL = adlValue;
        data.push_back(std::make_pair(price, adlValue));
    }
}

ADL::ADL(MarketData const *marketData) {
    mktData = marketData;
    buildData();
}

void ADL::addDataPoint(double price, size_t volume) {
    std::pair<double, double> lastObv = data.back();
    double lastPrice = lastObv.first;
    double adlValue = lastObv.second;

    if (price > lastPrice) {
        adlValue = adlValue + volume;
    } else if (price < lastPrice) {
        adlValue = adlValue - volume;
    }

    data.push_back(std::make_pair(price, adlValue));
}

std::string ADL::getTickerSymbol() {
    return mktData->getTickerSymbol();
}
