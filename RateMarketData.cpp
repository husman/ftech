//
// Created by Haleeq Usman on 2/16/16.
//

#include "RateMarketData.h"

RateMarketData::RateMarketData(int p) {
    period = p;
}

void RateMarketData::processDataLine(std::string line) {
    std::string value = "";
    size_t len = line.length();
    size_t column = 0;
    double values[2];

    for (int i = 0; i < len; ++i) {
        if (column > 3 && line[i] != ',') {
            value += line[i];
            continue;
        } else if (column < 4 && line[i] == ',') {
            ++column;
            continue;
        } else if (column > 3) {
            values[column - 4] = std::stod(value);
            value = "";
            ++column;
        }

    }
    values[column - 4] = std::stod(value);

    data.insert(data.end(), std::make_pair(values[0], values[1]));
}

void RateMarketData::printData() {
    std::cout << "====== " << ticker << " RATE TICK MARKET DATA ======" << std::endl;
    for (std::vector<std::pair<double, double>>::const_iterator it = data.begin();
         it != data.end(); ++it) {
        std::cout << "<" << it->first << ", " << it->second << ">" << std::endl;
    }
    std::cout << "=============================" << std::endl;
}

bool RateMarketData::seedDataFromCSV(std::string filepath, std::string tickerSymbol) {
    std::ifstream file(filepath);
    std::string line;
    size_t row = 0;

    if (!file) {
        std::cout << "could not open file " << filepath << std::endl;
        return false;
    }

    ticker = tickerSymbol;

    while (std::getline(file, line)) {
        if (row > 0) {
            processDataLine(line);
        }

        ++row;
    }

    return true;
}

size_t RateMarketData::getSize() const {
    return data.size();
}

std::vector<std::pair<double, double>>::const_iterator RateMarketData::getDataBegin() const {
    return data.begin();
}

std::vector<std::pair<double, double>>::const_iterator RateMarketData::getDataEnd() const {
    return data.end();
}

size_t RateMarketData::getPeriod() const {
    return data.size();
}

std::string RateMarketData::getTickerSymbol() const {
    return ticker;
}

void RateMarketData::addDataPoint(double bid, double ask) {
    data.push_back(std::make_tuple(bid, ask));
}

void RateMarketData::plot(DataPointType chartType) {
    Gnuplot gp;
    std::string title;
    double min = -1;
    double max = -1;
    size_t x = 0;
    std::vector<std::pair<size_t, double>> bidDataPoints;
    std::vector<std::pair<size_t, double>> askDataPoints;

    for (std::vector<std::pair<double, double>>::const_iterator it = data.begin();
         it != data.end(); ++it) {

        double bid = it->first;
        double ask = it->second;

        if (bid < min || min == -1) {
            min = bid;
        }

        if (bid > max || max == -1) {
            max = bid;
        }

        if (ask < min || min == -1) {
            min = ask;
        }

        if (ask > max || max == -1) {
            max = ask;
        }

        bidDataPoints.push_back(std::make_pair(x, bid));
        askDataPoints.push_back(std::make_pair(x++, ask));
    }

    gp << "set term x11 title 'FTech: " << getTickerSymbol() << " - Rate'\n";
    gp << "set xrange [0:" << (bidDataPoints.size() - 1) << "]\nset yrange [" << min << ":" << max << "]\n";
    gp << "plot '-' w l ls 6 title 'Bid', ";
    gp << "'-' w l ls 7 title 'Ask'\n";
    gp.send1d(bidDataPoints);
    gp.send1d(askDataPoints);
}

void RateMarketData::plotBid() {
    plot(DataPointType::RATE_BID_PRICE);
}

void RateMarketData::plotAsk() {
    plot(DataPointType::RATE_ASK_PRICE);
}
