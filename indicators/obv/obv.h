//
// Created by Haleeq Usman on 1/10/16.
//

#ifndef FTECH_OBV_H
#define FTECH_OBV_H


#include "../../global.h"
#include "../../PriceMarketData.h"
#include "../../MarketObserver.h"

class Obv : public MarketObserver {
private:
    std::vector<std::pair<double, double>> data;
    PriceMarketData const *mktData;

    void buildData();

public:
    Obv(PriceMarketData const *marketData);

    void addDataPoint(double price, size_t volume);

    void printData();

    void plotOBV();

    std::string getTickerSymbol();
};


#endif //FTECH_OBV_H
