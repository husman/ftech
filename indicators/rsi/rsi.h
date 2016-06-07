//
// Created by Haleeq Usman on 1/10/16.
//

#ifndef FTECH_RSI_H
#define FTECH_RSI_H


#include "../indicator.h"
#include "../../RateMarketData.h"

class RSI : public Indicator {
private:
    RateMarketData const *rateData;
    void buildData();
    void buildRateData();
    bool isBid;
    double lastPrice;
    size_t nbPrices;
    double prevAvgGain;
    double prevAvgLoss;

public:
    RSI(std::string n);
    RSI(PriceMarketData const *marketData, std::string n = "");
    RSI(RateMarketData const *marketData, std::string n = "", bool bid = false);
    void addRate(double askPrice);
};


#endif //FTECH_RSI_H
