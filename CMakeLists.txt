cmake_minimum_required(VERSION 3.3)
project(ftech)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    global.h
    indicators/indicator.cpp
    indicators/indicator.h
    indicators/obv/obv.cpp
    indicators/obv/obv.h
    indicators/adl/adl.cpp
    indicators/adl/adl.h
    indicators/rsi/rsi.cpp
    indicators/rsi/rsi.h
    indicators/sma/sma.cpp
    indicators/sma/sma.h
    indicators/ema/ema.cpp
    indicators/ema/ema.h
    indicators/macd/macd.cpp
    indicators/macd/macd.h
    MarketData.cpp
    MarketData.h
    main.cpp
    MarketEvent.cpp
    MarketEvent.h
    PriceMarketData.h
    PriceMarketData.cpp
    MarketObserver.h
    models/macking.h
    models/macking.cpp
    RateMarketData.h
    RateMarketData.cpp
)

set(LIB_LINKS
    util
    boost_iostreams
    boost_system
    boost_filesystem
    boost_thread-mt
    boost_chrono-mt
    ssl
    crypto
    libcpprest.2.8.dylib
    liboauth.0.dylib
    )

link_directories($ENV{BOOST_HOME}/lib)
link_directories(/usr/local/opt/openssl/lib)
link_directories($ENV{HOME}/workspace/casablanca/build.debug/Binaries)
link_directories(/usr/local/lib)
include_directories($ENV{BOOST_HOME}/include)
include_directories($ENV{HOME}/workspace/casablanca/Release/include)
include_directories(/usr/local/opt/openssl/include)
include_directories(/usr/local/include)

add_executable(ftech ${SOURCE_FILES})
target_link_libraries(ftech ${LIB_LINKS})
