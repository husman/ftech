#include <iostream>
#include "MarketData.h"
#include "MarketEvent.h"
#include "DailyPriceMarketData.h"

int main() {
    MarketEvent mktEvent;
    MarketData mdADBE;
    DailyPriceMarketData dailyPricesMD;

    mdADBE.seedDataFromCSV("data/HistoricalQuotes_ADBE_2-15-20162-51PMET.csv", "ADBE");
    dailyPricesMD.seedDataFromCSV("data/daily-prices.csv", "ADBE-daily-prices");

    dailyPricesMD.printData();
    dailyPricesMD.plotClosing();

    return 0;
}