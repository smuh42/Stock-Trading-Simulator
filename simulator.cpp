#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <stdexcept>
#include <sstream>
#include <ctime>

using namespace std;

// ========================= Utility =========================
string getCurrentTimestamp() {
    time_t now = time(0);
    char* dt = ctime(&now);
    string ts = dt;

    if (!ts.empty() && ts[ts.length() - 1] == '\n') {
        ts.erase(ts.length() - 1);
    }

    return ts;
}

// ========================= Custom Exceptions =========================
class TradingException : public runtime_error {
public:
    TradingException(const string& message) : runtime_error(message) {}
};

class InsufficientFundsException : public TradingException {
public:
    InsufficientFundsException() : TradingException("Order rejected: Insufficient cash balance.") {}
};

class InsufficientSharesException : public TradingException {
public:
    InsufficientSharesException() : TradingException("Order rejected: Insufficient shares available.") {}
};

class UndoException : public TradingException {
public:
    UndoException() : TradingException("Undo failed: No executed trade available.") {}
};

// ========================= Order Base Class =========================
class Order {
protected:
    int orderId;
    double price;
    int quantity;
    string timestamp;
    bool userOrder;

public:
    Order(int id = 0, double p = 0, int q = 0, bool isUser = false)
        : orderId(id), price(p), quantity(q), timestamp(getCurrentTimestamp()), userOrder(isUser) {}

    virtual ~Order() {}

    int getOrderId() const { return orderId; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }
    string getTimestamp() const { return timestamp; }
    bool isUser() const { return userOrder; }

    void reduceQuantity(int q) { quantity -= q; }
    void increaseQuantity(int q) { quantity += q; }

    virtual string getType() const = 0;
};

class BuyOrder : public Order {
public:
    BuyOrder(int id = 0, double p = 0, int q = 0, bool isUser = false)
        : Order(id, p, q, isUser) {}

    string getType() const override { return "Buy"; }
};

class SellOrder : public Order {
public:
    SellOrder(int id = 0, double p = 0, int q = 0, bool isUser = false)
        : Order(id, p, q, isUser) {}

    string getType() const override { return "Sell"; }
};

// ========================= Trade Record =========================
class TradeRecord {
private:
    string timestamp;
    int buyOrderId;
    int sellOrderId;
    double price;
    int quantity;

public:
    TradeRecord(string ts = "", int bId = 0, int sId = 0, double p = 0, int q = 0)
        : timestamp(ts), buyOrderId(bId), sellOrderId(sId), price(p), quantity(q) {}

    string getTimestamp() const { return timestamp; }
    int getBuyOrderId() const { return buyOrderId; }
    int getSellOrderId() const { return sellOrderId; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }

    void display() const {
        cout << timestamp << " | "
             << "BuyID: " << buyOrderId << " | "
             << "SellID: " << sellOrderId << " | "
             << "Price: " << price << " | "
             << "Qty: " << quantity << endl;
    }
};

// ========================= Portfolio =========================
class Portfolio {
private:
    double initialCash;
    double cashBalance;
    double reservedCash;
    int sharesOwned;
    int reservedShares;
    double lastTradePrice;

public:
    Portfolio(double initial = 10000.0) {
        initialCash = initial;
        cashBalance = initial;
        reservedCash = 0.0;
        sharesOwned = 100;
        reservedShares = 0;
        lastTradePrice = 100.0;
    }

    double getCashBalance() const { return cashBalance; }
    double getReservedCash() const { return reservedCash; }
    int getSharesOwned() const { return sharesOwned; }
    int getReservedShares() const { return reservedShares; }
    double getLastTradePrice() const { return lastTradePrice; }

    double getAvailableCash() const {
        return cashBalance;
    }

    int getAvailableShares() const {
        return sharesOwned - reservedShares;
    }

    void reserveBuy(double price, int quantity) {
        double total = price * quantity;

        if (cashBalance < total) {
            throw InsufficientFundsException();
        }

        cashBalance -= total;
        reservedCash += total;
    }

    void reserveSell(int quantity) {
        if (getAvailableShares() < quantity) {
            throw InsufficientSharesException();
        }

        reservedShares += quantity;
    }

    void executeBuy(double limitPrice, double tradePrice, int quantity) {
        reservedCash -= limitPrice * quantity;
        cashBalance += (limitPrice - tradePrice) * quantity;
        sharesOwned += quantity;
        lastTradePrice = tradePrice;
    }

    void executeSell(double tradePrice, int quantity) {
        reservedShares -= quantity;
        sharesOwned -= quantity;
        cashBalance += tradePrice * quantity;
        lastTradePrice = tradePrice;
    }

    void undoBuy(double limitPrice, double tradePrice, int quantity) {
        sharesOwned -= quantity;
        cashBalance -= (limitPrice - tradePrice) * quantity;
        reservedCash += limitPrice * quantity;
    }

