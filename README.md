# 📈 PSX Stock Trading Simulator

GUI-based PSX stock trading simulator developed in C++ using Object Oriented Programming (OOP) concepts and the Raylib graphics library.

---

# 📌 Project Overview

The **PSX Stock Trading Simulator** is a desktop-based stock market simulation system developed as an OOP semester project.

The simulator creates a simplified Pakistan Stock Exchange (PSX) trading environment where users can:

- view stock market data from CSV files
- buy shares
- sell shares
- manage a portfolio
- track recent trades
- sort stocks by volume
- view top market advancers
- interact through a graphical user interface (GUI)

The project demonstrates practical implementation of:
- OOP concepts
- STL data structures
- algorithms
- file handling
- exception handling
- GUI development

---

# 🎯 Features Implemented

- GUI-based Interface using Raylib
- CSV Stock Market Data Loading
- Scrollable Stock List
- Selected Stock Details Panel
- Portfolio Management
- Buy Stock Functionality
- Sell Stock Functionality
- Recent Trade History
- Trade History CSV Export
- Top Advancers Section
- Merge Sort by Volume
- Quantity Input Handling
- Dynamic GUI Updates
- Exception Handling

---

# 🧠 OOP Concepts Used

- Encapsulation
- Inheritance
- Polymorphism
- Abstraction
- Composition
- Exception Handling

---

# 🧱 Main Classes

- `MarketAsset` (Abstract Base Class)
- `Stock`
- `Portfolio`
- `TradeRecord`
- `TradingSystem`
- `GUIManager`
- `CSVLoader`
- `TradingException`

---

# ⚙️ Data Structures & Algorithms Used

| Data Structure / Algorithm | Used In | Purpose |
|---|---|---|
| `vector<Stock>` | `TradingSystem::stocks` | Stores all stock market data |
| `vector<TradeRecord>` | `TradingSystem::tradeHistory` | Stores recent trade history |
| `priority_queue<Stock>` | `TradingSystem::topGainers` | Displays top market advancers |
| `map<string,int>` | `Portfolio::holdings` | Stores shares owned by user |
| `map<string,double>` | `Portfolio::investedAmount` | Stores invested amount per stock |
| `Merge Sort` | `mergeSortByVolume()` | Sorts stocks by trading volume |
| `File Handling` | `appendTradeToFile()` | Saves trade history into CSV |
| `stringstream` | `TradeRecord::toCSV()` | Converts trade object into CSV format |

---

# 🖥️ GUI Components

The simulator interface includes:

- Stock List Panel
- Stock Details Panel
- Portfolio Section
- Recent Trades Section
- Top Advancers Section
- Quantity Input Box
- Buy Button
- Sell Button
- High Volume Sorting Button
- Status Message Bar

---

# 📊 Stock Data Displayed

Each stock displays:

- Symbol
- LDCP
- Open Price
- High Price
- Low Price
- Close Price
- Change
- Change Percentage
- Volume

---

# 📂 CSV File Handling

Stock market data is loaded from CSV files using the `CSVLoader` class.

Trade history is automatically saved into:

```text
records/trade_history.csv
