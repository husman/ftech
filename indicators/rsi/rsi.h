//
// Created by Haleeq Usman on 1/10/16.
//

#ifndef FTECH_RSI_H
#define FTECH_RSI_H


#include "../indicator.h"

class RSI : public Indicator {
private:
    void buildData();

public:
    RSI(PriceMarketData const *marketData, std::string n = "");
};


#endif //FTECH_RSI_H
