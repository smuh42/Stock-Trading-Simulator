#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include "TradingSystem.h"
#include <string>

using namespace std;

class GUIManager {
private:
    TradingSystem* system;

    int selectedIndex;
    int scrollOffset;

    string quantityText;
    bool quantityActive;

    string guiMessage;

    bool isMouseOver(int x, int y, int width, int height);

    void drawButton(
        int x,
        int y,
        int width,
        int height,
        const char* text,
        bool hovered
    );

    void handleQuantityInput();

    void drawStockList();
    void drawStockDetails();
    void drawPortfolio();
    void drawTopGainers();

public:
    GUIManager(TradingSystem* sys);

    void run();
};

#endif