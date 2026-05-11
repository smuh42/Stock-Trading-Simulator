#ifndef TRADERECORD_H
#define TRADERECORD_H

#include <string>
using namespace std;

class TradeRecord {
private:
    string action;
    string symbol;
    int quantity;
    double price;
    double totalAmount;
    string timestamp;

public:
    TradeRecord();
    TradeRecord(string act, string sym, int qty, double pr, string ts);

    string getAction() const;
    string getSymbol() const;
    int getQuantity() const;
    double getPrice() const;
    double getTotalAmount() const;
    string getTimestamp() const;

    string toCSV() const;
};

#endif
