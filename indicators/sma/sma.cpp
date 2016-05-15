//
// Created by Haleeq Usman on 5/14/16.
//

#include "sma.h"

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

SMA::SMA(PriceMarketData const *marketData, unsigned int p, std::string n) : Indicator(marketData, n) {
    period = p;
    buildData();
}
