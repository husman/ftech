//
// Created by Haleeq Usman on 1/10/16.
//

#ifndef FTECH_SMA_H
#define FTECH_SMA_H


#include "../indicator.h"
#include <list>

class SMA : public Indicator {
private:
    unsigned int period;
    std::list<double> periodPrices;
    void buildData();

public:
    SMA(PriceMarketData const *marketData, unsigned int p, std::string n = "");
};


#endif //FTECH_SMA_H
