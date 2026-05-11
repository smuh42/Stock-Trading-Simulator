#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include <map>
#include <string>
using namespace std;

class Portfolio {
private:
    double cashBalance;
    map<string, int> holdings;
    map<string, double> investedAmount;

public:
    Portfolio(double cash = 100000.0);
    ~Portfolio();

    double getCashBalance() const;
    int getShares(string symbol) const;
    double getInvestedAmount(string symbol) const;
    map<string, int> getHoldings() const;

    void addStock(string symbol, int quantity, double price);
    void removeStock(string symbol, int quantity, double price);

    double getTotalInvested() const;
    
};

#endif
