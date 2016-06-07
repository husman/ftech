//
// Created by Haleeq Usman on 5/23/16.
//

#ifndef FTECH_MACKING_H
#define FTECH_MACKING_H

#include "../PriceMarketData.h"
#include "../indicators/adl/adl.h"
#include "../indicators/rsi/rsi.h"
#include "../indicators/macd/macd.h"
#include "../RateMarketData.h"

class Macking {
private:
    PriceMarketData *marketData;
    RateMarketData *rateData;
    ADL *adl;
    RSI *rsiBid;
    RSI *rsiAsk;
    MACD *macd;
    double profit = 0;
    std::string symbol;

    unsigned int wins, losses, i;
    double shares;
    double boughtPrice;

public:
    Macking(std::string ticker);
    void  runSimulation();

};

#endif //FTECH_MACKING_H
