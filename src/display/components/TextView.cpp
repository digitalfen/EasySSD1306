#include "display/components/TextView.h"

unsigned int TextView::render(Adafruit_SSD1306 *display)
{

    unsigned int nextTextView = 0;

    if (exec)
    {
        next = exec();
    }

    std::vector<String> newText;

    for (const auto &line : text)
    {
        String trimmedLine = line;
        trimmedLine.trim();

        if (trimmedLine.length() == 0)
        {
            newText.push_back(line);
            continue;
        }

        String currentLine = "";
        String word = "";
        int lineLength = 0;

        for (int i = 0; i < line.length(); ++i)
        {
            char c = line[i];

            if (c == ' ' || i == line.length() - 1)
            {
                if (i == line.length() - 1 && c != ' ')
                {
                    word += c;
                }

                if (currentLine.length() + word.length() + 1 > 18)
                {
                    if (currentLine.length() > 0)
                    {
                        newText.push_back(currentLine);
                    }
                    currentLine = word;
                }
                else
                {
                    if (currentLine.length() > 0)
                    {
                        currentLine += " ";
                    }
                    currentLine += word;
                }

                word = "";
            }
            else
            {
                word += c;
            }
        }

        if (currentLine.length() > 0)
        {
            newText.push_back(currentLine);
        }
    }

    text = newText;

    if (preset == TXT_VIEW_BORDERLESS_LEFT)
    {
        nextTextView = presetTextView1(display);
    }
    else if (preset == TXT_VIEW_BORDERLESS_CENTER)
    {
        nextTextView = presetTextView2(display);
    }
    else if (preset == TXT_VIEW_BORDERLESS_RIGHT)
    {
        nextTextView = presetTextView3(display);
    }
    else if (preset == TXT_VIEW_SOLID_BORDER_LEFT)
    {
        nextTextView = presetTextView4(display);
    }
    else if (preset == TXT_VIEW_SOLID_BORDER_CENTER)
    {
        nextTextView = presetTextView5(display);
    }
    else if (preset == TXT_VIEW_SOLID_BORDER_RIGHT)
    {
        nextTextView = presetTextView6(display);
    }
    else if (preset == TXT_VIEW_ROUNDED_BORDER_LEFT)
    {
        nextTextView = presetTextView7(display);
    }
    else if (preset == TXT_VIEW_ROUNDED_BORDER_CENTER)
    {
        nextTextView = presetTextView8(display);
    }
    else if (preset == TXT_VIEW_ROUNDED_BORDER_RIGHT)
    {
        nextTextView = presetTextView9(display);
    }
    else
    {
        display->clearDisplay();
        display->setTextSize(1);
        display->setCursor(0, display->height() / 2 - 4);
        display->print("Unknown TextView preset.");
        display->display();
        delay(2000);
        return 0; // Retorna 0 para indicar erro
    }

    display->display();

    return nextTextView;
}

void TextView::execute(std::function<unsigned int()> execute)
{
    this->exec = execute;
}

void TextView::nextComponent(unsigned int nextComponent)
{
    this->next = nextComponent;
}

// Preset sem borda, alinhado à esquerda
unsigned int TextView::presetTextView1(Adafruit_SSD1306 *display)
{
    display->clearDisplay();
    int startIndex = DisplayManager::selectedItem;
    startIndex = constrain(startIndex, 0, text.size() - maxVisibleLines);

    int spacing = 10;
    int yOffset = 8;
    int maxLineWidth = display->width() - 8;

    for (int i = 0; i < maxVisibleLines && (startIndex + i) < text.size(); ++i)
    {
        String line = text[startIndex + i];
        int16_t x1, y1;
        uint16_t textWidth, textHeight;

        // Checa a largura do texto
        display->getTextBounds(line.c_str(), 0, 0, &x1, &y1, &textWidth, &textHeight);

        while (textWidth > maxLineWidth)
        {
            int breakPoint = line.length() / 2;
            while (textWidth > maxLineWidth && breakPoint > 0)
            {
                breakPoint--;
                line = text[startIndex + i].substring(0, breakPoint);
                display->getTextBounds(line.c_str(), 0, 0, &x1, &y1, &textWidth, &textHeight);
            }

            display->setTextColor(SSD1306_WHITE);
            display->setCursor(8, yOffset);
            display->print(line.c_str());

            yOffset += spacing;

            line = text[startIndex + i].substring(breakPoint);
            display->getTextBounds(line.c_str(), 0, 0, &x1, &y1, &textWidth, &textHeight);
        }

        if (!line.isEmpty())
        {
            display->setTextColor(SSD1306_WHITE);
            display->setCursor(8, yOffset);
            display->print(line.c_str());
            yOffset += spacing;
        }
    }

    display->display();
    delay(200);

    if (DisplayManager::confirmItem)
    {
        return next;
    }

    return id;
}

