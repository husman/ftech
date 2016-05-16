//
// Created by Haleeq Usman on 5/15/16.
//

#include "macd.h"

MACD::MACD(PriceMarketData const *marketData, std::string n) : Indicator(marketData, n) {
    ema9 = new EMA(9, "EMA-9 Signal Line");
    ema12 = new EMA(marketData, 12);
    ema26 = new EMA(marketData, 26);
    buildData();
}

void MACD::buildData() {
    PriceMarketData::PriceMarketDataVector::const_iterator itMktData = mktData->getDataBegin() + 26;
    Indicator::IndicatorDataVector::const_iterator itEMA12 = ema12->getDataBegin() + 14;
    Indicator::IndicatorDataVector::const_iterator itEMA26 = ema26->getDataBegin();

    while (itMktData != mktData->getDataEnd()) {
        double price = std::get<3>(*itMktData);
        double ema12Value = itEMA12->second;
        double ema26Value = itEMA26->second;
        double macdLineValue = ema12Value - ema26Value;

        data.push_back(std::make_pair(price, macdLineValue));
        ema9->addPrice(macdLineValue);
        ++itMktData;
        ++itEMA12;
        ++itEMA26;
    }
}

void MACD::plot() {
    Gnuplot gp;
    double minSMA = 0;
    double maxSMA = 0;
    size_t x = 0;
    std::vector<std::pair<size_t, double>> macdDataPoints;
    std::vector<std::pair<size_t, double>> signalDataPoints;

    for (Indicator::IndicatorDataVector::const_iterator it = data.begin(); it != data.end(); ++it) {
        double smaValue = it->second;

        if (smaValue < minSMA || minSMA == 0) {
            minSMA = smaValue;
        }

        if (smaValue > maxSMA) {
            maxSMA = smaValue;
        }

        macdDataPoints.push_back(std::make_pair(x++, smaValue));
    }

    x = 9;
    for (Indicator::IndicatorDataVector::const_iterator it = ema9->getDataBegin(); it != ema9->getDataEnd(); ++it) {
        double smaValue = it->second;

        if (smaValue < minSMA || minSMA == 0) {
            minSMA = smaValue;
        }

        if (smaValue > maxSMA) {
            maxSMA = smaValue;
        }

        signalDataPoints.push_back(std::make_pair(x++, smaValue));
    }

    gp << "set term x11 title 'FTech: " << mktData->getTickerSymbol() << " - " << name << "'\n";
    gp << "set xrange [0:" << (macdDataPoints.size() - 1) << "]\nset yrange [" << minSMA << ":" << maxSMA << "]\n";
    gp << "plot '-' w l ls 6 title 'MACD', ";
    gp << "'-' w l ls 5 title 'Signal'\n";
    gp.send1d(macdDataPoints);
    gp.send1d(signalDataPoints);
}

void MACD::printData() {
    std::cout << "====== " << mktData->getTickerSymbol() << " " << name << " Line DATA ======" << std::endl;
    for (Indicator::IndicatorDataVector::const_iterator it = data.begin(); it != data.end(); ++it) {
        std::cout << "<" << it->first << ", " << it->second << ">" << std::endl;
    }
    std::cout << "=============================" << std::endl;

    std::cout << "====== " << mktData->getTickerSymbol() << " " << name << " Signal DATA ======" << std::endl;
    for (Indicator::IndicatorDataVector::const_iterator it = ema9->getDataBegin(); it != ema9->getDataEnd(); ++it) {
        std::cout << "<" << it->first << ", " << it->second << ">" << std::endl;
    }
    std::cout << "=============================" << std::endl;
}
