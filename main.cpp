#include <iostream>
#include "MarketEvent.h"

#include <cpprest/http_client.h>
#include <cpprest/http_listener.h>              // HTTP server
#include <cpprest/ws_client.h>                  // WebSocket client


using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams

using namespace web::http::experimental::listener;          // HTTP server
using namespace web::experimental::web_sockets::client;     // WebSockets client
using namespace web::json;                                  // JSON library

int main() {
//    MarketEvent mktEvent;
//    PriceMarketData dailyPricesMD;

//    dailyPricesMD.seedDataFromCSV("data/goog2.csv", "table.goog-dec-1-2015-may-15-2016");

//    dailyPricesMD.printData();
//    dailyPricesMD.plotClosing();
//    dailyPricesMD.plotVolume();

//    auto pivots = dailyPricesMD.getPivots();
//    std::cout
//    << "pivots = <p="
//    << std::get<0>(pivots) << ", r1="
//    << std::get<1>(pivots) << ", r2="
//    << std::get<2>(pivots) << ", s1="
//    << std::get<3>(pivots) << ", s2="
//    << std::get<4>(pivots)
//    << ">\n";

//    Obv obv(&dailyPricesMD, "OBV");
//    obv.plot();

//    ADL adl(&dailyPricesMD, "ADL");
//    adl.plot();

//    RSI rsi(&dailyPricesMD, "RSI");
//    rsi.plot();

//    SMA sma(&dailyPricesMD, 10, "10-day SMA");
//    sma.plot();

//    EMA ema(&dailyPricesMD, 10, "10-day EMA");
//    ema.plot();

//    MACD macd(&dailyPricesMD, "MACD");
//    macd.printData();
//    macd.plot();

//    Macking macking("goog");
//    macking.runSimulation();

    http_client client(U("http://finance.yahoo.com/webservice/v1/"));
    uri_builder builder(U("/symbols/NUGT/quote"));
    builder.append_query(U("format"), U("json"));
    builder.append_query(U("view"), U("detail"));

    pplx::task<void> requestTask = client
            .request(methods::GET, builder.to_string())
            .then([=](http_response response) {
                printf("Received response status code: %u\n", response.status_code());
                return response.extract_json();
            })
            .then([](json::value resp_json) {
                auto &price = resp_json[U("list")][U("resources")][0][U("resource")][U("fields")][U("price")];
                std::cout << "Stock price = " << price << "\n";
            });

    try {
        requestTask.wait();
    }
    catch (const std::exception &e) {
        printf("Error exception: %s\n", e.what());
    }

    return 0;
}