    void undoSell(double tradePrice, int quantity) {
        cashBalance -= tradePrice * quantity;
        sharesOwned += quantity;
        reservedShares += quantity;
    }

    double totalEquity() const {
        return cashBalance + reservedCash + (sharesOwned * lastTradePrice);
    }

    double overallProfitLoss() const {
        return totalEquity() - initialCash;
    }

    void displayStatement() const {
        cout << "\n========== Portfolio Statement ==========\n";
        cout << "Cash Balance     : " << cashBalance << endl;
        cout << "Reserved Cash    : " << reservedCash << endl;
        cout << "Shares Owned     : " << sharesOwned << endl;
        cout << "Reserved Shares  : " << reservedShares << endl;
        cout << "Last Trade Price : " << lastTradePrice << endl;
        cout << "Total Equity     : " << totalEquity() << endl;
        cout << "Overall P/L      : " << overallProfitLoss() << endl;
        cout << "=========================================\n";
    }
};

// ========================= Comparators =========================
struct BuyComparator {
    bool operator()(BuyOrder a, BuyOrder b) {
        return a.getPrice() < b.getPrice(); // highest price gets priority
    }
};

struct SellComparator {
    bool operator()(SellOrder a, SellOrder b) {
        return a.getPrice() > b.getPrice(); // lowest price gets priority
    }
};

// ========================= Undo Record =========================
struct UndoRecord {
    TradeRecord trade;
    double buyLimitPrice;
    double sellPrice;
    bool buyWasUser;
    bool sellWasUser;
};

// ========================= Trading System =========================
class TradingSystem {
private:
    priority_queue<BuyOrder, vector<BuyOrder>, BuyComparator> buyBook;
    priority_queue<SellOrder, vector<SellOrder>, SellComparator> sellBook;

    vector<TradeRecord> tradeHistory;
    stack<UndoRecord> undoStack;

    Portfolio portfolio;
    int nextOrderId;
    int totalVolume;
    double totalTradeValue;

public:
    TradingSystem() : portfolio(10000.0) {
        nextOrderId = 1;
        totalVolume = 0;
        totalTradeValue = 0.0;
    }

    void placeUserBuy(double price, int quantity) {
        portfolio.reserveBuy(price, quantity);
        BuyOrder order(nextOrderId++, price, quantity, true);
        buyBook.push(order);
        cout << "User Buy Order placed successfully. Order ID: " << order.getOrderId() << endl;
    }

    void placeUserSell(double price, int quantity) {
        portfolio.reserveSell(quantity);
        SellOrder order(nextOrderId++, price, quantity, true);
        sellBook.push(order);
        cout << "User Sell Order placed successfully. Order ID: " << order.getOrderId() << endl;
    }

    void placeMarketBuy(double price, int quantity) {
        BuyOrder order(nextOrderId++, price, quantity, false);
        buyBook.push(order);
        cout << "Market Buy Liquidity added. Order ID: " << order.getOrderId() << endl;
    }

    void placeMarketSell(double price, int quantity) {
        SellOrder order(nextOrderId++, price, quantity, false);
        sellBook.push(order);
        cout << "Market Sell Liquidity added. Order ID: " << order.getOrderId() << endl;
    }

    void matchOrders() {
        bool matchedAny = false;

        while (!buyBook.empty() && !sellBook.empty()) {
            BuyOrder buy = buyBook.top();
            SellOrder sell = sellBook.top();

            if (buy.getPrice() < sell.getPrice()) {
                break;
            }

            matchedAny = true;

            buyBook.pop();
            sellBook.pop();

            int matchedQty;
            if (buy.getQuantity() < sell.getQuantity()) {
                matchedQty = buy.getQuantity();
            } else {
                matchedQty = sell.getQuantity();
            }

            double tradePrice = sell.getPrice();
            string ts = getCurrentTimestamp();

            if (buy.isUser()) {
                portfolio.executeBuy(buy.getPrice(), tradePrice, matchedQty);
            }

            if (sell.isUser()) {
                portfolio.executeSell(tradePrice, matchedQty);
            }

            TradeRecord trade(ts, buy.getOrderId(), sell.getOrderId(), tradePrice, matchedQty);
            tradeHistory.push_back(trade);

            UndoRecord record;
            record.trade = trade;
            record.buyLimitPrice = buy.getPrice();
            record.sellPrice = sell.getPrice();
            record.buyWasUser = buy.isUser();
            record.sellWasUser = sell.isUser();

            undoStack.push(record);

            totalVolume += matchedQty;
            totalTradeValue += tradePrice * matchedQty;

            buy.reduceQuantity(matchedQty);
            sell.reduceQuantity(matchedQty);

            if (buy.getQuantity() > 0) {
                buyBook.push(buy);
            }

            if (sell.getQuantity() > 0) {
                sellBook.push(sell);
            }

            cout << "Trade Executed -> BuyID: " << trade.getBuyOrderId()
                 << ", SellID: " << trade.getSellOrderId()
                 << ", Price: " << trade.getPrice()
                 << ", Qty: " << trade.getQuantity() << endl;
        }

        if (!matchedAny) {
            cout << "No matching orders found.\n";
        }
    }

