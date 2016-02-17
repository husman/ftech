//
// Created by Haleeq Usman on 2/17/16.
//

#ifndef FTECH_MARKETEVENT_H
#define FTECH_MARKETEVENT_H

#include "MarketObserver.h"

class MarketEvent {
private:
    std::vector<MarketObserver *> observers;

public:
    enum EventType {
        ADD_DATA_POINT = 0x0,
    };

    void subscribe(MarketObserver *observer);

    void unSubscribe(MarketObserver *observer);

    void trigger(EventType eventType, std::string tickerSymbol, double price, size_t volume);

    void notifyAddDataPoint(std::string tickerSymbol, double price, size_t volume);

};

#endif //FTECH_MARKETEVENT_H
