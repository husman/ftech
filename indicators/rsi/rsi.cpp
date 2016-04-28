//
// Created by Haleeq Usman on 4/11/16.
//

#include "rsi.h"

void RSI::printData() {
    std::cout << "====== " << mktData->getTickerSymbol() << " RSI DATA ======" << std::endl;
    for (std::vector<std::pair<double, double>>::const_iterator it = data.begin(); it != data.end(); ++it) {
        std::cout << "<" << it->first << ", " << it->second << ">" << std::endl;
    }
    std::cout << "=============================" << std::endl;
}

void RSI::plotRSI() {
    Gnuplot gp;
    double minRSI = 0;
    double maxRSI = 0;
    size_t x = 0;
    std::vector<std::pair<size_t, double>> dataPoints;

    for (std::vector<std::pair<double, double>>::const_iterator it = data.begin(); it != data.end(); ++it) {
        double rsiValue = it->second;

        if (rsiValue < minRSI) {
            minRSI = rsiValue;
        }

        if (rsiValue > maxRSI) {
            maxRSI = rsiValue;
        }

        dataPoints.push_back(std::make_pair(x++, rsiValue));
    }

    gp << "set term x11 title 'FTech: " << mktData->getTickerSymbol() << " - RSI'\n";
    gp << "set xrange [0:" << (dataPoints.size() - 1) << "]\nset yrange [" << minRSI << ":" << maxRSI << "]\n";
    gp << "plot '-' w p ls 7 title 'RSI'\n";
    gp.send1d(dataPoints);
}

void RSI::buildData() {
    double runningGain = 0;
    double runningLoss = 0;
    double prevAvgGain = 0;
    double prevAvgLoss = 0;
    double prevPrice = 0;
    int counter = 0;
    int period = 14;
    bool isInitialRSI = true;


    for (std::vector<std::tuple<double, double, double, double, size_t>>::const_iterator it = mktData->getDataBegin();
         it != mktData->getDataEnd(); ++it) {
        double price = std::get<3>(*it);
        double delta = price - prevPrice;

        if (delta == 0) {
            continue;
        }

        if (counter > 0) {
            if (delta >= 0) {
                runningGain += delta;
            } else {
                runningLoss += delta * -1;
            }
        }

        ++counter;
        if (isInitialRSI) {
            prevPrice = price;

            if (counter < period != 0) {
                continue;
            }

            prevAvgGain = runningGain / period;
            prevAvgLoss = runningLoss / period;

            double initialRS = prevAvgGain / prevAvgLoss;
            double initialRSI = 100 - 100 / (1 + initialRS);
            data.push_back(std::make_pair(price, initialRSI));

            std::cout << "avg. Gain=" << prevAvgGain << " avg. Loss=" << prevAvgLoss
            << " RS=" << initialRS << " RSI=" << initialRSI << std::endl;

            isInitialRSI = false;
            continue;
        }

        if (delta > 0) {
            prevAvgGain = (prevAvgGain * (period - 1) + delta) / period;
            prevAvgLoss = (prevAvgLoss * (period - 1) + 0) / period;
        } else if(delta < 0) {
            prevAvgGain = (prevAvgGain * (period - 1) + 0) / period;
            prevAvgLoss = (prevAvgLoss * (period - 1) + (delta * -1)) / period;
        } else {
            prevAvgGain = (prevAvgGain * (period - 1) + 0) / period;
            prevAvgLoss = (prevAvgLoss * (period - 1) + 0) / period;
        }

        double rs = prevAvgGain / prevAvgLoss;
        double rsi = 100 - 100 / (1 + rs);
        data.push_back(std::make_pair(price, rsi));

        std::cout << "avg. Gain=" << prevAvgGain << " avg. Loss=" << prevAvgLoss
        << " RS=" << rs << " RSI=" << rsi << std::endl;
    }
}

RSI::RSI(PriceMarketData const *marketData) {
    mktData = marketData;
    buildData();
}

void RSI::addDataPoint(double price, size_t volume) {
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

std::string RSI::getTickerSymbol() {
    return mktData->getTickerSymbol();
}
