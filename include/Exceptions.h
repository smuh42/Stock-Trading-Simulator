#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>
using namespace std;

class TradingException : public runtime_error {
public:
    TradingException(const string& msg) : runtime_error(msg) {}
};

class InsufficientFundsException : public TradingException {
public:
    InsufficientFundsException()
        : TradingException("Insufficient funds to complete purchase.") {}
};

class InvalidQuantityException : public TradingException {
public:
    InvalidQuantityException()
        : TradingException("Invalid quantity entered.") {}
};

class InsufficientSharesException : public TradingException {
public:
    InsufficientSharesException()
        : TradingException("Not enough shares available to sell.") {}
};

#endif