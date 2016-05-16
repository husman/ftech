#include <iostream>
#include "MarketEvent.h"
#include "PriceMarketData.h"
#include "indicators/sma/sma.h"
#include "indicators/ema/ema.h"
#include "indicators/rsi/rsi.h"
#include "indicators/adl/adl.h"
#include "indicators/obv/obv.h"
#include "indicators/macd/macd.h"

int main() {
    MarketEvent mktEvent;
    PriceMarketData dailyPricesMD;

    dailyPricesMD.seedDataFromCSV("data/table.goog-dec-1-2015-may-15-2016.csv", "table.goog-dec-1-2015-may-15-2016");

//    dailyPricesMD.printData();
    dailyPricesMD.plotClosing();
//    dailyPricesMD.plotVolume();

    auto pivots = dailyPricesMD.getPivots();
//    std::cout
//    << "pivots = <p="
//    << std::get<0>(pivots) << ", r1="
//    << std::get<1>(pivots) << ", r2="
//    << std::get<2>(pivots) << ", s1="
//    << std::get<3>(pivots) << ", s2="
//    << std::get<4>(pivots)
//    << ">\n";

    Obv obv(&dailyPricesMD, "OBV");
//    obv.plot();

    ADL adl(&dailyPricesMD, "ADL");
//    adl.plot();

    RSI rsi(&dailyPricesMD, "RSI");
//    rsi.plot();

    SMA sma(&dailyPricesMD, 10, "10-day SMA");
//    sma.plot();

    EMA ema(&dailyPricesMD, 10, "10-day EMA");
//    ema.plot();

    MACD macd(&dailyPricesMD, "MACD");
    macd.printData();
    macd.plot();

    return 0;
}