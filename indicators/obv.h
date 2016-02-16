//
// Created by Haleeq Usman on 1/10/16.
//

#ifndef FTECH_OBV_H
#define FTECH_OBV_H

#include <stdio.h>
#include <iostream>
#include "constants.h"

#include <vector>
#include <cmath>
#include <boost/tuple/tuple.hpp>

#include "../gnuplot/gnuplot-iostream.h"

class obv {
private:
    int period;
    unsigned int lineType;
    int frameSize;
    double *data;
    size_t dataLen;

public:
    obv(int p, unsigned int lineType);
    void printData();
    void plotOBV();
    bool setDataFromCSV(std::string filepath);
};


#endif //FTECH_OBV_H
