#include "../include/CSVLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

string trim(string s) {
    if(!s.empty()) {
        if(s[s.size()-1] == '\r') s.erase(s.size()-1);
    }
    return s;
}

vector<Stock> CSVLoader::loadStocks(const string& filename) {
    vector<Stock> stocks;

    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Could not open CSV file: " << filename << endl;
        return stocks;
    }

    string line;

    // Skip the first line because it contains column headings
    getline(file, line);

    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        stringstream ss(line);

        string symbol;
        string ldcp;
        string open;
        string high;
        string low;
        string close;
        string change;
        string changePercent;
        string volume;

        getline(ss, symbol, ',');
        getline(ss, ldcp, ',');
        getline(ss, open, ',');
        getline(ss, high, ',');
        getline(ss, low, ',');
        getline(ss, close, ',');
        getline(ss, change, ',');
        getline(ss, changePercent, ',');
        getline(ss, volume, ',');

        volume = trim(volume);

        try {
            Stock stock(
                symbol,
                stod(ldcp),
                stod(open),
                stod(high),
                stod(low),
                stod(close),
                stod(change),
                stod(changePercent),
                stoll(volume)
            );

            stocks.push_back(stock);
        }
        catch (...) {
            // If any row has invalid data, skip that row
        }
    }

    file.close();

    return stocks;
}