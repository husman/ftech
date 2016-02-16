#include <iostream>
#include "indicators/obv.h"

using namespace std;

int main() {
    obv ind(20, CSVLineType::DATE_OPEN_LOW_HIGH_CLOSE_AVGVOL);
    ind.setDataFromCSV("HistoricalQuotes_ADBE_2-15-20162-51PMET.csv");
    ind.printData();
    ind.plotOBV();
    cout << "Launching OBV plot." << endl;
    return 0;
}