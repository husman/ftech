#include <iostream>
#include "MarketEvent.h"
#include "models/macking.h"

//#include <cpprest/http_client.h>
//#include <cpprest/http_listener.h>              // HTTP server
//#include <cpprest/ws_client.h>                  // WebSocket client
//#include "PriceMarketData.h"
//#include "RateMarketData.h"
//#include "indicators/rsi/rsi.h"
//#include <boost/date_time/posix_time/posix_time.hpp>
//#include <oauth.h>
#include <dirent.h>


//using namespace utility;                    // Common utilities like string conversions
//using namespace web;                        // Common features like URIs.
//using namespace web::http;                  // Common HTTP functionality
//using namespace web::http::client;          // HTTP client features
//using namespace concurrency::streams;       // Asynchronous streams
//using namespace web::http::oauth1::experimental;
//using namespace web::http::experimental::listener;          // HTTP server
//using namespace web::experimental::web_sockets::client;     // WebSockets client
//using namespace web::json;                                  // JSON library
#include <boost/thread/thread.hpp>

int main() {
//    MarketEvent mktEvent;
//    PriceMarketData dailyPricesMD;
//    RateMarketData eurUsd;
//    eurUsd.seedDataFromCSV("data/EUR_USD_05_Week1.csv", "EUR_USD_May_20016_Week1");
//    eurUsd.plotBid();

//    RSI rsi(&eurUsd, "EUR/USD RSI");
//    rsi.plot();

//    double principal = 200.0;
//    double totalGain = 0;
//    int nbFiles = 0;
//    DIR *dir;
//    struct dirent *ent;
//    if ((dir = opendir("data/eurUSD/")) != NULL) {
//        while ((ent = readdir(dir)) != NULL) {
//            if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0) {
//                printf("%s\n", ent->d_name);
//
//                Macking macking("eurUSD/" + std::string(ent->d_name));
//                double gain = macking.runSimulation();
//                totalGain += gain;
//                ++nbFiles;
//                std::cout << ent->d_name << " - AverageGainCash = " << (gain/106) << "\n";
//            }
//        }
//        closedir(dir);
//    } else {
//        /* could not open directory */
//        perror("");
//        return EXIT_FAILURE;
//    }
//
//    double AverageGainCash = totalGain / nbFiles;
//    double AverageGainPercent = 100.0 * (AverageGainCash/106) / principal;
//    std::cout << "AverageGainCash = " << (AverageGainCash/106) << " AverageGainPercent = " << AverageGainPercent << "\n";

//    double shares = 769230.0;
//


//    Macking macking_04_1("EUR_USD_04_Week1");
//    Macking macking_04_2("EUR_USD_04_Week2");
//    Macking macking_04_3("EUR_USD_04_Week3");
//    Macking macking_04_4("EUR_USD_04_Week4");
//    gain1 = macking_04_1.runSimulation();
//    gain2 = macking_04_2.runSimulation();
//    gain3 = macking_04_3.runSimulation();
//    gain4 = macking_04_4.runSimulation();
//
//    double gainCash2 = gain1 + gain2 + gain3 + gain4;
//    AverageGainCash = gainCash2/4.0;
//    AverageGainPercent = 100.0 * AverageGainCash / shares;
//    std::cout << "AverageGainCash = " << AverageGainCash << " AverageGainPercent = " << AverageGainPercent << "\n";
//
//    Macking macking_05_1("EUR_USD_05_Week1");
//    Macking macking_05_2("EUR_USD_05_Week2");
//    Macking macking_05_3("EUR_USD_05_Week3");
//    Macking macking_05_4("EUR_USD_05_Week4");
//    gain1 = macking_05_1.runSimulation();
//    gain2 = macking_05_2.runSimulation();
//    gain3 = macking_05_3.runSimulation();
//    gain4 = macking_05_4.runSimulation();
//
//    double gainCash3 = gain1 + gain2 + gain3 + gain4;
//    AverageGainCash = gainCash3/4.0;
//    AverageGainPercent = 100.0 * AverageGainCash / shares;
//    std::cout << "AverageGainCash = " << AverageGainCash << " AverageGainPercent = " << AverageGainPercent << "\n";
//
//    AverageGainCash = (gainCash1 + gainCash2 + gainCash3)/12.0;
//    AverageGainPercent = 100.0 * AverageGainCash / shares;
//    std::cout << "AverageGainCash final = " << AverageGainCash << " AverageGainPercent final = " << AverageGainPercent << "\n";

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

//    http_client client(U("http://finance.yahoo.com/webservice/v1/"));
//    uri_builder builder(U("/symbols/NUGT/quote"));
//    builder.append_query(U("format"), U("json"));
//    builder.append_query(U("view"), U("detail"));
//
//    pplx::task<void> requestTask = client
//            .request(methods::GET, builder.to_string())
//            .then([=](http_response response) {
//                printf("Received response status code: %u\n", response.status_code());
//                return response.extract_json();
//            })
//            .then([](json::value resp_json) {
//                auto &price = resp_json[U("list")][U("resources")][0][U("resource")][U("fields")][U("price")];
//                std::cout << "Stock price = " << price << "\n";
//            });
//
//    try {
//        requestTask.wait();
//    }
//    catch (const std::exception &e) {
//        printf("Error exception: %s\n", e.what());
//    }

//    char *uri = NULL;
//    uri = oauth_sign_url2(
//            "https://etws.etrade.com/oauth/request_token?oauth_callback=oob",
//            NULL,
//            OA_HMAC,
//            NULL,
//            "4d9d8091c71667152442efca01f796e7",
//            "17e3402d445ec0d2bd3a49e65daa8a0c",
//            NULL,
//            NULL
//    );
//
//    if (!uri) {
//        return -1;
//    }

//    Q+5rV+nXkkPkJ1C3CsMcSIOtQXqh5kGgj3ifVa+RKu4=
//    d1H3tZLyRQtv8s/5VqDrkwVHpXvBFL2stu/MavfCqKo=

//
//    http_client client2(uri);
//    free(uri);
//
//    pplx::task<void> requestTask2 = client2
//            .request(methods::GET)
//            .then([=](http_response response) {
//                printf("Received response status code: %u\n", response.status_code());
//                return response.extract_string();
//            })
//            .then([](utility::string_t resp) {
//                std::cout << "resp = " << resp << "\n";
//                std::map<utility::string_t, utility::string_t> query = uri::split_query(uri::decode(resp));
//                utility::string_t oauthTokenKey = query.at("oauth_token");
//                utility::string_t oauthTokenSecret = query.at("oauth_token_secret");
//                std::cout << "oauthTokenKey = " << oauthTokenKey << " oauthTokenSecret = " << oauthTokenSecret << "\n";
//            });
//
//    try {
//        requestTask2.wait();
//    }
//    catch (const std::exception &e) {
//        printf("Error exception: %s\n", e.what());
//    }

    // ETrade oauth
//    const char *cKey = "4d9d8091c71667152442efca01f796e7";
//    const char *cSecret = "17e3402d445ec0d2bd3a49e65daa8a0c";
//    const char *accessToken = "9Kf34hr83/3mKWqqcdHqq2Gc0w8rVJBsccoJogIwrTo=";
//    const char *accessTokenSecret = "x8cFyTBJXUBCvX+moTKEKtphcqQigQle0scYczNCNCs=";
//    const char *endpoint = "https://etwssandbox.etrade.com/market/sandbox/rest/quote/adbe,nugt.json";
//
//    char *uri = oauth_sign_url2(endpoint, NULL, OA_HMAC, "GET", cKey, cSecret, accessToken, accessTokenSecret);
//
//    if (!uri) {
//        return -1;
//    }
//
//    http_client http(uri);
//    pplx::task<void> requestTask3 = http.request(methods::GET)
//            .then([=](http_response response) {
//                return response.extract_json();
//            })
//            .then([](json::value qData) {
//                auto &ask = qData[U("quoteResponse")][U("quoteData")][0][U("all")][U("ask")];
//                auto &askSize = qData[U("quoteResponse")][U("quoteData")][0][U("all")][U("askSize")];
//                auto &askTime = qData[U("quoteResponse")][U("quoteData")][0][U("all")][U("askTime")];
//                std::cout << "Stock ask = " << ask << " ask size = " << askSize << "ask time = " << askTime << "\n";
//            });
//
//    try {
//        requestTask3.wait();
//    } catch (const std::exception &e) {
//        printf("Error exception: %s\n", e.what());
//    }

    Macking macking("EUR/USD");

    while(true) {
        // wait slightly more than half a second
        boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
        macking.runSimulation();
    }

    return 0;
}