#ifndef MARKETASSET_H
#define MARKETASSET_H

#include <string>
using namespace std;

class MarketAsset {
protected:
    string symbol;

public:
    MarketAsset(string symbol = "");
    virtual ~MarketAsset();

    string getSymbol() const;
    void setSymbol(string symbl);

    virtual void displayInfo() const = 0;
};

#endif


//MarketAsset is a general parent class for anything that can be traded in the market