unsigned int TextView::presetTextView2(Adafruit_SSD1306 *display)
{
    display->clearDisplay();
    int startIndex = DisplayManager::selectedItem;
    startIndex = constrain(startIndex, 0, text.size() - maxVisibleLines);

    int spacing = 10;
    int startY = (display->height() - (maxVisibleLines * spacing)) / 2;
    for (int i = 0; i < maxVisibleLines && (startIndex + i) < text.size(); ++i)
    {
        display->setTextColor(SSD1306_WHITE);
        int16_t x1, y1;
        uint16_t textWidth, textHeight;
        display->getTextBounds(text[startIndex + i].c_str(), 0, 0, &x1, &y1, &textWidth, &textHeight);
        int startX = (display->width() - textWidth) / 2;
        display->setCursor(startX, startY + i * spacing);
        display->print(text[startIndex + i].c_str());
    }

    display->display();
    delay(200);

    if (DisplayManager::confirmItem)
    {
        return next;
    }

    return id;
}

unsigned int TextView::presetTextView3(Adafruit_SSD1306 *display)
{
    display->clearDisplay();
    int startIndex = DisplayManager::selectedItem;
    startIndex = constrain(startIndex, 0, text.size() - maxVisibleLines);

    int spacing = 10;
    int startY = (display->height() - (maxVisibleLines * spacing)) / 2;
    for (int i = 0; i < maxVisibleLines && (startIndex + i) < text.size(); ++i)
    {
        display->setTextColor(SSD1306_WHITE);
        int16_t x1, y1;
        uint16_t textWidth, textHeight;
        display->getTextBounds(text[startIndex + i].c_str(), 0, 0, &x1, &y1, &textWidth, &textHeight);
        int startX = display->width() - textWidth - 8;
        display->setCursor(startX, startY + i * spacing);
        display->print(text[startIndex + i].c_str());
    }

    display->display();
    delay(200);

    if (DisplayManager::confirmItem)
    {
        return next;
    }

    return id;
}

unsigned int TextView::presetTextView4(Adafruit_SSD1306 *display)
{
    display->clearDisplay();
    int startIndex = DisplayManager::selectedItem;
    startIndex = constrain(startIndex, 0, text.size() - maxVisibleLines);

    display->drawRect(0, 0, display->width(), display->height(), SSD1306_WHITE);
    int spacing = 10;
    for (int i = 0; i < maxVisibleLines && (startIndex + i) < text.size(); ++i)
    {
        display->setTextColor(SSD1306_WHITE);
        display->setCursor(8, i * spacing + 8);
        display->print(text[startIndex + i].c_str());
    }

    display->display();
    delay(200);

    if (DisplayManager::confirmItem)
    {
        return next;
    }

    return id;
}

unsigned int TextView::presetTextView5(Adafruit_SSD1306 *display)
{
    display->clearDisplay();
    int startIndex = DisplayManager::selectedItem;
    startIndex = constrain(startIndex, 0, text.size() - maxVisibleLines);

    display->drawRect(0, 0, display->width(), display->height(), SSD1306_WHITE);
    int spacing = 10;
    int startY = (display->height() - (maxVisibleLines * spacing)) / 2;
    for (int i = 0; i < maxVisibleLines && (startIndex + i) < text.size(); ++i)
    {
        display->setTextColor(SSD1306_WHITE);
        int16_t x1, y1;
        uint16_t textWidth, textHeight;
        display->getTextBounds(text[startIndex + i].c_str(), 0, 0, &x1, &y1, &textWidth, &textHeight);
        int startX = (display->width() - textWidth) / 2;
        display->setCursor(startX, startY + i * spacing);
        display->print(text[startIndex + i].c_str());
    }

    display->display();
    delay(200);

    if (DisplayManager::confirmItem)
    {
        return next;
    }

    return id;
}

