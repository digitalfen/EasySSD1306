#include "display/components/Load.h"
#include "display/DisplayManager.h"

unsigned int Load::render(Adafruit_SSD1306 *display)
{
    if (preset == PROGRESS_BAR)
    {
        return presetLoad1(display);
    }
    else if (preset == CIRCLE_SWEEP)
    {
        return presetLoad2(display);
    }
    else if (preset == DOT_SEQUENCE)
    {
        return presetLoad3(display);
    }
    else
    {
        display->clearDisplay();
        display->setTextSize(1);
        display->setCursor(0, display->height() / 2 - 4);
        display->print("Unknown Load preset.");
        display->display();
        delay(2000);

        return 0; // Retorna 0 para indicar erro
    }

    if (toExecute)
    {
        toExecute();
    }
}

unsigned int Load::presetLoad1(Adafruit_SSD1306 *display)
{
    display->clearDisplay();
    for (int i = 0; i <= 100; i++)
    {
        display->fillRect(10, 30, i, 10, SSD1306_WHITE); // Desenha a barra de progresso
        display->display();
        delay(10); // Ajuste para controlar a velocidade
    }
    display->clearDisplay();
    display->display();
    return toExecute();
}

unsigned int Load::presetLoad2(Adafruit_SSD1306 *display)
{

    int x = display->width() / 2;
    int y = display->height() / 2;
    int radius = 10;
    display->clearDisplay();

    for (int angle = 0; angle < 360; angle += 30)
    {
        display->drawCircle(x + radius * cos(angle * PI / 180),
                            y + radius * sin(angle * PI / 180),
                            2, SSD1306_WHITE);
        display->display();
        delay(250);
        display->clearDisplay();
    }
    return toExecute();
}
unsigned int Load::presetLoad3(Adafruit_SSD1306 *display)
{
    display->clearDisplay();
    int xStart = display->width() / 2 - 20; // Posição inicial no eixo X
    int y = display->height() / 2;          // Posição central no eixo Y

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // Desenha os círculos em sequência
            int x = xStart + (j * 20); // Espaçamento entre os círculos
            display->fillCircle(x, y, (i % 3 == j) ? 5 : 0, SSD1306_WHITE);
        }

        display->display();
        delay(300); // Tempo entre os frames
        display->clearDisplay();
    }

    display->display();

    return toExecute();
}

// Implementações de presetLoad2, presetLoad3, presetLoad4, presetLoad5
// Seguem a mesma lógica, mas podem variar o layout ou o comportamento dependendo do preset.
