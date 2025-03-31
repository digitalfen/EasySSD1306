# Examples

Examples demonstrating the use of EasySSD1306 components.

## Basic Examples

### Simple Text Display
```cpp
#include <EasySSD1306.h>

void setup() {
    DisplayManager display(128, 64);
    TextView* text = new TextView("Hello World!");
    text->setPosition(0, 0);
    display.addComponent(text);
    display.begin();
}

void loop() {
    display.update();
}
```

### Menu Navigation
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

void loop() {
    display.update();
}
```

### Loading Animation
```cpp
#include <EasySSD1306.h>

void setup() {
    DisplayManager display(128, 64);
    
    LoadAnimation* loading = new LoadAnimation("Loading...");
    loading->setPosition(0, 0);
    
    display.addComponent(loading);
    display.begin();
    
    loading->start();
}

void loop() {
    display.update();
}
```

## Advanced Examples

### System Status Display
```cpp
#include <EasySSD1306.h>

TextView* temp;
TextView* hum;
char buffer[32];

void setup() {
    DisplayManager display(128, 64);
    
    TextView* title = new TextView("System Status");
    title->setPosition(0, 0);
    title->setStyle(TextStyle::BOLD);
    
    temp = new TextView("");
    temp->setPosition(0, 16);
    
    hum = new TextView("");
    hum->setPosition(0, 32);
    
    display.addComponent(title);
    display.addComponent(temp);
    display.addComponent(hum);
    display.begin();
}

void loop() {
    sprintf(buffer, "Temperature: %d°C", getTemperature());
    temp->setText(buffer);
    
    sprintf(buffer, "Humidity: %d%%", getHumidity());
    hum->setText(buffer);
    
    display.update();
}
```

### Settings Menu
```cpp
#include <EasySSD1306.h>

void setup() {
    DisplayManager display(128, 64);
    
    Navigation* menu = new Navigation("Settings");
    menu->addItem("Brightness", "50%");
    menu->addItem("Contrast", "75%");
    menu->addItem("Inversion", "Off");
    menu->addItem("Back", "");
    
    display.addComponent(menu);
    display.begin();
}

void loop() {
    display.update();
}
```

### Alert System
```cpp
#include <EasySSD1306.h>

void setup() {
    DisplayManager display(128, 64);
    
    Alert* alert = new Alert("Warning", "Temperature too high!");
    alert->setDuration(3000);
    
    display.addComponent(alert);
    display.begin();
    
    alert->show();
}

void loop() {
    display.update();
}
```

## Complete Applications

### Weather Station
```cpp
#include <EasySSD1306.h>

TextView* temp;
TextView* hum;
TextView* press;
char buffer[32];

void setup() {
    DisplayManager display(128, 64);
    
    TextView* title = new TextView("Weather Station");
    title->setPosition(0, 0);
    title->setStyle(TextStyle::BOLD);
    
    temp = new TextView("");
    temp->setPosition(0, 16);
    
    hum = new TextView("");
    hum->setPosition(0, 32);
    
    press = new TextView("");
    press->setPosition(0, 48);
    
    display.addComponent(title);
    display.addComponent(temp);
    display.addComponent(hum);
    display.addComponent(press);
    display.begin();
}

void loop() {
    sprintf(buffer, "Temperature: %d°C", getTemperature());
    temp->setText(buffer);
    
    sprintf(buffer, "Humidity: %d%%", getHumidity());
    hum->setText(buffer);
    
    sprintf(buffer, "Pressure: %d hPa", getPressure());
    press->setText(buffer);
    
    display.update();
}
```

### System Monitor
```cpp
#include <EasySSD1306.h>

void setup() {
    DisplayManager display(128, 64);
    
    Navigation* menu = new Navigation("System Monitor");
    menu->addItem("CPU Usage", "45%");
    menu->addItem("Memory", "2.5GB/4GB");
    menu->addItem("Network", "Connected");
    menu->addItem("Storage", "75%");
    
    display.addComponent(menu);
    display.begin();
}

void loop() {
    display.update();
} 