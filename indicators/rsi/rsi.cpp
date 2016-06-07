//
// Created by Haleeq Usman on 4/11/16.
//

#include "rsi.h"

RSI::RSI(std::string n) : Indicator(n) {
    lastPrice = 0;
    nbPrices = 0;
    prevAvgGain = 0;
    prevAvgLoss = 0;
}

RSI::RSI(PriceMarketData const *marketData, std::string n) : Indicator(marketData, n) {
    lastPrice = 0;
    nbPrices = 0;
    prevAvgGain = 0;
    prevAvgLoss = 0;
    buildData();
}

RSI::RSI(RateMarketData const *marketData, std::string n, bool bid) {
    lastPrice = 0;
    nbPrices = 0;
    prevAvgGain = 0;
    prevAvgLoss = 0;
    rateData = marketData;
    isBid = bid;
    buildRateData();
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

//        if (delta == 0) {
//            continue;
//        }

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

            if (counter < period) {
                continue;
            }

            prevAvgGain = runningGain / period;
            prevAvgLoss = runningLoss / period;

            double initialRS = prevAvgGain / prevAvgLoss;
            double initialRSI = 100 - 100 / (1 + initialRS);
            data.push_back(std::make_pair(price, initialRSI));

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
        prevPrice = price;
    }
}

void RSI::buildRateData() {
    double runningGain = 0;
    double runningLoss = 0;
    double prevAvgGain = 0;
    double prevAvgLoss = 0;
    double prevPrice = 0;
    int counter = 0;
    int period = 14;
    bool isInitialRSI = true;


    for (RateMarketData::MarketDataVector::const_iterator it = rateData->getDataBegin();
         it != rateData->getDataEnd(); ++it) {
        double price = isBid ? it->first : it->second;
        double delta = price - prevPrice;

//        if (delta == 0) {
//            continue;
//        }

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

            if (counter < period) {
                continue;
            }

            prevAvgGain = runningGain / period;
            prevAvgLoss = runningLoss / period;

            double initialRS = prevAvgGain / prevAvgLoss;
            double initialRSI = 100 - 100 / (1 + initialRS);
            data.push_back(std::make_pair(price, initialRSI));

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
        prevPrice = price;
    }
}

void RSI::addRate(double price) {
    int period = 14;
    double delta = price - lastPrice;

    if (nbPrices < 14) {
        ++nbPrices;

        if(nbPrices == 0) {
            lastPrice = price;
            return;
        }

        if(delta > 0) {
            prevAvgGain += price;
        } else {
            prevAvgLoss += price * -1;
        }

        lastPrice = price;
        return;
    }

    if(delta > 0) {
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
    lastPrice = price;
}
