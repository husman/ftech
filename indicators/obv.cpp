//
// Created by Haleeq Usman on 1/10/16.
//

#include <string>
#include <fstream>
#include "obv.h"

double *processDataLine(std::string line) {
    int i = 0;
    int column = 0;
    unsigned long len = line.length();
    std::string value = "";
    double *data = new double[5];

    while (i < len) {
        if (line[i] != ',') {
            value += line[i];
        } else {
            if (column > 0) {
                data[column - 1] = std::stod(value);
            }

            ++column;
            value = "";
        }
        ++i;
    }
    data[column - 1] = std::stod(value);

    return data;
}

void obv::printData() {
    printf("====== DATA ======\n");
    for (int i = 0; i < frameSize; ++i) {
        printf("%02d: %lf\n", i, data[i]);
    }
    printf("==================\n");
}

bool obv::setDataFromCSV(std::string filepath) {
    std::ifstream file(filepath);
    std::string line;

    if (!file) {
        std::cout << "could not open file " << filepath << "\n";
        return false;
    }

//    if (data) {
//        delete data;
//    }
    data = new double[frameSize];

    size_t i = 0;
    while (std::getline(file, line)) {
        if (i > 0) {
            size_t index = i - 1;
            double *dataLine = processDataLine(line);
            data[index++] = dataLine[0];
            data[index++] = dataLine[1];
            data[index++] = dataLine[2];
            data[index++] = dataLine[3];
            data[index++] = dataLine[4];
            data[index++] = dataLine[5];
            data[index++] = dataLine[6];
            i = index;
        } else {
            ++i;
        }
    }

    dataLen = i - 1;

    return true;
}

void obv::plotOBV() {
    Gnuplot gp;
    std::vector<std::pair<double, double> > dataPoints;

    std::cout << "dataLen = " << dataLen << "\n";
    size_t numRows = dataLen / 6;

    double obvValue = 0;
    double prevClosePrice = 0;
    double closePrice = 0;
    double closeVolume = 0;
    double minObv = 0;
    double maxObv = 0;

    for (size_t i = 0; i < numRows; ++i) {
        closeVolume = data[6 * i + 4];
        closePrice = data[6 * i + 3];

        if (closePrice > prevClosePrice) {
            obvValue = obvValue + closeVolume;
        } else if (closePrice < prevClosePrice) {
            obvValue = obvValue - closeVolume;
        }

        if (obvValue < minObv) {
            minObv = obvValue;
        }

        if (obvValue > maxObv) {
            maxObv = obvValue;
        }

        prevClosePrice = closePrice;
        dataPoints.push_back(std::make_pair(i, obvValue));
    }

    gp << "set term x11 title 'FTech: ADBE - OBV'\n";
    gp << "set xrange [0:" << (period - 1) << "]\nset yrange [" << minObv << ":" << maxObv << "]\n";
    gp << "plot '-' with lines title 'OBV'\n";
    gp.send1d(dataPoints);
}

obv::obv(int p, unsigned int lineType) {
    data = NULL;
    lineType = lineType;
    period = p;
    frameSize = period * lineType;
    dataLen = 0;
}
