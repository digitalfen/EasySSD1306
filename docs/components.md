# Display Components

This document explains the available components in the EasySSD1306 library.

## Available Components

- `TextView`: Display text with various styles
- `Navigation`: Create navigation menus
- `LoadAnimation`: Show loading animations
- `Alert`: Display alert messages
- `ImageView`: Display images

## Component Creation

```cpp
#include <EasySSD1306.h>

DisplayManager display(RESOLUTION_128x64, ORIENTATION_NORMAL);

void setup() {
  display.begin();
  
  if (!display.isInitialized()) {
    Serial.println("Failed to initialize display");
    return;
  }
  
  // Create components
  TextView* text = new TextView("Hello World");
  Navigation* menu = new Navigation();
  LoadAnimation* loader = new LoadAnimation();
  Alert* alert = new Alert("Alert!");
  ImageView* image = new ImageView();
  
  // Add components to display
  display.addComponent(text);
  display.addComponent(menu);
  display.addComponent(loader);
  display.addComponent(alert);
  display.addComponent(image);
  
  display.update();
}
```

## Component Adaptation

Components automatically adapt to resolution and orientation changes:

```cpp
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
  
  delay(2000);
  
  // Change orientation
  display.setOrientation(ORIENTATION_RIGHT);
  display.update();
}
```

## Component Styles

### TextView Styles

```cpp
TextViewStyle style;
style.fontSize = 2;
style.alignment = TEXT_ALIGN_CENTER;
style.color = COLOR_WHITE;

TextView* text = new TextView("Hello World", style);
```

### Navigation Styles

```cpp
NavigationStyle style;
style.itemHeight = 16;
style.selectedColor = COLOR_WHITE;
style.unselectedColor = COLOR_GRAY;

Navigation* menu = new Navigation(style);
```

### LoadAnimation Styles

```cpp
LoadAnimationStyle style;
style.size = 16;
style.color = COLOR_WHITE;
style.speed = 100;

LoadAnimation* loader = new LoadAnimation(style);
```

### Alert Styles

```cpp
AlertStyle style;
style.duration = 2000;
style.color = COLOR_WHITE;
style.backgroundColor = COLOR_BLACK;

Alert* alert = new Alert("Alert!", style);
```

### ImageView Styles

```cpp
ImageViewStyle style;
style.scale = 1;
style.alignment = IMAGE_ALIGN_CENTER;

ImageView* image = new ImageView(style);
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
  
  display.update();
}
```

## Troubleshooting

1. Component not displaying
   - Check component creation
   - Verify component addition
   - Check display update

2. Component positioning
   - Check resolution
   - Verify orientation
   - Update after changes

3. Style issues
   - Check style parameters
   - Verify color values
   - Update after changes

4. Memory issues
   - Reduce number of components
   - Use simpler styles
   - Check available memory
