#include <iostream>
#include "MarketData.h"
#include "MarketEvent.h"
#include "indicators/obv/Obv.h"

int main() {
    MarketEvent mktEvent;
    MarketData mdADBE;
    MarketData mdGOOG;

    mdADBE.seedDataFromCSV("data/HistoricalQuotes_ADBE_2-15-20162-51PMET.csv", "ADBE");
    mdGOOG.seedDataFromCSV("data/HistoricalQuotes_ADBE_2-15-20162-51PMET.csv", "GOOG");

    Obv obvADBE(&mdADBE);
    Obv obvGOOG(&mdGOOG);

    mktEvent.subscribe(&obvADBE);
    mktEvent.subscribe(&obvGOOG);

    mktEvent.trigger(MarketEvent::EventType::ADD_DATA_POINT, "ADBE", 77.77, 999777);

    return 0;
}