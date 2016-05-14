//
// Created by Haleeq Usman on 5/14/16.
//

#include "sma.h"

void SMA::printData() {
    std::cout << "====== " << mktData->getTickerSymbol() << " SMA (period = " << period << ") DATA ======" << std::endl;
    for (std::vector<std::pair<double, double>>::const_iterator it = data.begin(); it != data.end(); ++it) {
        std::cout << "<" << it->first << ", " << it->second << ">" << std::endl;
    }
    std::cout << "=============================" << std::endl;
}

void SMA::plotSMA() {
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

    gp << "set term x11 title 'FTech: " << mktData->getTickerSymbol() << " - SMA (period = " << period << ")'\n";
    gp << "set xrange [0:" << (dataPoints.size() - 1) << "]\nset yrange [" << minSMA << ":" << maxSMA << "]\n";
    gp << "plot '-'  w l ls 7 title 'ADL'\n";
    gp.send1d(dataPoints);
}

void SMA::buildData() {
    for (std::vector<std::tuple<double, double, double, double, size_t>>::const_iterator it = mktData->getDataBegin();
         it != mktData->getDataEnd(); ++it) {
        double price = std::get<3>(*it);

        if (periodPrices.size() == period) {
            periodPrices.pop_front();
        }

        periodPrices.push_back(price);

        if (periodPrices.size() == period) {
            double average = 0;
            for (std::list<double>::iterator i = periodPrices.begin(); i != periodPrices.end(); ++i) {
                average += *i;
            }

            data.push_back(std::make_pair(price, average / (double)period));
        }
    }
}

SMA::SMA(PriceMarketData const *marketData, unsigned int p) {
    mktData = marketData;
    period = p;
    buildData();
}

void SMA::addDataPoint(double price, size_t volume) {
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

std::string SMA::getTickerSymbol() {
    return mktData->getTickerSymbol();
}
