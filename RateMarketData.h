//
// Created by Haleeq Usman on 2/16/16.
//

#ifndef FTECH_RATEMARKETDATA_H
#define FTECH_RATEMARKETDATA_H

#include "global.h"

class RateMarketData {
private:
    // data: <double bid, double ask>
    std::vector<std::pair<double, double>> data;

    // # years the dataset represents.
    int period;

    std::string ticker;

    void processDataLine(std::string line);

    enum DataPointType {
        RATE_BID_PRICE,
        RATE_ASK_PRICE,
    };

public:
    typedef std::vector<std::pair<double, double>> MarketDataVector;

    RateMarketData(int p = 20);

    void printData();

    void plot(DataPointType chartType);

    void plotBid();

    void plotAsk();

    size_t getSize() const;

    std::string getTickerSymbol() const;

    size_t getPeriod() const;

    void addDataPoint(double bid, double ask);

    std::vector<std::pair<double, double>>::const_iterator getDataBegin() const;

    std::vector<std::pair<double, double>>::const_iterator getDataEnd() const;

    bool seedDataFromCSV(std::string filepath, std::string tickerSymbol);
};

#endif //FTECH_MARKETDATA_H
