#include <iostream>
#include "MarketData.h"
#include "indicators/obv/Obv.h"

using namespace std;

int main() {
    MarketData md;
    md.seedDataFromCSV("data/HistoricalQuotes_ADBE_2-15-20162-51PMET.csv", "ADBE");

    Obv obv(&md);
    obv.plotOBV();
    return 0;
}