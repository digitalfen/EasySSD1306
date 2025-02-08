#include "display/components/Alert.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

unsigned int Alert::render(Adafruit_SSD1306 *display)
{
    unsigned int nextView = 0;

    display->clearDisplay();

    if (preset == ALERT_DEFAULT)
    {
        nextView = preset1(display);
    }
    else if (preset == ALERT_WITH_BORDERS)
    {
        nextView = preset2(display);
    }
    else
    {
        display->clearDisplay();
        display->setTextSize(1);
        display->setCursor(0, SCREEN_HEIGHT / 2 - 4);
        display->print("Unknown ActionPrompt request.");
        display->display();
        delay(3000);
    }
    renderOkButton(display);
    display->display();

    return nextView;
}

void Alert::execute(std::function<unsigned int()> execute)
{
    this->exec = execute;
}

void Alert::nextComponent(unsigned int nextComponent)
{
    this->next = nextComponent;
}

unsigned int Alert::preset1(Adafruit_SSD1306 *display)
{
    display->setTextSize(1);
    display->setTextColor(SSD1306_WHITE);
    display->setCursor(10, 10);
    display->print(message);

    if (DisplayManager::selectedItem != 0)
    {
        return next;
    }

    return id;
}

unsigned int Alert::preset2(Adafruit_SSD1306 *display)
{
    display->drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE); // Desenha a borda

    display->setTextSize(1);
    display->setTextColor(SSD1306_WHITE);
    display->setCursor(10, 10);
    display->print(message);

    if (DisplayManager::selectedItem != 0)
    {
        return next;
    }

    return id;
}

void Alert::renderOkButton(Adafruit_SSD1306 *display)
{
    display->setTextSize(1);
    display->setTextColor(SSD1306_WHITE);

    display->fillRect((SCREEN_WIDTH - 30) / 2, SCREEN_HEIGHT - 20, 30, 15, SSD1306_WHITE); // Fundo branco
    display->setTextColor(SSD1306_BLACK);                                                  // Texto preto
    display->setCursor((SCREEN_WIDTH - 10) / 2, SCREEN_HEIGHT - 18);                       // Centraliza o texto
    display->print("OK");
}