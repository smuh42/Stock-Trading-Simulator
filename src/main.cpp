#include "../include/TradingSystem.h"
#include "../include/CSVLoader.h"
#include "../include/GUIManager.h"
#include <iostream>
using namespace std;

int main() {
    CSVLoader loader;
    vector<Stock> stocks = loader.loadStocks("data/PSX_Market_Watch_Top100.csv");

    if (stocks.empty()) {
        cout << "No stocks loaded. Make sure data/PSX_Market_Watch_Top100.csv exists.\n";
        return 1;
    }

    TradingSystem system;
    system.loadStocks(stocks);

    GUIManager gui(&system);
    gui.run();

    return 0;
}
