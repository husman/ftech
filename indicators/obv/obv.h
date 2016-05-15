//
// Created by Haleeq Usman on 1/10/16.
//

#ifndef FTECH_OBV_H
#define FTECH_OBV_H


#include "../indicator.h"

class Obv : public Indicator {
private:
    void buildData();

public:
    Obv(PriceMarketData const *marketData, std::string n = "");
};


#endif //FTECH_OBV_H
