#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
using namespace std;

class TradingException : public runtime_error {
public:
    TradingException(const string& msg) : runtime_error(msg) {}
};

class InsufficientFundsException : public TradingException {
public:
    InsufficientFundsException() : TradingException("Insufficient funds for this purchase.") {}
};

class InvalidQuantityException : public TradingException {
public:
    InvalidQuantityException() : TradingException("Quantity must be a positive number.") {}
};

class EmptyUndoStackException : public TradingException {
public:
    EmptyUndoStackException() : TradingException("No trade available to undo.") {}
};

#endif
