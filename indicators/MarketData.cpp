//
// Created by Haleeq Usman on 2/16/16.
//

#include "MarketData.h"

MarketData::MarketData(int p) {
    period = p;
}

void MarketData::processDataLine(std::string line) {
    double price = 0;
    size_t volume = 0;

    std::string value = "";
    size_t len = line.length();

    for (int i = 0; i < len; ++i) {
        if (line[i] != ',') {
            value += line[i];
            continue;
        }

        price = std::stod(value);
        value = "";
    }

    volume = std::stoul(value);

    data.push_back(std::make_pair(price, volume));
}

void MarketData::printData() {
    std::cout << "====== " << ticker << " MARKET DATA ======" << std::endl;
    for (std::vector<std::pair<double, size_t>>::const_iterator it = data.begin(); it != data.end(); ++it) {
        std::cout << "<" << it->first << ", " << it->second << ">" << std::endl;
    }
    std::cout << "=============================" << std::endl;
}

bool MarketData::seedDataFromCSV(std::string filepath, std::string tickerSymbol) {
    std::ifstream file(filepath);
    std::string line;

    if (!file) {
        std::cout << "could not open file " << filepath << std::endl;
        return false;
    }

    ticker = tickerSymbol;

    while (std::getline(file, line)) {
        processDataLine(line);
    }

    return true;
}

size_t MarketData::getSize() const {
    return data.size();
}

std::vector<std::pair<double, size_t>>::const_iterator MarketData::getDataBegin() const {
    return data.begin();
}

std::vector<std::pair<double, size_t>>::const_iterator MarketData::getDataEnd() const {
    return data.end();
}

int MarketData::getPeriod() const {
    return period;
}

std::string MarketData::getTickerSymbol() const {
    return ticker;
}
