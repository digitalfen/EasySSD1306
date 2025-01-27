#ifndef MENU_H
#define MENU_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <map>
#include <string>

#include "display/IDisplayComponent.h"

// Enum para os presets de menu
enum MenuPresets
{
    CURSOR_LIST,
    HIGHLIGHT_LIST,
    VERTICAL_SELECTOR,
    HORIZONTAL_SELECTOR,

};

class Menu : public IDisplayComponent
{
public:
    // Construtor da classe Menu
    Menu(unsigned int id, MenuPresets preset, const std::map<int, String> &options)
        : IDisplayComponent(id), preset(preset), options(options) {}

    unsigned int render(Adafruit_SSD1306 *disp) override;

private:
    MenuPresets preset;            // Preset do menu
    std::map<int, String> options; // Opções do menu, mapeando ID para nome

    // Métodos privados para renderizar os menus específicos
    unsigned int presetMenu1(Adafruit_SSD1306 *display);
    unsigned int presetMenu2(Adafruit_SSD1306 *display);
    unsigned int presetMenu3(Adafruit_SSD1306 *display);
    unsigned int presetMenu4(Adafruit_SSD1306 *display);
};

#endif
