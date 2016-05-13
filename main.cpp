#include <iostream>
#include "MarketData.h"
#include "MarketEvent.h"
#include "PriceMarketData.h"
#include "indicators/adl/adl.h"
#include "indicators/obv/obv.h"
#include "indicators/rsi/rsi.h"

int main() {
    MarketEvent mktEvent;
    MarketData mdADBE;
    PriceMarketData dailyPricesMD;

    mdADBE.seedDataFromCSV("data/historical-prices.csv", "ADBE");
    dailyPricesMD.seedDataFromCSV("data/daily-prices.csv", "ADBE-daily-prices");

//    dailyPricesMD.printData();
//    dailyPricesMD.plotClosing();
//    dailyPricesMD.plotVolume();

    auto pivots = dailyPricesMD.getPivots();
    std::cout
    << "pivots = <p="
    << std::get<0>(pivots) << ", r1="
    << std::get<1>(pivots) << ", r2="
    << std::get<2>(pivots) << ", s1="
    << std::get<3>(pivots) << ", s2="
    << std::get<4>(pivots)
    << ">\n";

    Obv obv(&dailyPricesMD);
    obv.plotOBV();

    ADL adl(&dailyPricesMD);
    adl.printData();
    adl.plotADL();

    RSI rsi(&dailyPricesMD);
    rsi.printData();
    rsi.plotRSI();

    return 0;
}