unsigned int TextView::presetTextView6(Adafruit_SSD1306 *display)
{
    display->clearDisplay();
    int startIndex = DisplayManager::selectedItem;
    startIndex = constrain(startIndex, 0, text.size() - maxVisibleLines);

    display->drawRect(0, 0, display->width(), display->height(), SSD1306_WHITE);
    int spacing = 10;
    int startY = (display->height() - (maxVisibleLines * spacing)) / 2;
    for (int i = 0; i < maxVisibleLines && (startIndex + i) < text.size(); ++i)
    {
        display->setTextColor(SSD1306_WHITE);
        int16_t x1, y1;
        uint16_t textWidth, textHeight;
        display->getTextBounds(text[startIndex + i].c_str(), 0, 0, &x1, &y1, &textWidth, &textHeight);
        int startX = display->width() - textWidth - 8;
        display->setCursor(startX, startY + i * spacing);
        display->print(text[startIndex + i].c_str());
    }

    display->display();
    delay(200);

    if (DisplayManager::confirmItem)
    {
        return next;
    }

    return id;
}

unsigned int TextView::presetTextView7(Adafruit_SSD1306 *display)
{
    display->clearDisplay();
    int startIndex = DisplayManager::selectedItem;
    startIndex = constrain(startIndex, 0, text.size() - maxVisibleLines);

    display->drawRoundRect(0, 0, display->width(), display->height(), 8, SSD1306_WHITE);
    int spacing = 10;
    for (int i = 0; i < maxVisibleLines && (startIndex + i) < text.size(); ++i)
    {
        display->setTextColor(SSD1306_WHITE);
        display->setCursor(8, i * spacing + 8);
        display->print(text[startIndex + i].c_str());
    }

    display->display();
    delay(200);

    if (DisplayManager::confirmItem)
    {
        return next;
    }

    return id;
}

unsigned int TextView::presetTextView8(Adafruit_SSD1306 *display)
{
    display->clearDisplay();
    int startIndex = DisplayManager::selectedItem;
    startIndex = constrain(startIndex, 0, text.size() - maxVisibleLines);

    display->drawRoundRect(0, 0, display->width(), display->height(), 8, SSD1306_WHITE);
    int spacing = 10;
    int startY = (display->height() - (maxVisibleLines * spacing)) / 2;
    for (int i = 0; i < maxVisibleLines && (startIndex + i) < text.size(); ++i)
    {
        display->setTextColor(SSD1306_WHITE);
        int16_t x1, y1;
        uint16_t textWidth, textHeight;
        display->getTextBounds(text[startIndex + i].c_str(), 0, 0, &x1, &y1, &textWidth, &textHeight);
        int startX = (display->width() - textWidth) / 2;
        display->setCursor(startX, startY + i * spacing);
        display->print(text[startIndex + i].c_str());
    }

    display->display();
    delay(200);

    if (DisplayManager::confirmItem)
    {
        return next;
    }

    return id;
}

unsigned int TextView::presetTextView9(Adafruit_SSD1306 *display)
{
    display->clearDisplay();
    int startIndex = DisplayManager::selectedItem;
    startIndex = constrain(startIndex, 0, text.size() - maxVisibleLines);

    display->drawRoundRect(0, 0, display->width(), display->height(), 8, SSD1306_WHITE);
    int spacing = 10;
    int startY = (display->height() - (maxVisibleLines * spacing)) / 2;
    for (int i = 0; i < maxVisibleLines && (startIndex + i) < text.size(); ++i)
    {
        display->setTextColor(SSD1306_WHITE);
        int16_t x1, y1;
        uint16_t textWidth, textHeight;
        display->getTextBounds(text[startIndex + i].c_str(), 0, 0, &x1, &y1, &textWidth, &textHeight);
        int startX = display->width() - textWidth - 8;

        display->setCursor(startX, startY + i * spacing);
        display->print(text[startIndex + i].c_str());
    }

    display->display();
    delay(200);

    if (DisplayManager::confirmItem)
    {
        return next;
    }

    return id;
}
