cmake_minimum_required(VERSION 3.3)
project(ftech)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    indicators/constants.h
    indicators/obv/Obv.cpp
    indicators/obv/Obv.h
    indicators/MarketData.cpp
    indicators/MarketData.h
    main.cpp
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
