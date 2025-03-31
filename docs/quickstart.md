# Quick Start Guide

Get started with the EasySSD1306 library.

## Installation

### PlatformIO

Add to your `platformio.ini`:

```ini
lib_deps =
    digitalfen/EasySSD1306
```

### Arduino IDE

1. Download the ZIP file
2. Go to Sketch > Include Library > Add .ZIP Library
3. Select the downloaded ZIP file

## Basic Usage

```cpp
#include <EasySSD1306.h>

void setup() {
    DisplayManager display(128, 64);
    TextView* text = new TextView("Hello!");
    display.addComponent(text);
    display.begin();
}

void loop() {
    display.update();
}
```

## Components

### Text Display
```cpp
TextView* text = new TextView("Hello World!");
text->setPosition(0, 0);
text->setStyle(TextStyle::BOLD);
```

### Menu Navigation
```cpp
Navigation* menu = new Navigation("Main Menu");
menu->addItem("Temperature", "25°C");
menu->addItem("Humidity", "60%");
```

### Loading Animation
```cpp
LoadAnimation* loading = new LoadAnimation("Loading...");
loading->setPosition(0, 0);
loading->start();
```

### Alert Messages
```cpp
Alert* alert = new Alert("Warning", "System error detected");
alert->setDuration(3000);
alert->show();
```

## Examples

### Status Display
```cpp
void setup() {
    DisplayManager display(128, 64);
    
    TextView* title = new TextView("System Status");
    title->setPosition(0, 0);
    title->setStyle(TextStyle::BOLD);
    
    TextView* temp = new TextView("Temperature: 25°C");
    temp->setPosition(0, 16);
    
    TextView* hum = new TextView("Humidity: 60%");
    hum->setPosition(0, 32);
    
    display.addComponent(title);
    display.addComponent(temp);
    display.addComponent(hum);
    display.begin();
}
```

### Menu Interface
```cpp
void setup() {
    DisplayManager display(128, 64);
    
    Navigation* menu = new Navigation("Settings");
    menu->addItem("Temperature", "25°C");
    menu->addItem("Humidity", "60%");
    menu->addItem("Pressure", "1013hPa");
    
    display.addComponent(menu);
    display.begin();
}
```

## Next Steps

1. Check the [Components Overview](components/overview.md)
2. Review the [Examples](examples.md)
3. Read the [API Reference](api-reference.md) 