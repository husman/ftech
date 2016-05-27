//
// Created by Haleeq Usman on 5/23/16.
//

#include "macking.h"

Macking::Macking(std::string ticker) {
    marketData = new PriceMarketData(14);
    marketData->seedDataFromCSV("data/" + ticker + ".csv", ticker);
    adl = new ADL(marketData);
    rsi = new RSI(marketData);
    macd = new MACD(marketData);
}

void Macking::runSimulation() {
    for (int f = 0; f < 1; f++) {
        PriceMarketData::PriceMarketDataVector::const_iterator itMktData = marketData->getDataBegin() + 26 + 9;
        Indicator::IndicatorDataVector::const_iterator itMacd = macd->getDataBegin() + 9;
        Indicator::IndicatorDataVector::const_iterator itMacdSignal = macd->ema9->getDataBegin();
        Indicator::IndicatorDataVector::const_iterator itRsi = rsi->getDataBegin() + 2;

        unsigned int wins = 0, losses = 0, i = 0;
        profit = 0;
        double shares = 1;
        double boughtPrice = -1;
        while (itMktData != marketData->getDataEnd()) {
            double price = std::get<3>(*itMktData);
            double macdLine = itMacd->second;
            double macdSignal = itMacdSignal->second;
            double rsi = itRsi->second;

            if (boughtPrice != -1) {
                if (rsi > 60) {
                    if (price - boughtPrice < 0) {
                        ++losses;
                    } else if (price - boughtPrice > 0) {
                        ++wins;
                    }

                    profit += (price - boughtPrice) * shares;
                    boughtPrice = -1;
                } else {
                    ++itMktData;
                    ++itMacd;
                    ++itMacdSignal;
                    ++itRsi;
                    continue;
                }
            }

            if (rsi < 35) {
                boughtPrice = price;
            }

            ++itMktData;
            ++itMacd;
            ++itMacdSignal;
            ++itRsi;
        }

        std::cout << "signal - macd > " << f << "\n";
        std::cout << "profit = " << profit << "\n";
        std::cout << "wins = " << wins << " losses = " << losses << " (" << (100 * wins / (wins + losses)) << "%)" <<
        "\n\n";
    }

}
