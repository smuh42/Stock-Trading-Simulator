#include "../include/GUIManager.h"
#include "../include/Exceptions.h"
#include "raylib.h"
#include <sstream>
#include <iomanip>
#include <cstdlib>

using namespace std;

static string toStr(double value, int decimals = 2) {
    stringstream ss;
    ss << fixed << setprecision(decimals) << value;
    return ss.str();
}

static string toStrLong(long long value) {
    stringstream ss;
    ss << value;
    return ss.str();
}

static string shortVolume(long long value) {
    string vol = toStrLong(value);

    if (vol.length() > 5) {
        vol = vol.substr(0, 5);
    }

    return vol;
}

GUIManager::GUIManager(TradingSystem* sys) {
    system = sys;
    selectedIndex = 0;
    scrollOffset = 0;
    quantityText = "";
    quantityActive = false;
    guiMessage = "Select a stock, enter quantity, then click BUY or SELL.";
}

bool GUIManager::isMouseOver(int x, int y, int width, int height) {
    Vector2 mouse = GetMousePosition();
    Rectangle rect = {(float)x, (float)y, (float)width, (float)height};
    return CheckCollisionPointRec(mouse, rect);
}

void GUIManager::drawButton(int x, int y, int width, int height, const char* text, bool hovered) {
    Color color = hovered ? Color{210, 230, 255, 255} : Color{230, 230, 230, 255};

    DrawRectangle(x, y, width, height, color);
    DrawRectangleLines(x, y, width, height, DARKGRAY);

    int textWidth = MeasureText(text, 20);
    DrawText(text, x + (width - textWidth) / 2, y + 12, 20, BLACK);
}

void GUIManager::handleQuantityInput() {
    if (!quantityActive) {
        return;
    }

    int key = GetCharPressed();

    while (key > 0) {
        if (key >= '0' && key <= '9' && quantityText.length() < 8) {
            quantityText += (char)key;
        }

        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE) && !quantityText.empty()) {
        quantityText.erase(quantityText.length() - 1);
    }
}

void GUIManager::drawStockList() {
    DrawText("Stocks", 25, 82, 24, BLACK);
    DrawRectangleLines(20, 115, 275, 500, GRAY);

    vector<Stock>& stocks = system->getStocks();

    int visibleRows = 20;
    int rowHeight = 24;

    float wheel = GetMouseWheelMove();

    if (isMouseOver(20, 115, 275, 500)) {
        if (wheel < 0 && scrollOffset + visibleRows < (int)stocks.size()) {
            scrollOffset++;
        }

        if (wheel > 0 && scrollOffset > 0) {
            scrollOffset--;
        }
    }

    if (IsKeyPressed(KEY_DOWN) && selectedIndex + 1 < (int)stocks.size()) {
        selectedIndex++;

        if (selectedIndex >= scrollOffset + visibleRows) {
            scrollOffset++;
        }
    }

    if (IsKeyPressed(KEY_UP) && selectedIndex > 0) {
        selectedIndex--;

        if (selectedIndex < scrollOffset) {
            scrollOffset--;
        }
    }

    DrawText("SYMBOL", 30, 123, 14, DARKGRAY);
    DrawText("PRICE", 92, 123, 14, DARKGRAY);
    DrawText("CHG%", 142, 123, 14, DARKGRAY);
    DrawText("VOL", 218, 123, 14, DARKGRAY);

    for (int i = 0; i < visibleRows; i++) {
        int index = scrollOffset + i;

        if (index >= (int)stocks.size()) {
            break;
        }

        int y = 145 + i * rowHeight;

        bool selected = index == selectedIndex;
        bool hover = isMouseOver(25, y, 260, rowHeight);

        if (selected) {
            DrawRectangle(25, y, 260, rowHeight, Color{190, 225, 255, 255});
        }
        else if (hover) {
            DrawRectangle(25, y, 260, rowHeight, Color{235, 235, 235, 255});
        }

        Color changeColor = stocks[index].getChangePercent() >= 0 ? DARKGREEN : RED;

        DrawText(stocks[index].getSymbol().c_str(), 30, y + 4, 18, BLACK);
        DrawText(toStr(stocks[index].getClose()).c_str(), 92, y + 4, 18, BLACK);
        DrawText((toStr(stocks[index].getChangePercent() * 100) + "%").c_str(),
                 142, y + 4, 18, changeColor);
        DrawText(shortVolume(stocks[index].getVolume()).c_str(), 218, y + 4, 18, BLACK);

        if (hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            selectedIndex = index;
        }
    }

    DrawText("Use mouse wheel or arrow keys", 25, 625, 15, DARKGRAY);
}

