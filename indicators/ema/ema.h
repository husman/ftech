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
    std::list<double> periodPrices;
    void buildData();

public:
    EMA(PriceMarketData const *marketData, unsigned int p, std::string n = "");
};


#endif //FTECH_EMA_H
