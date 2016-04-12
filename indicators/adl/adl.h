//
// Created by Haleeq Usman on 1/10/16.
//

#ifndef FTECH_OBV_H
#define FTECH_OBV_H


#include "../../global.h"
#include "../../MarketData.h"
#include "../../MarketObserver.h"

class ADL : public MarketObserver {
private:
    std::vector<std::pair<double, double>> data;
    MarketData const *mktData;

    void buildData();

public:
    ADL(MarketData const *marketData);

    void addDataPoint(double price, size_t volume);

    void printData();

    void plotADL();

    std::string getTickerSymbol();
};


#endif //FTECH_OBV_H
