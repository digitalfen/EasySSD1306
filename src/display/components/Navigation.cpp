#include "display/components/Navigation.h"
#include "display/DisplayManager.h"

unsigned int Navigation::render(Adafruit_SSD1306 *display)
{

    unsigned int nextView = 0;

    if (preset == NAV_CURSOR_LIST)
    {
        nextView = presetNavigation1(display);
    }
    else if (preset == NAV_HIGHLIGHT_LIST)
    {
        nextView = presetNavigation2(display);
    }
    else if (preset == NAV_VERTICAL_SELECTOR)
    {
        nextView = presetNavigation3(display);
    }
    else if (preset == NAV_HORIZONTAL_SELECTOR)
    {
        nextView = presetNavigation4(display);
    }

    else
    {
        display->clearDisplay();
        display->setTextSize(1);
        display->setCursor(0, display->height() / 2 - 4);
        display->print("Unknown Navigation preset.");
        display->display();
        delay(2000);
        return 0;
    }

    return nextView;
}

unsigned int Navigation::presetNavigation1(Adafruit_SSD1306 *display)
{
    if (DisplayManager::selectedItem < 0)
    {
        DisplayManager::selectedItem = options.size() - 1;
    }
    else if (DisplayManager::selectedItem >= options.size())
    {
        DisplayManager::selectedItem = 0;
    }

    display->clearDisplay();

    int maxItemsOnScreen = 5;
    int spacing = 10;
    int startY = (display->height() - (maxItemsOnScreen * spacing)) / 2;

    int startIndex = DisplayManager::selectedItem - (maxItemsOnScreen / 2);
    if (startIndex + maxItemsOnScreen > options.size())
    {
        startIndex = options.size() - maxItemsOnScreen;
    }
    startIndex = max(0, startIndex);

    int endIndex = min((int)options.size(), startIndex + maxItemsOnScreen);

    int index = 0;
    auto it = options.begin();
    std::advance(it, startIndex);
    for (int i = startIndex; i < endIndex; ++i, ++it)
    {
        String name = it->second;

        if (name.length() > 19)
        {
            name = name.substring(0, 17) + "..";
        }

        if (i == DisplayManager::selectedItem)
        {
            display->setCursor(0, startY + index * spacing);
            display->print(">");
        }
        else
        {
            display->setTextColor(SSD1306_WHITE);
        }

        display->setCursor(10, startY + index * spacing);
        display->print(name.c_str());

        index++;
    }

    display->display();
    delay(50);

    auto itt = options.begin();
    std::advance(itt, DisplayManager::selectedItem);
    int optionState = itt->first;

    unsigned int nextState = id;

    if (DisplayManager::confirmItem)
    {
        nextState = optionState;
    }

    return nextState;
}

unsigned int Navigation::presetNavigation2(Adafruit_SSD1306 *display)
{
    if (DisplayManager::selectedItem < 0)
    {
        DisplayManager::selectedItem = options.size() - 1;
    }
    else if (DisplayManager::selectedItem >= options.size())
    {
        DisplayManager::selectedItem = 0;
    }

    display->clearDisplay();

    int maxItemsOnScreen = 5;
    int spacing = 10;
    int startY = (display->height() - (maxItemsOnScreen * spacing)) / 2;

    int startIndex = DisplayManager::selectedItem - (maxItemsOnScreen / 2);
    if (startIndex + maxItemsOnScreen > options.size())
    {
        startIndex = options.size() - maxItemsOnScreen;
    }
    startIndex = max(0, startIndex);

    int endIndex = min((int)options.size(), startIndex + maxItemsOnScreen);

    int index = 0;
    auto it = options.begin();
    std::advance(it, startIndex);
    for (int i = startIndex; i < endIndex; ++i, ++it)
    {
        String name = it->second;

        if (name.length() > 19)
        {
            name = name.substring(0, 17) + "...";
        }

        if (i == DisplayManager::selectedItem)
        {
            display->setTextColor(SSD1306_BLACK, SSD1306_WHITE);
            display->setCursor(0, startY + index * spacing);
            display->print(" ");
        }
        else
        {
            display->setTextColor(SSD1306_WHITE);
        }

        display->setCursor(10, startY + index * spacing);
        display->print(name.c_str());

        index++;
    }

    display->display();
    delay(50);

    auto itt = options.begin();
    std::advance(itt, DisplayManager::selectedItem);
    int optionState = itt->first;

    unsigned int nextState = id;

    if (DisplayManager::confirmItem)
    {
        Serial.println(optionState);
        nextState = optionState;
    }

    return nextState;
}

