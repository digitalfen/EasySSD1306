#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <map>

#include "display/components/Navigation.h"
#include "display/IDisplayComponent.h"

class DisplayManager
{
public:
    DisplayManager();

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