void GUIManager::drawStockDetails() {
    vector<Stock>& stocks = system->getStocks();

    if (stocks.empty()) {
        return;
    }

    Stock s = stocks[selectedIndex];

    DrawText("Selected Stock Details", 310, 82, 24, BLACK);
    DrawRectangleLines(300, 115, 390, 300, GRAY);

    int labelX = 320;
    int valueX = 450;
    int y = 140;
    int gap = 29;

    DrawText("SYMBOL", labelX, y, 20, BLACK);
    DrawText(s.getSymbol().c_str(), valueX, y, 20, BLACK);
    y += gap;

    DrawText("LDCP", labelX, y, 20, BLACK);
    DrawText(toStr(s.getLDCP()).c_str(), valueX, y, 20, BLACK);
    y += gap;

    DrawText("OPEN", labelX, y, 20, BLACK);
    DrawText(toStr(s.getOpen()).c_str(), valueX, y, 20, BLACK);
    y += gap;

    DrawText("HIGH", labelX, y, 20, BLACK);
    DrawText(toStr(s.getHigh()).c_str(), valueX, y, 20, BLACK);
    y += gap;

    DrawText("LOW", labelX, y, 20, BLACK);
    DrawText(toStr(s.getLow()).c_str(), valueX, y, 20, BLACK);
    y += gap;

    DrawText("CLOSE", labelX, y, 20, BLACK);
    DrawText(toStr(s.getClose()).c_str(), valueX, y, 20, BLACK);
    y += gap;

    DrawText("CHANGE", labelX, y, 20, BLACK);
    DrawText(toStr(s.getChange()).c_str(), valueX, y, 20,
             s.getChange() >= 0 ? DARKGREEN : RED);
    y += gap;

    DrawText("CHANGE %", labelX, y, 20, BLACK);
    DrawText((toStr(s.getChangePercent() * 100) + "%").c_str(),
             valueX, y, 20, s.getChangePercent() >= 0 ? DARKGREEN : RED);
    y += gap;

    DrawText("VOLUME", labelX, y, 20, BLACK);
    DrawText(toStrLong(s.getVolume()).c_str(), valueX, y, 20, BLACK);

    DrawText("Quantity", 310, 440, 20, BLACK);

    bool boxHover = isMouseOver(410, 430, 150, 42);

    if (boxHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        quantityActive = true;
    }
    else if (!boxHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        quantityActive = false;
    }

    DrawRectangle(410, 430, 150, 42, quantityActive ? Color{245, 250, 255, 255} : WHITE);
    DrawRectangleLines(410, 430, 150, 42, quantityActive ? BLUE : GRAY);
    DrawText(quantityText.c_str(), 420, 441, 22, BLACK);

    bool buyHover = isMouseOver(310, 495, 125, 45);
    drawButton(310, 495, 125, 45, "BUY", buyHover);

    if (buyHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        try {
            int quantity = quantityText.empty() ? 0 : atoi(quantityText.c_str());

            system->buyStock(s, quantity);
            guiMessage = system->getLastMessage();
            quantityText = "";
        }
        catch (TradingException& e) {
            guiMessage = e.what();
        }
    }

    bool sellHover = isMouseOver(455, 495, 125, 45);
    drawButton(455, 495, 125, 45, "SELL", sellHover);

    if (sellHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        try {
            int quantity = quantityText.empty() ? 0 : atoi(quantityText.c_str());

            system->sellStock(s, quantity);
            guiMessage = system->getLastMessage();
            quantityText = "";
        }
        catch (TradingException& e) {
            guiMessage = e.what();
        }
    }

    bool sortHover = isMouseOver(310, 555, 325, 45);
    drawButton(310, 555, 325, 45, "SHOW HIGH VOLUME STOCKS", sortHover);

    if (sortHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        system->mergeSortByVolume();
        system->buildTopGainers();

        selectedIndex = 0;
        scrollOffset = 0;

        guiMessage = "High-volume stocks are now shown first using merge sort.";
    }
}

void GUIManager::drawPortfolio() {
    Portfolio& p = system->getPortfolio();

    DrawText("Portfolio", 720, 82, 24, BLACK);
    DrawRectangleLines(710, 115, 450, 250, GRAY);

    DrawText(("Cash Balance: " + toStr(p.getCashBalance())).c_str(), 730, 140, 20, BLACK);
    DrawText(("Total Invested: " + toStr(p.getTotalInvested())).c_str(), 730, 172, 20, BLACK);

    DrawText("Holdings:", 730, 215, 20, BLACK);

    map<string, int> holdings = p.getHoldings();

    int y = 245;
    int count = 0;

    if (holdings.empty()) {
        DrawText("No shares purchased yet.", 730, y, 18, DARKGRAY);
    }
    else {
        for (auto item : holdings) {
            if (count >= 5) {
                break;
            }

            string row = item.first + " : " + to_string(item.second) + " shares";
            DrawText(row.c_str(), 730, y, 18, BLACK);

            y += 25;
            count++;
        }
    }

    DrawText("Recent Trades", 720, 395, 24, BLACK);
    DrawRectangleLines(710, 430, 450, 180, GRAY);

    vector<TradeRecord> history = system->getTradeHistory();

    y = 455;

    if (history.empty()) {
        DrawText("No trades yet.", 730, y, 18, DARKGRAY);
    }
    else {
        int start = history.size() > 5 ? history.size() - 5 : 0;

        for (int i = start; i < (int)history.size(); i++) {
            string row = history[i].getAction() + " " + history[i].getSymbol()
                       + " x" + to_string(history[i].getQuantity())
                       + " @ " + toStr(history[i].getPrice());

            DrawText(row.c_str(), 730, y, 18, BLACK);
            y += 26;
        }
    }
}

void GUIManager::drawTopGainers() {
    DrawText("TOP ADVANCERS", 720, 635, 24, BLACK);
    DrawRectangleLines(710, 665, 450, 80, GRAY);

    vector<Stock> gainers = system->getTopGainers(3);

    int y = 680;

    for (int i = 0; i < (int)gainers.size(); i++) {
        string row = gainers[i].getSymbol() + "   +" + toStr(gainers[i].getChangePercent() * 100) + "%";
        DrawText(row.c_str(), 735, y, 18, DARKGREEN);

        y += 22;
    }
}

void GUIManager::run() {
    InitWindow(1200, 760, "PSX Stock Trading Simulator");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        handleQuantityInput();

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("PSX Stock Trading Simulator", 25, 25, 34, BLACK);

        drawStockList();
        drawStockDetails();
        drawPortfolio();
        drawTopGainers();

        DrawRectangle(20, 710, 660, 35, Color{240, 240, 240, 255});
        DrawRectangleLines(20, 710, 660, 35, GRAY);
        DrawText(guiMessage.c_str(), 30, 719, 18, DARKBLUE);

        EndDrawing();
    }

    CloseWindow();
}