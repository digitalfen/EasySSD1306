#ifndef LOAD_H
#define LOAD_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <map>
#include <string>

#include "display/IDisplayComponent.h"

// Enum para os presets de menu
enum LoadPresets
{
    PROGRESS_BAR,
    CIRCLE_SWEEP,
    DOT_SEQUENCE
};

class Load : public IDisplayComponent
{
public:
    // Construtor da classe Menu
    Load(unsigned int id, LoadPresets preset, std::function<unsigned int()> toExecute)
        : IDisplayComponent(id), preset(preset), toExecute(toExecute) {}

    unsigned int render(Adafruit_SSD1306 *disp) override;

private:
    std::function<unsigned int()> toExecute;

    LoadPresets preset; // Preset do menu

    // Métodos privados para renderizar os menus específicos
    unsigned int presetLoad1(Adafruit_SSD1306 *display);
    unsigned int presetLoad2(Adafruit_SSD1306 *display);
    unsigned int presetLoad3(Adafruit_SSD1306 *display);
};

#endif
