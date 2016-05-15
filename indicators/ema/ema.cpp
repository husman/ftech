//
// Created by Haleeq Usman on 5/15/16.
//

#include "ema.h"

EMA::EMA(PriceMarketData const *marketData, unsigned int p, std::string n) : Indicator(marketData, n) {
    period = p;
    buildData();
}

void EMA::buildData() {
    double count = 0;
    double sma = 0;
    double ema = 0;

    for (std::vector<std::tuple<double, double, double, double, size_t>>::const_iterator it = mktData->getDataBegin();
         it != mktData->getDataEnd(); ++it) {
        double price = std::get<3>(*it);

        if (count < period) {
            ++count;
            sma += price;
            continue;
        }

        if (count == period) {
            ema = sma / period;
            ++count;
        }

        double mul = 2 / ((double)period + 1);
        ema = (price - ema) * mul + ema;
        data.push_back(std::make_pair(price, ema));
    }
}