unsigned int Navigation::presetNavigation3(Adafruit_SSD1306 *display)
{
    if (DisplayManager::selectedItem < 0)
    {
        DisplayManager::selectedItem = options.size() - 1;
    }
    else if (DisplayManager::selectedItem >= options.size())
    {
        DisplayManager::selectedItem = 0;
    }

    display->clearDisplay();

    int maxItemsOnScreen = 1;
    int spacing = 12;
    int startY = (display->height() - (maxItemsOnScreen * spacing)) / 2;

    int startIndex = DisplayManager::selectedItem;
    int endIndex = startIndex + 1;

    auto it = options.begin();
    std::advance(it, startIndex);
    String name = it->second;

    if (name.length() > 19)
    {
        name = name.substring(0, 17) + "...";
        /
    }

    display->setTextColor(SSD1306_WHITE);
    display->setCursor(20, startY);
    display->print(name.c_str());

    if (startIndex > 0)
    {
        display->setTextColor(SSD1306_WHITE);
        display->setCursor(0, startY - 20);
        display->print("/\\");
    }
    if (startIndex < options.size() - 1)
    {
        display->setTextColor(SSD1306_WHITE);
        display->setCursor(0, startY + 20);
        display->print("\\/");
    }

    display->display();
    delay(150);

    auto itt = options.begin();
    std::advance(itt, DisplayManager::selectedItem);
    int optionState = itt->first;

    unsigned int nextState = id;

    if (DisplayManager::confirmItem)
    {
        Serial.println(optionState);
        nextState = optionState;
    }

    return nextState;
}

unsigned int Navigation::presetNavigation4(Adafruit_SSD1306 *display)
{
    if (DisplayManager::selectedItem < 0)
    {
        DisplayManager::selectedItem = options.size() - 1;
    }
    else if (DisplayManager::selectedItem >= options.size())
    {
        DisplayManager::selectedItem = 0;
    }

    display->clearDisplay();

    int startIndex = DisplayManager::selectedItem;

    auto it = options.begin();
    std::advance(it, startIndex);
    String name = it->second;

    if (name.length() > 19)
    {
        name = name.substring(0, 17) + "...";
    }

    int16_t x1, y1;
    uint16_t textWidth, textHeight;
    display->getTextBounds(name.c_str(), 0, 0, &x1, &y1, &textWidth, &textHeight);

    int centerX = (display->width() - textWidth) / 2;

    display->setTextColor(SSD1306_WHITE);
    display->setCursor(centerX, 20);
    display->print(name.c_str());

    if (startIndex > 0)
    {
        display->setTextColor(SSD1306_WHITE);
        display->setCursor(10, 20);
        display->print("<");
    }
    if (startIndex < options.size() - 1)
    {
        display->setTextColor(SSD1306_WHITE);
        display->setCursor(display->width() - 10, 20);
        display->print(">");
    }

    display->display();
    delay(150);

    auto itt = options.begin();
    std::advance(itt, DisplayManager::selectedItem);
    int optionState = itt->first;

    unsigned int nextState = id;

    if (DisplayManager::confirmItem)
    {
        Serial.println(optionState);
        nextState = optionState;
    }
    return nextState;
}
