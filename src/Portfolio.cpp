#include "../include/Portfolio.h"

Portfolio::Portfolio(double cash) {
    cashBalance = cash;
}

Portfolio::~Portfolio() {}

double Portfolio::getCashBalance() const {
    return cashBalance;
}

int Portfolio::getShares(string symbol) const {
    auto it = holdings.find(symbol);
    if (it == holdings.end()) return 0;
    return it->second;
}

double Portfolio::getInvestedAmount(string symbol) const {
    auto it = investedAmount.find(symbol);
    if (it == investedAmount.end()) return 0;
    return it->second;
}

map<string, int> Portfolio::getHoldings() const {
    return holdings;
}

void Portfolio::addStock(string symbol, int quantity, double price) {
    cashBalance -= quantity * price;
    holdings[symbol] += quantity;
    investedAmount[symbol] += quantity * price;
}

void Portfolio::removeStock(string symbol, int quantity, double price) {
    cashBalance += quantity * price;
    holdings[symbol] -= quantity;
    investedAmount[symbol] -= quantity * price;

    if (holdings[symbol] <= 0) {
        holdings.erase(symbol);
        investedAmount.erase(symbol);
    }
}

double Portfolio::getTotalInvested() const {
    double total = 0;
    for (auto item : investedAmount) {
        total += item.second;
    }
    return total;
}

