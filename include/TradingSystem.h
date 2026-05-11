#ifndef TRADINGSYSTEM_H
#define TRADINGSYSTEM_H

#include <vector>
#include <queue>
#include <string>
#include "Stock.h"
#include "Portfolio.h"
#include "TradeRecord.h"

using namespace std;

class TradingSystem {
private:
    vector<Stock> stocks;
    Portfolio portfolio;
    vector<TradeRecord> tradeHistory;
    priority_queue<Stock> topGainers;
    string lastMessage;

    string getCurrentTimestamp() const;
    void appendTradeToFile(const TradeRecord& trade);
    void merge(int left, int mid, int right);

public:
    TradingSystem();
    ~TradingSystem();

    void loadStocks(vector<Stock> loadedStocks);

    vector<Stock>& getStocks();
    Portfolio& getPortfolio();
    vector<TradeRecord> getTradeHistory() const;
    string getLastMessage() const;

    void buyStock(const Stock& stock, int quantity);
    void sellStock(const Stock& stock, int quantity);

    void buildTopGainers();
    vector<Stock> getTopGainers(int count);

    void mergeSortByVolume();
    void mergeSortByVolume(int left, int right);
};

#endif