//
// Created by Haleeq Usman on 2/16/16.
//

#include "DailyPriceMarketData.h"

DailyPriceMarketData::DailyPriceMarketData(int p) {
    period = p;
}

void DailyPriceMarketData::processDataLine(std::string line) {
    std::string value = "";
    size_t len = line.length();
    size_t column = 0;
    double values[5];

    for (int i = 0; i < len; ++i) {
        if (column > 0 && line[i] != ',') {
            value += line[i];
            continue;
        } else if (column == 0 && line[i] == ',') {
            ++column;
            continue;
        } else if (column > 0) {
            values[column - 1] = std::stod(value);
            value = "";
            ++column;
        }

    }

    data.push_back(std::make_tuple(values[0], values[1], values[2], values[3], values[4]));
}

void DailyPriceMarketData::printData() {
    std::cout << "====== " << ticker << " DAILY PRICE MARKET DATA ======" << std::endl;
    for (std::vector<std::tuple<double, double, double, double, size_t>>::const_iterator it = data.begin();
         it != data.end(); ++it) {
        std::cout << "<" << std::get<0>(*it) << ", " << std::get<1>(*it) << ", " << std::get<2>(*it) << ", " <<
        std::get<3>(*it) << ", " << std::get<4>(*it) << ">" << std::endl;
    }
    std::cout << "=============================" << std::endl;
}

bool DailyPriceMarketData::seedDataFromCSV(std::string filepath, std::string tickerSymbol) {
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

size_t DailyPriceMarketData::getSize() const {
    return data.size();
}

std::vector<std::tuple<double, double, double, double, size_t>>::const_iterator DailyPriceMarketData::getDataBegin() const {
    return data.begin();
}

std::vector<std::tuple<double, double, double, double, size_t>>::const_iterator DailyPriceMarketData::getDataEnd() const {
    return data.end();
}

size_t DailyPriceMarketData::getPeriod() const {
    return data.size();
}

std::string DailyPriceMarketData::getTickerSymbol() const {
    return ticker;
}

void DailyPriceMarketData::addDataPoint(double open, double high, double low, double close, size_t volume) {
    data.push_back(std::make_tuple(open, high, low, close, volume));
}

void DailyPriceMarketData::plot(DataPointType chartType) {
    Gnuplot gp;
    double min = -1;
    double max = -1;
    size_t x = 0;
    std::vector<std::pair<size_t, double>> dataPoints;

    for (std::vector<std::tuple<double, double, double, double, size_t>>::const_iterator it = data.begin();
         it != data.end(); ++it) {

        double value;
        switch(chartType) {
            case DataPointType::DAILY_PRICE_OPEN_PRICE:
                value = std::get<0>(*it);
                break;
            case DataPointType::DAILY_PRICE_HIGH_PRICE:
                value = std::get<1>(*it);
                break;
            case DataPointType::DAILY_PRICE_LOW_PRICE:
                value = std::get<2>(*it);
                break;
            case DataPointType::DAILY_PRICE_CLOSE_PRICE:
                value = std::get<3>(*it);
                break;
            case DataPointType::DAILY_PRICE_VOLUME:
                value = std::get<4>(*it);
                break;
            default:
                value = std::get<0>(*it);
                break;
        }

        if (value < min || min == -1) {
            min = value;
        }

        if (value > max || max == -1) {
            max = value;
        }

        dataPoints.push_back(std::make_pair(x++, value));
    }

    gp << "set term x11 title 'FTech: " << getTickerSymbol() << " - Daily Closing Price'\n";
    gp << "set xrange [0:" << (dataPoints.size() - 1) << "]\nset yrange [" << min << ":" << max << "]\n";
    gp << "plot '-' with lines title 'Daily Closing Price'\n";
    gp.send1d(dataPoints);
}

void DailyPriceMarketData::plotClosing() {
    plot(DataPointType::DAILY_PRICE_CLOSE_PRICE);
}
