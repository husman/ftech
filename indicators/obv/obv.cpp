//
// Created by Haleeq Usman on 1/10/16.
//

#include "Obv.h"

void Obv::buildData() {
    double obvValue = 0;
    double prevPrice = 0;

    for (std::vector<std::tuple<double, double, double, double, size_t>>::const_iterator it = mktData->getDataBegin();
         it != mktData->getDataEnd(); ++it) {
        double price = std::get<3>(*it);
        size_t volume = std::get<4>(*it);

        if (price > prevPrice) {
            obvValue = obvValue + volume;
        } else if (price < prevPrice) {
            obvValue = obvValue - volume;
        }

        prevPrice = price;
        data.push_back(std::make_pair(price, obvValue));
    }
}

Obv::Obv(PriceMarketData const *marketData, std::string n) : Indicator(marketData, n) {
    buildData();
}
