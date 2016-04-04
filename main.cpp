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

    auto pivots = dailyPricesMD.getPivots();
    std::cout
    << "pivots = <p="
    << std::get<0>(pivots) << ", r1="
    << std::get<1>(pivots) << ", r2="
    << std::get<2>(pivots) << ", s1="
    << std::get<3>(pivots) << ", s2="
    << std::get<4>(pivots)
    << ">\n";

    return 0;
}