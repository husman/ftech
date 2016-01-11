//
// Created by Haleeq Usman on 1/10/16.
//

#include <string>
#include <fstream>
#include "obv.h"

bool obv::setDataFromCSV(char *filepath) {
    std::ifstream file(filepath);
    std::string line;

    if(data) {
        delete data;
    }

    data = new double[dataWidth * dataHeight];

    while (std::getline(file, line)) {

    }

    return true;
}

bool obv::setPeriod(int period) {
    return false;
}

double *obv::processCSVLine(std::string line, CSVLineType type) {
    double *dataPoints = new double[7];
    std::string value = "";
    int index = 0;
    for(std::string::iterator it = line.begin(); it != line.end(); ++it) {
        if(*it == ' ') {
            dataPoints[index++] = std::stod(value);
            value = "";
            continue;
        }

        value += *it;
    }

    return dataPoints;
}
