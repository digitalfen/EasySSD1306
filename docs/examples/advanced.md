# Advanced Examples

## Custom Animation

```cpp
#include <EasySSD1306.h>

class CustomAnimation : public TextAnimation {
public:
    CustomAnimation(const char* text) : TextAnimation(text) {}

    void update() override {
        // Bounce text left and right
        static int direction = 1;
        static int x = 0;
        
        x += direction;
        if (x >= 32 || x <= 0) {
            direction *= -1;
        }
        
        setPosition(x, getY());
    }
};

void setup() {
    DisplayManager display(128, 64);
    display.begin();

    CustomAnimation* animation = new CustomAnimation("Bouncing!");
    animation->setPosition(0, 32);
    display.addComponent(animation);
}

void loop() {
    display.update();
    delay(50);  // Control animation speed
}
```

## Interactive Menu System

```cpp
#include <EasySSD1306.h>

// Menu callback function type
typedef void (*MenuCallback)();

// Menu item structure
struct MenuItem {
    const char* name;
    MenuCallback callback;
};

void option1() { /* Handle option 1 */ }
void option2() { /* Handle option 2 */ }
void option3() { /* Handle option 3 */ }

// Menu items
MenuItem menuItems[] = {
    {"Option 1", option1},
    {"Option 2", option2},
    {"Option 3", option3}
};

void setup() {
    DisplayManager display(128, 64);
    display.begin();

    Navigation* menu = new Navigation();
    for (const auto& item : menuItems) {
        menu->addItem(item.name);
    }
    menu->setPosition(0, 0);
    display.addComponent(menu);

    // Add selection indicator
    TextView* indicator = new TextView(">");
    indicator->setPosition(0, menu->getSelectedIndex() * 8);
    display.addComponent(indicator);
}

void loop() {
    // Handle button inputs
    if (digitalRead(SELECT_PIN) == HIGH) {
        menuItems[menu->getSelectedIndex()].callback();
    }
    
    display.update();
}
```

## Multi-Screen Interface

```cpp
#include <EasySSD1306.h>

class Screen {
public:
    virtual void show(DisplayManager& display) = 0;
    virtual void hide(DisplayManager& display) = 0;
};

class MainScreen : public Screen {
    TextView* title;
    Navigation* menu;
public:
    MainScreen() {
        title = new TextView("Main Menu");
        title->setPosition(0, 0);
        
        menu = new Navigation();
        menu->addItem("Settings");
        menu->addItem("Status");
        menu->setPosition(0, 16);
    }
    
    void show(DisplayManager& display) override {
        display.addComponent(title);
        display.addComponent(menu);
    }
    
    void hide(DisplayManager& display) override {
        display.removeComponent(title);
        display.removeComponent(menu);
    }
};

class SettingsScreen : public Screen {
    // Similar implementation
};

void setup() {
    DisplayManager display(128, 64);
    display.begin();

    MainScreen* mainScreen = new MainScreen();
    mainScreen->show(display);
}

void loop() {
    display.update();
}
```

## Status Dashboard

```cpp
#include <EasySSD1306.h>

void setup() {
    DisplayManager display(128, 64);
    display.begin();

    // Title
    TextView* title = new TextView("System Status");
    title->setPosition(0, 0);
    display.addComponent(title);

    // CPU Usage Bar
    LoadAnimation* cpuBar = new LoadAnimation();
    cpuBar->setPosition(0, 16);
    display.addComponent(cpuBar);
    
    // Memory Usage
    TextView* memLabel = new TextView("MEM:");
    memLabel->setPosition(0, 32);
    display.addComponent(memLabel);
    
    TextView* memValue = new TextView("75%");
    memValue->setPosition(48, 32);
    display.addComponent(memValue);
    
    // Temperature
    TextView* tempLabel = new TextView("TEMP:");
    tempLabel->setPosition(0, 48);
    display.addComponent(tempLabel);
    
    TextView* tempValue = new TextView("28C");
    tempValue->setPosition(48, 48);
    display.addComponent(tempValue);
}

void loop() {
    // Update values periodically
    updateSystemStats();
    display.update();
    delay(1000);
}
``` 