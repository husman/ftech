//
// Created by Haleeq Usman on 2/17/16.
//

#include "MarketEvent.h"

void MarketEvent::subscribe(MarketObserver *observer) {
    observers.push_back(observer);
}

void MarketEvent::unSubscribe(MarketObserver *observer) {
    for (std::vector<MarketObserver *>::const_iterator it = observers.begin(); it != observers.end(); ++it) {
        if (*it == observer) {
            observers.erase(it);
        }
    }
}

void MarketEvent::notifyAddDataPoint(std::string tickerSymbol, double price, size_t volume) {
    for (std::vector<MarketObserver *>::const_iterator it = observers.begin(); it != observers.end(); ++it) {
        if ((*it)->getTickerSymbol() == tickerSymbol) {
            (*it)->addDataPoint(price, volume);
        }
    }
}

void MarketEvent::trigger(MarketEvent::EventType eventType, std::string tickerSymbol, double price, size_t volume) {
    switch (eventType) {
        case EventType::ADD_DATA_POINT:
            notifyAddDataPoint(tickerSymbol, price, volume);
            break;
    }
}
