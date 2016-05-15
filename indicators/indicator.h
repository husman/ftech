//
// Created by Haleeq Usman on 5/15/16.
//

#ifndef FTECH_INDICATOR_H
#define FTECH_INDICATOR_H

#include "../global.h"
#include "../PriceMarketData.h"
#include "../MarketObserver.h"


class Indicator : public MarketObserver {
protected:
    std::vector<std::pair<double, double>> data;
    PriceMarketData const *mktData;
    std::string name;

public:
    Indicator(PriceMarketData const *marketData, std::string n = "");

    void addDataPoint(double price, size_t volume);

    void printData();

    void plot();

    std::string getTickerSymbol();
};


#endif //FTECH_INDICATOR_H
