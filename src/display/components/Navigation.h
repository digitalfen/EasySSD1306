#ifndef Navigation_H
#define Navigation_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <map>
#include <string>

#include "display/IDisplayComponent.h"

// Enum para os presets de Navigation
enum NavigationPresets
{
    CURSOR_LIST,
    HIGHLIGHT_LIST,
    VERTICAL_SELECTOR,
    HORIZONTAL_SELECTOR,

};

class Navigation : public IDisplayComponent
{
public:
    // Construtor da classe Navigation
    Navigation(unsigned int id, NavigationPresets preset, const std::map<int, String> &options)
        : IDisplayComponent(id), preset(preset), options(options) {}

    unsigned int render(Adafruit_SSD1306 *disp) override;

private:
    NavigationPresets preset;            // Preset do Navigation
    std::map<int, String> options; // Opções do Navigation, mapeando ID para nome

    // Métodos privados para renderizar os Navigations específicos
    unsigned int presetNavigation1(Adafruit_SSD1306 *display);
    unsigned int presetNavigation2(Adafruit_SSD1306 *display);
    unsigned int presetNavigation3(Adafruit_SSD1306 *display);
    unsigned int presetNavigation4(Adafruit_SSD1306 *display);
};

#endif
