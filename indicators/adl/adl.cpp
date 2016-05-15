//
// Created by Haleeq Usman on 4/11/16.
//

#include "adl.h"

void ADL::buildData() {
    double adlValue = 0;
    double prevADL = 0;
    double mfm = 0;
    double mfv = 0;

    for (std::vector<std::tuple<double, double, double, double, size_t>>::const_iterator it = mktData->getDataBegin();
         it != mktData->getDataEnd(); ++it) {
        double highPrice = std::get<1>(*it);
        double lowPrice = std::get<2>(*it);
        double closePrice = std::get<3>(*it);
        size_t volume = std::get<4>(*it);

        if (highPrice == lowPrice) {
            continue;
        }

        mfm = ((closePrice - lowPrice) - (highPrice - closePrice)) / (highPrice - lowPrice);
        mfv = mfm * volume;
        adlValue = prevADL + mfv;

        prevADL = adlValue;
        data.push_back(std::make_pair(closePrice, adlValue));
    }
}

ADL::ADL(PriceMarketData const *marketData, std::string n) : Indicator(marketData, n) {
    buildData();
}
