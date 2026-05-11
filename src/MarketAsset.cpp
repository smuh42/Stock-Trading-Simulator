#include "../include/MarketAsset.h"

MarketAsset::MarketAsset(string symbol) {
    this->symbol = symbol;
}

MarketAsset::~MarketAsset() {}

string MarketAsset::getSymbol() const {
    return symbol;
}

void MarketAsset::setSymbol(string symbl) {
    symbol = symbl;
}
