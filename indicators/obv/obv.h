//
// Created by Haleeq Usman on 1/10/16.
//

#ifndef FTECH_OBV_H
#define FTECH_OBV_H

#include <boost/tuple/tuple.hpp>
#include <vector>
#include <cmath>
#include <stdio.h>
#include <iostream>

#include "../../gnuplot/gnuplot-iostream.h"
#include "../constants.h"
#include "../MarketData.h"

class Obv {
private:
    double *data;
    size_t dataLen;
    MarketData const *mktData;

    void buildData();

public:
    Obv(MarketData const *marketData);

    void printData();

    void reSync();

    void plotOBV();
};


#endif //FTECH_OBV_H
