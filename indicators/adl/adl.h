//
// Created by Haleeq Usman on 1/10/16.
//

#ifndef FTECH_ADL_H
#define FTECH_ADL_H


#include "../../global.h"
#include "../../PriceMarketData.h"
#include "../../MarketObserver.h"

class ADL : public MarketObserver {
private:
    std::vector<std::pair<double, double>> data;
    PriceMarketData const *mktData;

    void buildData();

public:
    ADL(PriceMarketData const *marketData);

    void addDataPoint(double price, size_t volume);

    void printData();

    void plotADL();

    std::string getTickerSymbol();
};


#endif //FTECH_ADL_H
