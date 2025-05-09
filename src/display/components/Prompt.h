#ifndef Prompt_h
#define Prompt_h

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <vector>
#include <string>

#include "display/IDisplayComponent.h"
#include "display/DisplayManager.h"

enum PromptPresets
{
    PROMPT_DEFAULT,     // preset1
    PROMPT_WITH_BORDERS // preset2
};

class Prompt : public IDisplayComponent
{
public:
    Prompt(unsigned int id, PromptPresets preset, const char *message)
        : IDisplayComponent(id), message(message), preset(preset), next(id), scrollOffset(0) {}

    unsigned int render(Adafruit_SSD1306 *display) override;
    void nextComponent(unsigned int nextComponent);

    void execute(std::function<unsigned int()> execute);

private:
    const char *message;
    PromptPresets preset;
    unsigned int next;
    int scrollOffset;
    std::function<unsigned int()> exec;

    unsigned int preset1(Adafruit_SSD1306 *display); // Estilo simples
    unsigned int preset2(Adafruit_SSD1306 *display); // Estilo com borda
    void renderButtons(Adafruit_SSD1306 *display);   // Renderiza os botões
};

#endif