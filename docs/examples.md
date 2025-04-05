# Examples

This document provides examples of using the EasySSD1306 library.

## Basic Example

```cpp
#include <EasySSD1306.h>

DisplayManager display(RESOLUTION_128x64, ORIENTATION_NORMAL);

void setup() {
  display.begin();
  
  if (!display.isInitialized()) {
    Serial.println("Failed to initialize display");
    return;
  }
  
  TextView* text = new TextView("Hello World");
  display.addComponent(text);
  
  display.update();
}

void loop() {
  display.update();
}
```

## Resolution Example

```cpp
#include <EasySSD1306.h>

DisplayManager display(RESOLUTION_128x64, ORIENTATION_NORMAL);

void setup() {
  display.begin();
  
  if (!display.isInitialized()) {
    Serial.println("Failed to initialize display");
    return;
  }
  
  TextView* text = new TextView("Hello World");
  display.addComponent(text);
  
  display.update();
  
  delay(2000);
  
  // Change resolution
  display.setResolution(RESOLUTION_64x32);
  display.update();
}

void loop() {
  display.update();
}
```

## Orientation Example

```cpp
#include <EasySSD1306.h>

DisplayManager display(RESOLUTION_128x64, ORIENTATION_NORMAL);

void setup() {
  display.begin();
  
  if (!display.isInitialized()) {
    Serial.println("Failed to initialize display");
    return;
  }
  
  TextView* text = new TextView("Hello World");
  display.addComponent(text);
  
  display.update();
  
  delay(2000);
  
  // Change orientation
  display.setOrientation(ORIENTATION_RIGHT);
  display.update();
}

void loop() {
  display.update();
}
```

## Navigation Example

```cpp
#include <EasySSD1306.h>

DisplayManager display(RESOLUTION_128x64, ORIENTATION_NORMAL);

void setup() {
  display.begin();
  
  if (!display.isInitialized()) {
    Serial.println("Failed to initialize display");
    return;
  }
  
  NavigationStyle style;
  style.itemHeight = 16;
  style.selectedColor = COLOR_WHITE;
  style.unselectedColor = COLOR_GRAY;
  
  Navigation* menu = new Navigation(style);
  
  menu->addItem("Item 1");
  menu->addItem("Item 2");
  menu->addItem("Item 3");
  
  display.addComponent(menu);
  
  display.update();
}

void loop() {
  if (display.isButtonPressed(ButtonType::UP)) {
    menu->selectPrevious();
  }
  
  if (display.isButtonPressed(ButtonType::DOWN)) {
    menu->selectNext();
  }
  
  display.update();
}
```

## LoadAnimation Example

```cpp
#include <EasySSD1306.h>

DisplayManager display(RESOLUTION_128x64, ORIENTATION_NORMAL);

void setup() {
  display.begin();
  
  if (!display.isInitialized()) {
    Serial.println("Failed to initialize display");
    return;
  }
  
  LoadAnimationStyle style;
  style.size = 16;
  style.color = COLOR_WHITE;
  style.speed = 100;
  
  LoadAnimation* loader = new LoadAnimation(style);
  display.addComponent(loader);
  
  display.update();
}

void loop() {
  display.update();
}
```

## Alert Example

```cpp
#include <EasySSD1306.h>

DisplayManager display(RESOLUTION_128x64, ORIENTATION_NORMAL);

void setup() {
  display.begin();
  
  if (!display.isInitialized()) {
    Serial.println("Failed to initialize display");
    return;
  }
  
  AlertStyle style;
  style.duration = 2000;
  style.color = COLOR_WHITE;
  style.backgroundColor = COLOR_BLACK;
  
  Alert* alert = new Alert("Alert!", style);
  display.addComponent(alert);
  
  display.update();
}

void loop() {
  display.update();
}
```

## ImageView Example

```cpp
#include <EasySSD1306.h>

DisplayManager display(RESOLUTION_128x64, ORIENTATION_NORMAL);

void setup() {
  display.begin();
  
  if (!display.isInitialized()) {
    Serial.println("Failed to initialize display");
    return;
  }
  
  ImageViewStyle style;
  style.scale = 1;
  style.alignment = IMAGE_ALIGN_CENTER;
  
  ImageView* image = new ImageView(style);
  display.addComponent(image);
  
  display.update();
}

void loop() {
  display.update();
}
```

## Complete Example

```cpp
#include <EasySSD1306.h>

DisplayManager display(RESOLUTION_128x64, ORIENTATION_NORMAL);

void setup() {
  display.begin();
  
  if (!display.isInitialized()) {
    Serial.println("Failed to initialize display");
    return;
  }
  
  // Create text style
  TextViewStyle textStyle;
  textStyle.fontSize = 2;
  textStyle.alignment = TEXT_ALIGN_CENTER;
  textStyle.color = COLOR_WHITE;
  
  // Create navigation style
  NavigationStyle menuStyle;
  menuStyle.itemHeight = 16;
  menuStyle.selectedColor = COLOR_WHITE;
  menuStyle.unselectedColor = COLOR_GRAY;
  
  // Create components
  TextView* text = new TextView("Hello World", textStyle);
  Navigation* menu = new Navigation(menuStyle);
  
  // Add menu items
  menu->addItem("Item 1");
  menu->addItem("Item 2");
  menu->addItem("Item 3");
  
  // Add components to display
  display.addComponent(text);
  display.addComponent(menu);
  
  display.update();
}

void loop() {
  if (display.isButtonPressed(ButtonType::UP)) {
    menu->selectPrevious();
  }
  
  if (display.isButtonPressed(ButtonType::DOWN)) {
    menu->selectNext();
  }
  
  if (display.isButtonPressed(ButtonType::SELECT)) {
    display.setResolution(RESOLUTION_64x32);
  }
  
  display.update();
}
```

## Troubleshooting

1. Display not initializing
   - Check I2C connections
   - Verify I2C address
   - Check I2C pins

2. Components not displaying
   - Check component creation
   - Verify component addition
   - Check display update

3. Button issues
   - Check button connections
   - Verify button pins
   - Check button state

4. Memory issues
   - Reduce number of components
   - Use simpler styles
   - Check available memory 