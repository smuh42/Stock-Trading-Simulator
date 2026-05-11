#include "../include/TradeRecord.h"
#include <sstream>
using namespace std;
/*
TradeRecord::TradeRecord() {
    action = "";
    symbol = "";
    quantity = 0;
    price = 0;
    totalAmount = 0;
    timestamp = "";
}
*/

TradeRecord::TradeRecord(string act, string sym, int qty, double pr, string ts) {
    action = act;
    symbol = sym;
    quantity = qty;
    price = pr;
    totalAmount = qty * pr;
    timestamp = ts;
}

string TradeRecord::getAction() const { return action; }
string TradeRecord::getSymbol() const { return symbol; }
int TradeRecord::getQuantity() const { return quantity; }
double TradeRecord::getPrice() const { return price; }
double TradeRecord::getTotalAmount() const { return totalAmount; }
string TradeRecord::getTimestamp() const { return timestamp; }

string TradeRecord::toCSV() const {
    stringstream ss;
    ss << action << "," << symbol << "," << quantity << "," << price << "," << totalAmount << "," << timestamp;
    return ss.str();
}
