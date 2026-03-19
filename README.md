# 📈 Stock Trading Simulator
OOP-based stock trading simulator for semester project

## 📌 Project Overview
The **Stock Trading Simulator** is a C++ based Object Oriented Programming (OOP) project developed.

This system simulates a basic stock trading environment where users can:
- place buy and sell orders
- match orders automatically
- track executed trades
- manage a portfolio
- undo the most recent trade

---

## 🎯 Features Implemented

- User Buy Order Placement  
- User Sell Order Placement  
- Market Buy/Sell Liquidity  
- Automatic Order Matching  
- Trade Execution & Recording  
- Trade History Display  
- Trading Session Summary  
- Portfolio Management  
- Undo Last Trade  
- Exception Handling  
- Menu-driven Console Interface  

---

## 🧠 OOP Concepts Used

- Encapsulation  
- Inheritance  
- Polymorphism  
- Abstraction  
- Exception Handling  

---

## 🧱 System Architecture

Main Classes:

- `Order` (Abstract Base Class)  
- `BuyOrder` (Derived)  
- `SellOrder` (Derived)  
- `Portfolio`  
- `TradeRecord`  
- `UndoRecord`  
- `TradingSystem`  

---

## ⚙️ Data Structures Used

- `priority_queue` → order matching  
- `vector` → trade history  
- `stack` → undo functionality  

---

## ⚠️ Validation & Exceptions

- Buy rejected if insufficient cash  
- Sell rejected if insufficient shares  
- Custom exceptions handle errors  

---

## 📊 Trade Tracking

Each trade stores:
- timestamp  
- buy order ID  
- sell order ID  
- price  
- quantity  

System calculates:
- total trading volume  
- average price  
- number of trades  

---

## 💼 Portfolio Management

Displays:
- cash balance  
- reserved cash  
- shares owned  
- reserved shares  
- total equity  
- profit/loss  

---

## 🔄 Undo Functionality

- Reverses last trade  
- Restores portfolio  
- Restores orders  
