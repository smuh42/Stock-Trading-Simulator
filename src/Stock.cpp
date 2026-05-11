#include "../include/Stock.h"
#include <iostream>
using namespace std;

Stock::Stock() : MarketAsset("") {
    ldcp = openPrice = high = low = closePrice = change = changePercent = 0;
    volume = 0;
}

Stock::Stock(string sym, double ld, double op, double hi, double lo,
             double cl, double ch, double chp, long long vol) : MarketAsset(sym) {
    ldcp = ld;
    openPrice = op;
    high = hi;
    low = lo;
    closePrice = cl;
    change = ch;
    changePercent = chp;
    volume = vol;
}

void Stock::displayInfo() const {
    cout << *this << endl;  //calls << function
}

double Stock::getLDCP() const { return ldcp; }
double Stock::getOpen() const { return openPrice; }
double Stock::getHigh() const { return high; }
double Stock::getLow() const { return low; }
double Stock::getClose() const { return closePrice; }
double Stock::getChange() const { return change; }
double Stock::getChangePercent() const { return changePercent; }
long long Stock::getVolume() const { return volume; }

bool Stock::operator>(const Stock& other) const {
    return changePercent > other.changePercent;
}

bool Stock::operator<(const Stock& other) const {
    return changePercent < other.changePercent;
}

ostream& operator<<(ostream& out, const Stock& stock) {
    out << stock.symbol << " Close: " << stock.closePrice
        << " Change%: " << stock.changePercent
        << " Volume: " << stock.volume;
    return out;
}
