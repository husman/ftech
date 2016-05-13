//
// Created by Haleeq Usman on 1/10/16.
//

#ifndef FTECH_RSI_H
#define FTECH_RSI_H


#include "../../global.h"
#include "../../PriceMarketData.h"
#include "../../MarketObserver.h"

class RSI : public MarketObserver {
private:
    std::vector<std::pair<double, double>> data;
    PriceMarketData const *mktData;

    void buildData();

public:
    RSI(PriceMarketData const *marketData);

    void addDataPoint(double price, size_t volume);

    void printData();

    void plotRSI();

    std::string getTickerSymbol();
};


#endif //FTECH_RSI_H
