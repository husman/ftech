//
// Created by Haleeq Usman on 1/10/16.
//

#ifndef FTECH_ADL_H
#define FTECH_ADL_H


#include "../indicator.h"

class ADL : public Indicator {
private:
    void buildData();

public:
    ADL(PriceMarketData const *marketData, std::string n = "");
};


#endif //FTECH_ADL_H
