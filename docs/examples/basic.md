# Basic Examples

## Simple Text Display

```cpp
#include <EasySSD1306.h>

void setup() {
    // Initialize display with default I2C pins
    DisplayManager display(128, 64);  // 128x64 OLED display
    display.begin();

    // Create and add a text component
    TextView* text = new TextView("Hello, World!");
    text->setPosition(0, 0);  // Position at top-left
    display.addComponent(text);
}

void loop() {
    display.update();  // Update display contents
}
```

## Multiple Components

```cpp
#include <EasySSD1306.h>

void setup() {
    DisplayManager display(128, 64);
    display.begin();

    // Add a title
    TextView* title = new TextView("Status");
    title->setPosition(0, 0);
    display.addComponent(title);

    // Add a loading animation
    LoadAnimation* loading = new LoadAnimation();
    loading->setPosition(0, 20);
    display.addComponent(loading);

    // Add a status message
    TextView* status = new TextView("Processing...");
    status->setPosition(0, 40);
    display.addComponent(status);
}

void loop() {
    display.update();
}
```

## Navigation Menu

```cpp
#include <EasySSD1306.h>

void setup() {
    DisplayManager display(128, 64);
    display.begin();

    // Create a navigation menu
    Navigation* menu = new Navigation();
    menu->addItem("Settings");
    menu->addItem("Info");
    menu->addItem("About");
    menu->setPosition(0, 0);
    display.addComponent(menu);
}

void loop() {
    // Handle button inputs (example using GPIO pins)
    if (digitalRead(UP_PIN) == HIGH) {
        menu->previous();
    }
    if (digitalRead(DOWN_PIN) == HIGH) {
        menu->next();
    }
    
    display.update();
}
```

## Alert Dialog

```cpp
#include <EasySSD1306.h>

void setup() {
    DisplayManager display(128, 64);
    display.begin();

    // Create an alert
    Alert* alert = new Alert("Warning", "Battery Low!");
    alert->setPosition(16, 16);  // Center on screen
    display.addComponent(alert);
}

void loop() {
    // Show alert for 3 seconds
    display.update();
    delay(3000);
    alert->setVisible(false);
    display.update();
}
```

## Image Display

```cpp
#include <EasySSD1306.h>

// Define a small 16x16 bitmap
const uint8_t ICON[] PROGMEM = {
    0x00, 0x00, 0x3E, 0x7C, 0x7E, 0xFE, 0x7E, 0xFE,
    0x7E, 0xFE, 0x7E, 0xFE, 0x7E, 0xFE, 0x3E, 0x7C,
    0x3E, 0x7C, 0x7E, 0xFE, 0x7E, 0xFE, 0x7E, 0xFE,
    0x7E, 0xFE, 0x7E, 0xFE, 0x3E, 0x7C, 0x00, 0x00
};

void setup() {
    DisplayManager display(128, 64);
    display.begin();

    // Create and add an image component
    ImageView* image = new ImageView(ICON, 16, 16);
    image->setPosition(56, 24);  // Center of screen
    display.addComponent(image);
}

void loop() {
    display.update();
} 