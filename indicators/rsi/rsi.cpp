//
// Created by Haleeq Usman on 4/11/16.
//

#include "rsi.h"

void RSI::buildData() {
    double runningGain = 0;
    double runningLoss = 0;
    double prevAvgGain = 0;
    double prevAvgLoss = 0;
    double prevPrice = 0;
    int counter = 0;
    int period = 14;
    bool isInitialRSI = true;


    for (std::vector<std::tuple<double, double, double, double, size_t>>::const_iterator it = mktData->getDataBegin();
         it != mktData->getDataEnd(); ++it) {
        double price = std::get<3>(*it);
        double delta = price - prevPrice;

        if (delta == 0) {
            continue;
        }

        if (counter > 0) {
            if (delta >= 0) {
                runningGain += delta;
            } else {
                runningLoss += delta * -1;
            }
        }

        ++counter;
        if (isInitialRSI) {
            prevPrice = price;

            if (counter < period != 0) {
                continue;
            }

            prevAvgGain = runningGain / period;
            prevAvgLoss = runningLoss / period;

            double initialRS = prevAvgGain / prevAvgLoss;
            double initialRSI = 100 - 100 / (1 + initialRS);
            data.push_back(std::make_pair(price, initialRSI));

            isInitialRSI = false;
            continue;
        }

        if (delta > 0) {
            prevAvgGain = (prevAvgGain * (period - 1) + delta) / period;
            prevAvgLoss = (prevAvgLoss * (period - 1) + 0) / period;
        } else if(delta < 0) {
            prevAvgGain = (prevAvgGain * (period - 1) + 0) / period;
            prevAvgLoss = (prevAvgLoss * (period - 1) + (delta * -1)) / period;
        } else {
            prevAvgGain = (prevAvgGain * (period - 1) + 0) / period;
            prevAvgLoss = (prevAvgLoss * (period - 1) + 0) / period;
        }

        double rs = prevAvgGain / prevAvgLoss;
        double rsi = 100 - 100 / (1 + rs);
        data.push_back(std::make_pair(price, rsi));
    }
}

RSI::RSI(PriceMarketData const *marketData, std::string n) : Indicator(marketData, n) {
    buildData();
}
