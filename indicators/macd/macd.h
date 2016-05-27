//
// Created by Haleeq Usman on 1/10/16.
//

#ifndef FTECH_MACD_H
#define FTECH_MACD_H


#include "../indicator.h"
#include "../ema/ema.h"

class MACD : public Indicator {
private:
    EMA *ema12, *ema26;
    void buildData();

public:
    EMA *ema9;
    MACD(PriceMarketData const *marketData, std::string n = "");
    void plot();
    void printData();
};


#endif //FTECH_MACD_H
