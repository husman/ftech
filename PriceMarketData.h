//
// Created by Haleeq Usman on 2/16/16.
//

#ifndef FTECH_DAILYPRICEMARKETDATA_H
#define FTECH_DAILYPRICEMARKETDATA_H

#include "global.h"

class PriceMarketData {
private:
    // data: <double open, double high, double low, double close, size_t volume>
    std::vector<std::tuple<double, double, double, double, size_t>> data;

    // # years the dataset represents.
    int period;

    std::string ticker;

    void processDataLine(std::string line);

    enum DataPointType {
        DAILY_PRICE_OPEN_PRICE,
        DAILY_PRICE_HIGH_PRICE,
        DAILY_PRICE_LOW_PRICE,
        DAILY_PRICE_CLOSE_PRICE,
        DAILY_PRICE_VOLUME,
    };

public:
    typedef std::vector<std::tuple<double, double, double, double, size_t>> PriceMarketDataVector;
    typedef std::vector<std::tuple<double, double, double, double, size_t>> MarketDataVector;

    PriceMarketData(int p = 20);

    void printData();

    void plot(DataPointType chartType);

    void plotClosing();

    void plotVolume();

    size_t getSize() const;

    std::string getTickerSymbol() const;

    size_t getPeriod() const;

    void addDataPoint(double open, double high, double low, double close, size_t volume);

    std::vector<std::tuple<double, double, double, double, size_t>>::const_iterator getDataBegin() const;

    std::vector<std::tuple<double, double, double, double, size_t>>::const_iterator getDataEnd() const;

    bool seedDataFromCSV(std::string filepath, std::string tickerSymbol);

    std::tuple<double, double, double, double, double> getPivots();
};

#endif //FTECH_MARKETDATA_H
