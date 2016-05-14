//
// Created by Haleeq Usman on 2/16/16.
//

#include "PriceMarketData.h"

PriceMarketData::PriceMarketData(int p) {
    period = p;
}

void PriceMarketData::processDataLine(std::string line) {
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

void PriceMarketData::printData() {
    std::cout << "====== " << ticker << " DAILY PRICE MARKET DATA ======" << std::endl;
    for (std::vector<std::tuple<double, double, double, double, size_t>>::const_iterator it = data.begin();
         it != data.end(); ++it) {
        std::cout << "<" << std::get<0>(*it) << ", " << std::get<1>(*it) << ", " << std::get<2>(*it) << ", " <<
        std::get<3>(*it) << ", " << std::get<4>(*it) << ">" << std::endl;
    }
    std::cout << "=============================" << std::endl;
}

bool PriceMarketData::seedDataFromCSV(std::string filepath, std::string tickerSymbol) {
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

size_t PriceMarketData::getSize() const {
    return data.size();
}

std::vector<std::tuple<double, double, double, double, size_t>>::const_iterator PriceMarketData::getDataBegin() const {
    return data.begin();
}

std::vector<std::tuple<double, double, double, double, size_t>>::const_iterator PriceMarketData::getDataEnd() const {
    return data.end();
}

size_t PriceMarketData::getPeriod() const {
    return data.size();
}

std::string PriceMarketData::getTickerSymbol() const {
    return ticker;
}

void PriceMarketData::addDataPoint(double open, double high, double low, double close, size_t volume) {
    data.push_back(std::make_tuple(open, high, low, close, volume));
}

void PriceMarketData::plot(DataPointType chartType) {
    Gnuplot gp;
    double min = -1;
    double max = -1;
    size_t x = 0;
    std::vector<std::pair<size_t, double>> dataPoints;

    for (std::vector<std::tuple<double, double, double, double, size_t>>::const_iterator it = data.begin();
         it != data.end(); ++it) {

        double value;
        switch (chartType) {
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
    gp << "plot '-' w l ls 7 title 'Daily Closing Price'\n";
    gp.send1d(dataPoints);
}

std::tuple<double, double, double, double, double> PriceMarketData::getPivots() {
    std::vector<std::tuple<double, double, double, double, size_t>>::const_iterator it = data.begin();

    // R2 = P + (H - L) = P + (R1 - S1)
    // R1 = (P x 2) - L
    // P = (H + L + C) / 3
    // S1 = (P x 2) - H
    // S2 = P - (H - L) = P - (R1 - S1)
    double h = std::get<1>(*it);
    double l = std::get<2>(*it);
    double c = std::get<3>(*it);

    double p = (h + l + c) / 3;

    double r1 = p * 2 - l;
    double s1 = p * 2 - h;
    double r2 = p + (r1 - s1);
    double s2 = p - (r1 - s1);

    return std::make_tuple(p, r1, r2, s1, s2);
}

void PriceMarketData::plotClosing() {
    plot(DataPointType::DAILY_PRICE_CLOSE_PRICE);
}

void PriceMarketData::plotVolume() {
    plot(DataPointType::DAILY_PRICE_VOLUME);
}
