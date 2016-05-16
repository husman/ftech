//
// Created by Haleeq Usman on 5/15/16.
//

#include "ema.h"

EMA::EMA(PriceMarketData const *marketData, unsigned int p, std::string n) : Indicator(marketData, n) {
    period = p;
    ema = 0;
    sma = 0;
    smaCount = 0;
    buildData();
}

EMA::EMA(unsigned int p, std::string n) : Indicator(n) {
    period = p;
    ema = 0;
    sma = 0;
    smaCount = 0;
}

void EMA::buildData() {
    for (std::vector<std::tuple<double, double, double, double, size_t>>::const_iterator it = mktData->getDataBegin();
         it != mktData->getDataEnd(); ++it) {
        double price = std::get<3>(*it);

        if (smaCount < period) {
            ++smaCount;
            sma += price;
            continue;
        }

        if (smaCount == period) {
            ema = sma / period;
            ++smaCount;
        }

        double mul = 2 / ((double) period + 1);
        ema = (price - ema) * mul + ema;
        data.push_back(std::make_pair(price, ema));
    }
}

void EMA::addPrice(double price) {
    if (smaCount < period) {
        ++smaCount;
        sma += price;
        return;
    }

    if (smaCount == period) {
        ema = sma / period;
        ++smaCount;
    }

    double mul = 2 / ((double) period + 1);
    ema = (price - ema) * mul + ema;
    data.push_back(std::make_pair(price, ema));
}
