#include "../include/TradingSystem.h"
#include "../include/Exceptions.h"
#include <fstream>
#include <ctime>
using namespace std;

TradingSystem::TradingSystem() : portfolio(100000.0) {
    lastMessage = "System ready.";

    ifstream check("records/trade_history.csv");

    if (!check.good()) {
        ofstream file("records/trade_history.csv");
        file << "ACTION,SYMBOL,QUANTITY,PRICE,TOTAL,TIMESTAMP\n";
        file.close();
    }
}

TradingSystem::~TradingSystem() {}

string TradingSystem::getCurrentTimestamp() const {
    time_t now = time(0);
    string timestamp = ctime(&now);

    if (!timestamp.empty() && timestamp[timestamp.size() - 1] == '\n') {
        timestamp.erase(timestamp.size() - 1);
    }

    return timestamp;
}

void TradingSystem::appendTradeToFile(const TradeRecord& trade) {
    ofstream file("records/trade_history.csv", ios::app);

    if (file.is_open()) {
        file << trade.toCSV() << "\n";
        file.close();
    }
}

void TradingSystem::loadStocks(vector<Stock> loadedStocks) {
    stocks = loadedStocks;
    buildTopGainers();
}

vector<Stock>& TradingSystem::getStocks() {
    return stocks;
}

Portfolio& TradingSystem::getPortfolio() {
    return portfolio;
}

vector<TradeRecord> TradingSystem::getTradeHistory() const {
    return tradeHistory;
}

string TradingSystem::getLastMessage() const {
    return lastMessage;
}

void TradingSystem::buyStock(const Stock& stock, int quantity) {
    if (quantity <= 0) {
        throw InvalidQuantityException();
    }

    double total = quantity * stock.getClose();

    if (portfolio.getCashBalance() < total) {
        throw InsufficientFundsException();
    }

    portfolio.addStock(stock.getSymbol(), quantity, stock.getClose());

    TradeRecord trade("BUY", stock.getSymbol(), quantity, stock.getClose(), getCurrentTimestamp());

    tradeHistory.push_back(trade);
    appendTradeToFile(trade);

    lastMessage = "Bought " + to_string(quantity) + " shares of " + stock.getSymbol();
}

void TradingSystem::sellStock(const Stock& stock, int quantity) {
    if (quantity <= 0) {
        throw InvalidQuantityException();
    }

    int ownedShares = portfolio.getShares(stock.getSymbol());

    if (ownedShares < quantity) {
        throw InsufficientSharesException();
    }

    portfolio.removeStock(stock.getSymbol(), quantity, stock.getClose());

    TradeRecord trade("SELL", stock.getSymbol(), quantity, stock.getClose(), getCurrentTimestamp());

    tradeHistory.push_back(trade);
    appendTradeToFile(trade);

    lastMessage = "Sold " + to_string(quantity) + " shares of " + stock.getSymbol();
}

void TradingSystem::buildTopGainers() {
    while (!topGainers.empty()) {
        topGainers.pop();
    }

    for (int i = 0; i < (int)stocks.size(); i++) {
        topGainers.push(stocks[i]);
    }
}

vector<Stock> TradingSystem::getTopGainers(int count) {
    vector<Stock> result;
    priority_queue<Stock> temp = topGainers;

    int added = 0;

    while (!temp.empty() && added < count) {
        result.push_back(temp.top());
        temp.pop();
        added++;
    }

    return result;
}

void TradingSystem::mergeSortByVolume() {
    if (!stocks.empty()) {
        mergeSortByVolume(0, stocks.size() - 1);
    }
}

void TradingSystem::mergeSortByVolume(int left, int right) {
    if (left >= right) {
        return;
    }

    int mid = left + (right - left) / 2;

    mergeSortByVolume(left, mid);
    mergeSortByVolume(mid + 1, right);

    merge(left, mid, right);
}

void TradingSystem::merge(int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Stock> L(n1);
    vector<Stock> R(n2);

    for (int i = 0; i < n1; i++) {
        L[i] = stocks[left + i];
    }

    for (int j = 0; j < n2; j++) {
        R[j] = stocks[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (L[i].getVolume() >= R[j].getVolume()) {
            stocks[k] = L[i];
            i++;
        }
        else {
            stocks[k] = R[j];
            j++;
        }

        k++;
    }

    while (i < n1) {
        stocks[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        stocks[k] = R[j];
        j++;
        k++;
    }
}