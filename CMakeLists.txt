cmake_minimum_required(VERSION 3.3)
project(ftech)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    global.h
    indicators/obv/Obv.cpp
    indicators/obv/Obv.h
    MarketData.cpp
    MarketData.h
    main.cpp
    MarketEvent.cpp
    MarketEvent.h
    DailyPriceMarketData.h
    DailyPriceMarketData.cpp
    MarketObserver.h
    )

set(LIB_LINKS
    util
    boost_iostreams
    boost_system
    boost_filesystem
    )

link_directories($ENV{BOOST_HOME}/lib)
include_directories($ENV{BOOST_HOME}/include)

add_executable(ftech ${SOURCE_FILES})
target_link_libraries(ftech ${LIB_LINKS})
