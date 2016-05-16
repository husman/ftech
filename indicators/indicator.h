//
// Created by Haleeq Usman on 5/15/16.
//

#ifndef FTECH_INDICATOR_H
#define FTECH_INDICATOR_H

#include "../global.h"
#include "../PriceMarketData.h"
#include "../MarketObserver.h"

#define __INDICATOR_DATA_VECTOR std::vector<std::pair<double, double>>

class Indicator : public MarketObserver {
protected:
    __INDICATOR_DATA_VECTOR data;
    PriceMarketData const *mktData;
    std::string name;

public:
    typedef __INDICATOR_DATA_VECTOR IndicatorDataVector;
    Indicator(PriceMarketData const *marketData, std::string n = "Indicator");
    Indicator(std::string n = "Indicator");

    void addDataPoint(double price, size_t volume);

    virtual void printData();

    virtual void plot();

    std::string getTickerSymbol();

    IndicatorDataVector::const_iterator getDataBegin() const;

    IndicatorDataVector::const_iterator getDataEnd() const;

    size_t getSize();
};


#endif //FTECH_INDICATOR_H
