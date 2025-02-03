#ifndef Event_H
#define Event_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <map>
#include <string>

#include "display/IDisplayComponent.h"

// Enum para os presets de menu
enum EventPresets
{
    PROGRESS_BAR,
    CIRCLE_SWEEP,
    DOT_SEQUENCE
};

class Event : public IDisplayComponent
{
public:
    // Construtor da classe Menu
    Event(unsigned int id, EventPresets preset, std::function<unsigned int()> toExecute)
        : IDisplayComponent(id), preset(preset), toExecute(toExecute) {}

    unsigned int render(Adafruit_SSD1306 *disp) override;

private:
    std::function<unsigned int()> toExecute;

    EventPresets preset; // Preset do menu

    // Métodos privados para renderizar os menus específicos
    unsigned int presetEvent1(Adafruit_SSD1306 *display);
    unsigned int presetEvent2(Adafruit_SSD1306 *display);
    unsigned int presetEvent3(Adafruit_SSD1306 *display);
};

#endif
