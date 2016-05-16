//
// Created by Haleeq Usman on 1/10/16.
//

#ifndef FTECH_EMA_H
#define FTECH_EMA_H


#include "../indicator.h"
#include <list>

class EMA : public Indicator {
private:
    unsigned int period;
    double ema, sma, smaCount;
    std::list<double> periodPrices;
    void buildData();

public:
    EMA(PriceMarketData const *marketData, unsigned int p, std::string n = "");
    EMA(unsigned int p, std::string n = "");
    void addPrice(double price);
};


#endif //FTECH_EMA_H
