#include <iostream>
#include "MarketData.h"
#include "MarketEvent.h"
#include "indicators/obv/Obv.h"

int main() {
    MarketEvent mktEvent;
    MarketData mdADBE;
    MarketData mdDailyPrices;

    mdADBE.seedDataFromCSV("data/HistoricalQuotes_ADBE_2-15-20162-51PMET.csv", "ADBE");
    mdDailyPrices.seedDataFromCSV("data/HistoricalQuotes_ADBE_2-15-20162-51PMET.csv", "ADBE-daily-prices");

    Obv obvADBE(&mdADBE);
    mktEvent.subscribe(&obvADBE);

    obvADBE.plotOBV();

    mktEvent.trigger(MarketEvent::EventType::ADD_DATA_POINT, "ADBE", 77.77, 999777);

    return 0;
}