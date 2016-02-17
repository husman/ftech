//
// Created by Haleeq Usman on 1/10/16.
//

#include "Obv.h"

void Obv::printData() {
    std::cout << "====== " << mktData->getTickerSymbol() << " OBV DATA ======" << std::endl;
    for (std::vector<std::pair<double, double>>::const_iterator it = data.begin(); it != data.end(); ++it) {
        std::cout << "<" << it->first << ", " << it->second << ">" << std::endl;
    }
    std::cout << "=============================" << std::endl;
}

void Obv::plotOBV() {
    Gnuplot gp;
    double minObv = 0;
    double maxObv = 0;
    size_t x = 0;
    std::vector<std::pair<size_t, double>> dataPoints;

    for (std::vector<std::pair<double, double>>::const_iterator it = data.begin(); it != data.end(); ++it) {
        double obvValue = it->second;

        if (obvValue < minObv) {
            minObv = obvValue;
        }

        if (obvValue > maxObv) {
            maxObv = obvValue;
        }

        dataPoints.push_back(std::make_pair(x++, obvValue));
    }

    gp << "set term x11 title 'FTech: " << mktData->getTickerSymbol() << " - OBV'\n";
    gp << "set xrange [0:" << (dataPoints.size() - 1) << "]\nset yrange [" << minObv << ":" << maxObv << "]\n";
    gp << "plot '-' with lines title 'OBV'\n";
    gp.send1d(dataPoints);
}

void Obv::buildData() {
    double obvValue = 0;
    double prevPrice = 0;

    for (std::vector<std::pair<double, size_t>>::const_iterator it = mktData->getDataBegin();
         it != mktData->getDataEnd(); ++it) {
        double price = it->first;
        size_t volume = it->second;

        if (price > prevPrice) {
            obvValue = obvValue + volume;
        } else if (price < prevPrice) {
            obvValue = obvValue - volume;
        }

        prevPrice = price;
        data.push_back(std::make_pair(price, obvValue));
    }
}

Obv::Obv(MarketData const *marketData) {
    mktData = marketData;
    buildData();
}

void Obv::addDataPoint(double price, size_t volume) {
    std::pair<double, double> lastObv = data.back();
    double lastPrice = lastObv.first;
    double obvValue = lastObv.second;

    if (price > lastPrice) {
        obvValue = obvValue + volume;
    } else if (price < lastPrice) {
        obvValue = obvValue - volume;
    }

    data.push_back(std::make_pair(price, obvValue));
}

std::string Obv::getTickerSymbol() {
    return mktData->getTickerSymbol();
}
