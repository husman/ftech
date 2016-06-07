//
// Created by Haleeq Usman on 5/23/16.
//

#include "macking.h"
#include <cpprest/http_client.h>

using namespace utility; // Common utilities like string conversions
using namespace web; // Common features like URIs.
using namespace web::http; // Common HTTP functionality
using namespace web::http::client; // HTTP client features
using namespace web::http::oauth2::experimental;
using namespace web::json; // JSON library

Macking::Macking(std::string ticker) {
    wins = 0, losses = 0, i = 0;
    profit = 0;
    shares = 700;
    boughtPrice = -1;

    symbol = ticker;
    rsiBid = new RSI("RSI BID");
    rsiAsk = new RSI("RSI ASK");
}

void Macking::runSimulation() {
    http_client http("https://api-fxtrade.oanda.com/v1");
    web::http::http_request req(methods::GET);
    req.set_request_uri("/prices?instruments=EUR_USD");
    req.headers().add(U("Authorization"),
                      U("Bearer 5e66d4d12e73f5457f668b3f47deb25b-079d6179afaac2e932fc771b1ceae31c"));

    pplx::task<void> requestTask3 = http.request(req)
            .then([=](http_response response) {
                return response.extract_json();
            })
            .then([this](json::value qData) mutable {
                double bid = std::stod(qData[U("prices")][0][U("bid")].serialize());
                double ask = std::stod(qData[U("prices")][0][U("ask")].serialize());
                rsiBid->addRate(bid);
                rsiAsk->addRate(ask);
                auto &askTime = qData[U("prices")][0][U("time")];

                std::cout << i << " Rate bid = " << bid << " ask = " << ask << " ask time = " << askTime << "\n";
                if (i < 14) {
                    ++i;
                }

                if(i >= 14) {
                    if (boughtPrice != -1) {
                        if (rsiBid->getDataEnd()->second > 90 && (bid - boughtPrice > 0)) {
                            if (bid - boughtPrice < 0) {
                                ++losses;
                            } else if (bid - boughtPrice > 0) {
                                ++wins;
                            }

                            std::cout << "Sold @ bid: " << bid << "\n";
                            profit += (bid - boughtPrice) * shares;
                            boughtPrice = -1;
                        }
                    } else {
                        std::cout << "Checking to buy @ ask: " << ask << " with rsi-ask = " <<
                        rsiAsk->getDataEnd()->second <<
                        "\n";
                        if (rsiAsk->getDataEnd()->second < 25) {
                            std::cout << "Bought @ ask: " << ask << "\n";
                            boughtPrice = ask;
                        }

                        std::cout << "profit = " << profit << "\n";
                        std::cout << "wins = " << wins << " losses = " << losses << " (" <<
                        (100 * wins / (wins + losses)) << "%)" <<
                        "\n\n";
                    }

                    return profit;
                }
            });
}
