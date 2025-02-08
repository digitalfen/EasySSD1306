#include "display/components/Prompt.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

unsigned int Prompt::render(Adafruit_SSD1306 *display)
{
    unsigned int nextView = 0;

    display->clearDisplay();

    if (preset == PROMPT_DEFAULT)
    {
        nextView = preset1(display);
    }
    else if (preset == PROMPT_WITH_BORDERS)
    {
        nextView = preset2(display);
    }
    else
    {
        display->clearDisplay();
        display->setTextSize(1);
        display->setCursor(0, SCREEN_HEIGHT / 2 - 4);
        display->print("Unknown Prompt request.");
        display->display();
        delay(3000);
    }
    renderButtons(display);
    display->display();

    return nextView;
}

void Prompt::execute(std::function<unsigned int()> execute)
{
    this->exec = execute;
}

unsigned int Prompt::preset1(Adafruit_SSD1306 *display)
{
    display->setTextSize(1);
    display->setTextColor(WHITE);
    display->setCursor(10, 10);
    display->print(message);

    if (DisplayManager::confirmItem)
    {
        return next;
    }

    return id;
}

unsigned int Prompt::preset2(Adafruit_SSD1306 *display)
{
    display->drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE); // Desenha a borda

    display->setTextSize(1);
    display->setTextColor(WHITE);
    display->setCursor(10, 10);
    display->print(message);

    if (DisplayManager::confirmItem)
    {
        return next;
    }

    return id;
}

void Prompt::renderButtons(Adafruit_SSD1306 *display)
{
    display->setTextSize(1);
    display->setTextColor(WHITE);

    display->fillRect(10, SCREEN_HEIGHT - 20, 50, 15, WHITE); // Fundo branco
    display->setTextColor(BLACK);                             // Texto preto
    display->setCursor(15, SCREEN_HEIGHT - 18);               // Posição do texto
    display->print("Cancel");

    display->fillRect(SCREEN_WIDTH - 60, SCREEN_HEIGHT - 20, 50, 15, WHITE); // Fundo branco
    display->setTextColor(BLACK);                                            // Texto preto
    display->setCursor(SCREEN_WIDTH - 55, SCREEN_HEIGHT - 18);               // Posição do texto
    display->print("Confirm");
}