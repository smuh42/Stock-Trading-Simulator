#ifndef CSVLOADER_H
#define CSVLOADER_H

#include <vector>
#include <string>
#include "Stock.h"
using namespace std;

class CSVLoader {
public:
    vector<Stock> loadStocks(const string& filename);
};

#endif
