//
// Created by Haleeq Usman on 2/16/16.
//

#ifndef FTECH_MARKETDATA_H
#define FTECH_MARKETDATA_H

#include "global.h"


class MarketData {
private:
    // data: <double price, size_t volume>
    std::vector<std::pair<double, size_t>> data;
    int period;
    std::string ticker;

    void processDataLine(std::string line);

public:
    MarketData(int p = 20);

    void printData();

    void plot();

    size_t getSize() const;

    std::string getTickerSymbol() const;

    size_t getPeriod() const;

    void addDataPoint(double price, size_t volume);

    std::vector<std::pair<double, size_t>>::const_iterator getDataBegin() const;

    std::vector<std::pair<double, size_t>>::const_iterator getDataEnd() const;

    bool seedDataFromCSV(std::string filepath, std::string tickerSymbol);
};

#endif //FTECH_MARKETDATA_H
