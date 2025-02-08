#ifndef ActionPrompt_h
#define ActionPrompt_h

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <vector>
#include <string>

#include "display/IDisplayComponent.h"
#include "display/DisplayManager.h"

enum ActionPromptPresets
{
    SIMPLE, // preset1
    BORDER  // preset2
};

class ActionPrompt : public IDisplayComponent
{
public:
    ActionPrompt(unsigned int id, ActionPromptPresets preset, unsigned int next, const char *message)
        : IDisplayComponent(id), message(message), preset(preset), next(next), scrollOffset(0) {}

    unsigned int render(Adafruit_SSD1306 *display) override;

    void execute(std::function<unsigned int()> execute);

private:
    const char *message;
    ActionPromptPresets preset;
    unsigned int next;
    int scrollOffset;
    std::function<unsigned int()> exec;

    unsigned int preset1(Adafruit_SSD1306 *display); // Estilo simples
    unsigned int preset2(Adafruit_SSD1306 *display); // Estilo com borda
    void renderButtons(Adafruit_SSD1306 *display);   // Renderiza os botões
};

#endif