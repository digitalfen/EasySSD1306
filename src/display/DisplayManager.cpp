#include "DisplayManager.h"

int DisplayManager::selectedItem = 0;
bool DisplayManager::confirmItem = false;
bool DisplayManager::cancelItem = false;

DisplayManager::DisplayManager(DisplayResolution res) : currentState(0),
                                   lastState(0),
                                   lastButtonUpState(HIGH),
                                   lastButtonDownState(HIGH),
                                   resolution(res)
{
    // Inicializa o display com a resolução correta
    switch(resolution) {
        case RESOLUTION_128x64:
            display = new Adafruit_SSD1306(128, 64, &Wire, -1);
            break;
        case RESOLUTION_128x32:
            display = new Adafruit_SSD1306(128, 32, &Wire, -1);
            break;
        default:
            display = new Adafruit_SSD1306(128, 64, &Wire, -1);
            break;
    }
}

void DisplayManager::setDisplay(Adafruit_SSD1306 *disp)
{
    display = disp;
}

void DisplayManager::setButtons(uint8_t up, uint8_t down)
{
    buttonUp = up;
    buttonDown = down;
}

void DisplayManager::moveDown()
{
    selectedItem++;
}

void DisplayManager::moveUp()
{
    selectedItem--;
}

void DisplayManager::addComponent(IDisplayComponent *component)
{
    components[currentState] = component;
}

void DisplayManager::render()
{
    if (display == nullptr)
        return;

    handleButtons();

    if (components.find(currentState) != components.end())
    {
        components[currentState]->render(display);
    }
}

void DisplayManager::setState(unsigned int n)
{
    lastState = currentState;
    currentState = n;
}

void DisplayManager::handleButtons()
{
    bool buttonUpState = digitalRead(buttonUp);
    bool buttonDownState = digitalRead(buttonDown);

    // Button 1 (Up) - Press: Navigate within the current view, Hold: Go back
    if (buttonUpState == LOW && lastButtonUpState == HIGH)
    {
        // Button pressed
        moveUp();
    }
    else if (buttonUpState == LOW && lastButtonUpState == LOW)
    {
        // Button held
        cancelItem = true;
    }

    // Button 2 (Down) - Press: Navigate within the current view, Hold: Advance or confirm
    if (buttonDownState == LOW && lastButtonDownState == HIGH)
    {
        // Button pressed
        moveDown();
    }
    else if (buttonDownState == LOW && lastButtonDownState == LOW)
    {
        // Button held
        confirmItem = true;
    }

    lastButtonUpState = buttonUpState;
    lastButtonDownState = buttonDownState;
}
