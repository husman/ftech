//
// Created by Haleeq Usman on 2/17/16.
//

#ifndef FTECH_MARKETOBSERVER_H
#define FTECH_MARKETOBSERVER_H

#include "global.h"

class MarketObserver {
public:
    virtual void addDataPoint(double price, size_t volume) = 0;

    virtual std::string getTickerSymbol() = 0;
};


#endif //FTECH_MARKETOBSERVER_H
