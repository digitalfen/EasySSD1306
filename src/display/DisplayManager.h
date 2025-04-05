#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <map>

#include "display/components/Navigation.h"
#include "display/IDisplayComponent.h"

// Enum para as resoluções disponíveis
enum DisplayResolution {
    RESOLUTION_128x64,  // Standard 128x64 pixel display (default)
    RESOLUTION_128x32   // 128x32 pixel display
};

class DisplayManager
{
public:
    // Construtor que exige a resolução
    DisplayManager(DisplayResolution resolution);

    void setDisplay(Adafruit_SSD1306 *disp);
    void setButtons(uint8_t buttonUp, uint8_t buttonDown);
    void addComponent(IDisplayComponent *component);

    void render();
    void setState(unsigned int n);

    unsigned int currentState;
    unsigned int lastState;

    static int selectedItem;
    static bool confirmItem;
    static bool cancelItem;

private:
    Adafruit_SSD1306 *display;
    DisplayResolution resolution;

    std::map<int, IDisplayComponent *> components;

    uint8_t buttonUp;
    uint8_t buttonDown;

    void moveDown();
    void moveUp();

    void handleButtons();

    bool lastButtonUpState;
    bool lastButtonDownState;
};

#endif
