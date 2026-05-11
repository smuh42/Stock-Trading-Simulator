#ifndef STOCK_H
#define STOCK_H

#include "MarketAsset.h"
#include <iostream>
using namespace std;

class Stock : public MarketAsset {
private:
    double ldcp;
    double openPrice;
    double high;
    double low;
    double closePrice;
    double change;
    double changePercent;
    long long volume;

public:
    Stock();
    Stock(string sym, double ld, double op, double hi, double lo,
          double cl, double ch, double chp, long long vol);

    void displayInfo() const override;

    double getLDCP() const;
    double getOpen() const;
    double getHigh() const;
    double getLow() const;
    double getClose() const;
    double getChange() const;
    double getChangePercent() const;
    long long getVolume() const;

    bool operator>(const Stock& other) const;
    bool operator<(const Stock& other) const;

    friend ostream& operator<<(ostream& out, const Stock& stock);
};

#endif
