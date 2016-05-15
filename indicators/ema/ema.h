//
// Created by Haleeq Usman on 1/10/16.
//

#ifndef FTECH_EMA_H
#define FTECH_EMA_H


#include "../../global.h"
#include "../../PriceMarketData.h"
#include "../../MarketObserver.h"
#include <list>

class EMA : public MarketObserver {
private:
    std::vector<std::pair<double, double>> data;
    PriceMarketData const *mktData;
    unsigned int period;
    std::list<double> periodPrices;

    void buildData();

public:
    EMA(PriceMarketData const *marketData, unsigned int p);

    void addDataPoint(double price, size_t volume);

    void printData();

    void plotEMA();

    std::string getTickerSymbol();
};


#endif //FTECH_EMA_H
