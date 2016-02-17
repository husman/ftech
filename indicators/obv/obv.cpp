//
// Created by Haleeq Usman on 1/10/16.
//

#include "Obv.h"

void Obv::printData() {
    std::cout << "====== " << mktData->getTickerSymbol() << " OBV DATA ======" << std::endl;
    for (size_t i = 0; i < dataLen; ++i) {
        std::cout << "<" << i << ", " << data[i] << ">" << std::endl;
    }
    std::cout << "=============================" << std::endl;
}

void Obv::plotOBV() {
    Gnuplot gp;
    double minObv = 0;
    double maxObv = 0;
    std::vector<std::pair<double, double>> dataPoints;

    for (size_t x = 0; x < dataLen; ++x) {
        double obvValue = data[x];

        if (obvValue < minObv) {
            minObv = obvValue;
        }

        if (obvValue > maxObv) {
            maxObv = obvValue;
        }

        dataPoints.push_back(std::make_pair(x, obvValue));
    }

    gp << "set term x11 title 'FTech: " << mktData->getTickerSymbol() << " - OBV'\n";
    gp << "set xrange [0:" << (mktData->getPeriod() - 1) << "]\nset yrange [" << minObv << ":" << maxObv << "]\n";
    gp << "plot '-' with lines title 'OBV'\n";
    gp.send1d(dataPoints);
}

void Obv::buildData() {
    size_t column = 0;
    double minObv = 0;
    double maxObv = 0;
    double prevClosePrice = 0;
    double obvValue = 0;

    dataLen = mktData->getSize();

    if (data) {
        delete data;
    }

    data = new double[dataLen];

    for (std::vector<std::pair<double, size_t>>::const_iterator it = mktData->getDataBegin();
         it != mktData->getDataEnd(); ++it) {
        double closePrice = it->first;
        size_t volume = it->second;

        if (closePrice > prevClosePrice) {
            obvValue = obvValue + volume;
        } else if (closePrice < prevClosePrice) {
            obvValue = obvValue - volume;
        }

        if (obvValue < minObv) {
            minObv = obvValue;
        }

        if (obvValue > maxObv) {
            maxObv = obvValue;
        }

        prevClosePrice = closePrice;
        data[column++] = obvValue;
    }
}

Obv::Obv(MarketData const *marketData) {
    mktData = marketData;
    data = NULL;
    dataLen = 0;

    buildData();
}

void Obv::reSync() {
    buildData();
}
