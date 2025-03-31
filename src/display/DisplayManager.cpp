#include "DisplayManager.h"

int DisplayManager::selectedItem = 0;
bool DisplayManager::confirmItem = false;
bool DisplayManager::cancelItem = false;

DisplayManager::DisplayManager() : currentState(0),
                                   lastState(0),
                                   lastButtonUpState(HIGH),
                                   lastButtonDownState(HIGH)
{
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

unsigned long buttonUpPressTime = 0;
unsigned long buttonDownPressTime = 0;
bool isButtonUpPressed = false;
bool isButtonDownPressed = false;
void DisplayManager::handleButtons()
{
    // Inicializações
    cancelItem = false;
    confirmItem = false;

    bool buttonUpState = digitalRead(buttonUp);
    bool buttonDownState = digitalRead(buttonDown);

    // Verifica o estado do botão Up
    if (buttonUpState == LOW && lastButtonUpState == HIGH)
    {
        // Botão foi pressionado
        buttonUpPressTime = millis(); // Marcar o tempo de pressionamento
        isButtonUpPressed = true;
        lastButtonUpState = LOW;
    }
    else if (buttonUpState == HIGH && lastButtonUpState == LOW)
    {
        // Botão foi solto
        if (isButtonUpPressed)
        {
            if ((millis() - buttonUpPressTime) < 500)
            {
                moveUp(); // Movimento apenas em clique curto
            }
            else
            {
                cancelItem = true; // Clique longo
            }
        }
        lastButtonUpState = HIGH;
        isButtonUpPressed = false;
    }

    // Verifica o estado do botão Down
    if (buttonDownState == LOW && lastButtonDownState == HIGH)
    {
        // Botão foi pressionado
        buttonDownPressTime = millis(); // Marcar o tempo de pressionamento
        isButtonDownPressed = true;
        lastButtonDownState = LOW;
    }
    else if (buttonDownState == HIGH && lastButtonDownState == LOW)
    {
        // Botão foi solto
        if (isButtonDownPressed)
        {
            if ((millis() - buttonDownPressTime) < 500)
            {
                moveDown(); // Movimento apenas em clique curto
            }
            else
            {
                confirmItem = true; // Clique longo
            }
        }
        lastButtonDownState = HIGH;
        isButtonDownPressed = false;
    }
}

void DisplayManager::addComponent(IDisplayComponent *component)
{
    int id = component->id;     // Supondo que cada componente tenha um método para obter seu ID.
    components[id] = component; // Insere ou substitui o componente no mapa.
}

void DisplayManager::setState(unsigned int n)
{
    if (n != currentState)
    {
        lastState = currentState;
        currentState = n;
        selectedItem = 0;
        confirmItem = false; // Reseta o estado de confirmação// Reseta o item selecionado ao mudar de estado
    }
}

void DisplayManager::render()
{
    handleButtons();

    if (DisplayManager::cancelItem)
    {
        setState(DisplayManager::lastState);
    }

    for (const auto &pair : components)
    {
        if (currentState == pair.first && pair.second != nullptr)
        {
            unsigned int state = pair.second->render(display);
            setState(state);
        }
    }
}
