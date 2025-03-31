# Navigation Component

The Navigation component creates menus and navigation interfaces.

## Usage

```cpp
#include <EasySSD1306.h>

void setup() {
    DisplayManager display(128, 64);
    Navigation* menu = new Navigation("Main Menu");
    menu->addItem("Temperature", "25°C");
    menu->addItem("Humidity", "60%");
    menu->addItem("Settings", "");
    display.addComponent(menu);
    display.begin();
}
```

## Methods

### Constructor
```cpp
Navigation(const char* title)
```

### Menu Items
```cpp
void addItem(const char* label, const char* value)
void removeItem(int index)
void clearItems()
```

### Selection
```cpp
void selectItem(int index)
int getSelectedIndex()
const char* getSelectedLabel()
const char* getSelectedValue()
```

### Navigation
```cpp
void nextItem()
void previousItem()
```

## Examples

### Hierarchical Menu
```cpp
void setup() {
    DisplayManager display(128, 64);
    
    Navigation* mainMenu = new Navigation("Main Menu");
    mainMenu->addItem("Temperature", "");
    mainMenu->addItem("Humidity", "");
    mainMenu->addItem("Settings", "");
    
    Navigation* settingsMenu = new Navigation("Settings");
    settingsMenu->addItem("Brightness", "50%");
    settingsMenu->addItem("Contrast", "75%");
    
    display.addComponent(mainMenu);
    display.addComponent(settingsMenu);
    display.begin();
}
```

### Dynamic Menu
```cpp
Navigation* menu;
char buffer[32];

void setup() {
    DisplayManager display(128, 64);
    menu = new Navigation("System Status");
    display.addComponent(menu);
    display.begin();
}

void loop() {
    menu->clearItems();
    sprintf(buffer, "Temperature: %d°C", getTemperature());
    menu->addItem("Temperature", buffer);
    sprintf(buffer, "Humidity: %d%%", getHumidity());
    menu->addItem("Humidity", buffer);
    display.update();
}
``` 