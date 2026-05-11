# 📈 PSX Stock Trading Simulator

GUI-based PSX stock trading simulator developed in C++ using Object Oriented Programming (OOP) concepts and the Raylib graphics library.

---

# 📌 Project Overview

The **PSX Stock Trading Simulator** is a desktop-based stock market simulation system developed as an OOP semester project.

The simulator creates a simplified Pakistan Stock Exchange (PSX) trading environment where users can:

- view stock market data from CSV files
- buy shares
- manage a portfolio
- track recent trades
- undo previous transactions
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
- Undo Last Buy
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

# ⚙️ Data Structures Used

| Data Structure | Purpose |
|---|---|
| `vector` | Stock storage and trade history |
| `stack` | Undo functionality |
| `priority_queue` | Top advancers |
| `map` | Portfolio holdings and investments |

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
- Undo Button
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

## Build

```bash
g++ src/*.cpp -Iinclude -o StockTradingSimulator.exe -lraylib -lopengl32 -lgdi32 -lwinmm
```


## Run

```bash
StockTradingSimulator.exe
```

