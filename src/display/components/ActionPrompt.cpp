#include "display/components/ActionPrompt.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

unsigned int ActionPrompt::render(Adafruit_SSD1306 *display)
{
    unsigned int nextView = 0;

    display->clearDisplay();

    if (preset == SIMPLE)
    {
        nextView = preset1(display);
    }
    else if (preset == BORDER)
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
    renderButtons(display);
    display->display();

    return nextView;
}

void ActionPrompt::execute(std::function<unsigned int()> execute)
{
    this->exec = execute;
}

unsigned int ActionPrompt::preset1(Adafruit_SSD1306 *display)
{
    // Estilo simples: apenas o texto centralizado
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

unsigned int ActionPrompt::preset2(Adafruit_SSD1306 *display)
{
    // Estilo com borda: texto centralizado com uma borda ao redor da tela
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

void ActionPrompt::renderButtons(Adafruit_SSD1306 *display)
{
    // Renderiza os botões "Cancelar" e "Confirmar" na parte inferior da tela
    display->setTextSize(1);
    display->setTextColor(WHITE);

    // Botão "Cancelar"
    display->fillRect(10, SCREEN_HEIGHT - 20, 50, 15, WHITE); // Fundo branco
    display->setTextColor(BLACK);                             // Texto preto
    display->setCursor(15, SCREEN_HEIGHT - 18);               // Posição do texto
    display->print("Cancel");

    // Botão "Confirmar"
    display->fillRect(SCREEN_WIDTH - 60, SCREEN_HEIGHT - 20, 50, 15, WHITE); // Fundo branco
    display->setTextColor(BLACK);                                            // Texto preto
    display->setCursor(SCREEN_WIDTH - 55, SCREEN_HEIGHT - 18);               // Posição do texto
    display->print("Confirm");
}