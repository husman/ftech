//
// Created by Haleeq Usman on 1/10/16.
//

#ifndef FTECH_OBV_H
#define FTECH_OBV_H

#include <stdio.h>
#include "constants.h"

class obv {
private:
    int period;
    int dataWidth, dataHeight;
    double *data;

public:
    bool setDataFromCSV(char *filepath);
    bool setPeriod(int period);
    double *processCSVLine(std::string, CSVLineType);
};


#endif //FTECH_OBV_H
