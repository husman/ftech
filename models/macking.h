//
// Created by Haleeq Usman on 5/23/16.
//

#ifndef FTECH_MACKING_H
#define FTECH_MACKING_H

#include "../PriceMarketData.h"
#include "../indicators/adl/adl.h"
#include "../indicators/rsi/rsi.h"
#include "../indicators/macd/macd.h"

class Macking {
private:
    PriceMarketData *marketData;
    ADL *adl;
    RSI *rsi;
    MACD *macd;
    double profit = 0;

public:
    Macking(std::string ticker);
    void runSimulation();

};

#endif //FTECH_MACKING_H
