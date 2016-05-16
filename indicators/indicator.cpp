//
// Created by Haleeq Usman on 5/15/16.
//

#include "indicator.h"

void Indicator::printData() {
    std::cout << "====== " << mktData->getTickerSymbol() << " " << name << " DATA ======" << std::endl;
    for (std::vector<std::pair<double, double>>::const_iterator it = data.begin(); it != data.end(); ++it) {
        std::cout << "<" << it->first << ", " << it->second << ">" << std::endl;
    }
    std::cout << "=============================" << std::endl;
}

void Indicator::plot() {
    Gnuplot gp;
    double minSMA = 0;
    double maxSMA = 0;
    size_t x = 0;
    std::vector<std::pair<size_t, double>> dataPoints;

    for (std::vector<std::pair<double, double>>::const_iterator it = data.begin(); it != data.end(); ++it) {
        double smaValue = it->second;

        if (smaValue < minSMA || minSMA == 0) {
            minSMA = smaValue;
        }

        if (smaValue > maxSMA) {
            maxSMA = smaValue;
        }

        dataPoints.push_back(std::make_pair(x++, smaValue));
    }

    gp << "set term x11 title 'FTech: " << mktData->getTickerSymbol() << " - " << name << "'\n";
    gp << "set xrange [0:" << (dataPoints.size() - 1) << "]\nset yrange [" << minSMA << ":" << maxSMA << "]\n";
    gp << "plot '-'  w l ls 7 title 'Indicator'\n";
    gp.send1d(dataPoints);
}

Indicator::Indicator(PriceMarketData const *marketData, std::string n) {
    mktData = marketData;
    name = n;
}

Indicator::Indicator(std::string n) {
    mktData = new PriceMarketData();
    name = n;
}

void Indicator::addDataPoint(double price, size_t volume) {
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

std::string Indicator::getTickerSymbol() {
    return mktData->getTickerSymbol();
}

Indicator::IndicatorDataVector::const_iterator Indicator::getDataBegin() const {
    return data.begin();
}

Indicator::IndicatorDataVector::const_iterator Indicator::getDataEnd() const {
    return data.end();
}

size_t Indicator::getSize() {
    data.size();
}