    void undoLastTrade() {
        if (undoStack.empty()) {
            throw UndoException();
        }

        UndoRecord last = undoStack.top();
        undoStack.pop();

        int qty = last.trade.getQuantity();
        double tradePrice = last.trade.getPrice();

        if (last.buyWasUser) {
            portfolio.undoBuy(last.buyLimitPrice, tradePrice, qty);
        }

        if (last.sellWasUser) {
            portfolio.undoSell(tradePrice, qty);
        }

        BuyOrder restoredBuy(last.trade.getBuyOrderId(), last.buyLimitPrice, qty, last.buyWasUser);
        SellOrder restoredSell(last.trade.getSellOrderId(), last.sellPrice, qty, last.sellWasUser);

        buyBook.push(restoredBuy);
        sellBook.push(restoredSell);

        totalVolume -= qty;
        totalTradeValue -= tradePrice * qty;

        if (!tradeHistory.empty()) {
            tradeHistory.pop_back();
        }

        cout << "Last trade undone successfully.\n";
    }

    void displayTradeHistory() const {
        if (tradeHistory.empty()) {
            cout << "No executed trades yet.\n";
            return;
        }

        cout << "\n==================== Executed Trades ====================\n";
        cout << "Timestamp | BuyID | SellID | Price | Qty\n";

        for (int i = 0; i < tradeHistory.size(); i++) {
            tradeHistory[i].display();
        }

        cout << "=========================================================\n";
    }

    void displaySummary() const {
        cout << "\n========== Trading Session Summary ==========\n";
        cout << "Total Trading Volume : " << totalVolume << endl;

        if (totalVolume > 0) {
            cout << "Average Traded Price : " << totalTradeValue / totalVolume << endl;
        } else {
            cout << "Average Traded Price : 0" << endl;
        }

        cout << "Executed Trades      : " << tradeHistory.size() << endl;
        cout << "=============================================\n";
    }

    void displayPortfolio() const {
        portfolio.displayStatement();
    }
};

// ========================= Menu =========================
void displayMenu() {
    cout << "\n========= Stock Trading Simulator =========\n";
    cout << "1. Place User Buy Order\n";
    cout << "2. Place User Sell Order\n";
    cout << "3. Add Market Buy Liquidity\n";
    cout << "4. Add Market Sell Liquidity\n";
    cout << "5. Match Orders\n";
    cout << "6. View Executed Trades\n";
    cout << "7. View Session Summary\n";
    cout << "8. View Portfolio Statement\n";
    cout << "9. Undo Last Trade\n";
    cout << "0. Exit\n";
    cout << "Enter choice: ";
}

int main() {
    TradingSystem system;
    int choice;

    do {
        displayMenu();
        cin >> choice;

        try {
            if (choice == 1) {
                double price;
                int quantity;
                cout << "Enter buy price: ";
                cin >> price;
                cout << "Enter quantity: ";
                cin >> quantity;
                system.placeUserBuy(price, quantity);
            }
            else if (choice == 2) {
                double price;
                int quantity;
                cout << "Enter sell price: ";
                cin >> price;
                cout << "Enter quantity: ";
                cin >> quantity;
                system.placeUserSell(price, quantity);
            }
            else if (choice == 3) {
                double price;
                int quantity;
                cout << "Enter market buy price: ";
                cin >> price;
                cout << "Enter quantity: ";
                cin >> quantity;
                system.placeMarketBuy(price, quantity);
            }
            else if (choice == 4) {
                double price;
                int quantity;
                cout << "Enter market sell price: ";
                cin >> price;
                cout << "Enter quantity: ";
                cin >> quantity;
                system.placeMarketSell(price, quantity);
            }
            else if (choice == 5) {
                system.matchOrders();
            }
            else if (choice == 6) {
                system.displayTradeHistory();
            }
            else if (choice == 7) {
                system.displaySummary();
            }
            else if (choice == 8) {
                system.displayPortfolio();
            }
            else if (choice == 9) {
                system.undoLastTrade();
            }
            else if (choice == 0) {
                cout << "Exiting system...\n";
            }
            else {
                cout << "Invalid choice.\n";
            }
        }
        catch (TradingException& e) {
            cout << e.what() << endl;
        }
        catch (...) {
            cout << "An unexpected error occurred.\n";
        }

    } while (choice != 0);

    return 0;
}