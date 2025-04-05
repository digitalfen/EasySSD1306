# Basic Example

This document provides a basic example of using the EasySSD1306 library.

## Code

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
  
  // Create components
  TextView* text = new TextView("Hello World", textStyle);
  display.addComponent(text);
  
  display.update();
}

void loop() {
  display.update();
}
```

## Explanation

1. Include the library
   ```cpp
   #include <EasySSD1306.h>
   ```

2. Create display instance
   ```cpp
   DisplayManager display(RESOLUTION_128x64, ORIENTATION_NORMAL);
   ```

3. Initialize display
   ```cpp
   display.begin();
   
   if (!display.isInitialized()) {
     Serial.println("Failed to initialize display");
     return;
   }
   ```

4. Create text style
   ```cpp
   TextViewStyle textStyle;
   textStyle.fontSize = 2;
   textStyle.alignment = TEXT_ALIGN_CENTER;
   textStyle.color = COLOR_WHITE;
   ```

5. Create text component
   ```cpp
   TextView* text = new TextView("Hello World", textStyle);
   ```

6. Add component to display
   ```cpp
   display.addComponent(text);
   ```

7. Update display
   ```cpp
   display.update();
   ```

## Troubleshooting

1. Display not initializing
   - Check I2C connections
   - Verify I2C address
   - Check I2C pins

2. Text not displaying
   - Check component creation
   - Verify component addition
   - Check display update

3. Style issues
   - Check style parameters
   - Verify color values
   - Update after changes

4. Memory issues
   - Reduce number of components
   - Use simpler styles
   - Check available memory

## Display Initialization

```cpp
#include <EasySSD1306.h>

void setup() {
    // For 128x64 display (default)
    DisplayManager display;
    // or explicitly
    DisplayManager display(RES_128_64);

    // For 128x32 display
    DisplayManager display(RES_128_32);

    // For 96x16 display
    DisplayManager display(RES_96_16);

    // For 64x48 display
    DisplayManager display(RES_64_48);

    // For 64x32 display
    DisplayManager display(RES_64_32);

    // Initialize with default I2C address (0x3C)
    if (!display.begin()) {
        Serial.println("Display initialization failed!");
        return;
    }

    // Or with custom I2C address
    if (!display.begin(0x3D)) {
        Serial.println("Display initialization failed!");
        return;
    }
}

void loop() {
    display.update();
}
```

## Simple Text Display

```cpp
#include <EasySSD1306.h>

DisplayManager display(RESOLUTION_128x64, ORIENTATION_NORMAL);

void setup() {
  if (!display.begin()) {
    Serial.println("Failed to initialize display");
    while (1);
  }
  
  TextView* text = new TextView("Hello World");
  display.addComponent(text);
  
  display.update();
}

void loop() {
  display.update();
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

DisplayManager display(RESOLUTION_128x64, ORIENTATION_NORMAL);

void setup() {
  if (!display.begin()) {
    Serial.println("Failed to initialize display");
    while (1);
  }
  
  const char* items[] = {"Home", "Settings", "About"};
  Navigation* menu = new Navigation(items, 3);
  menu->setStyle(NAV_STYLE_SIMPLE);
  
  display.addComponent(menu);
  display.update();
}

void loop() {
  display.update();
}
```

## Alert Dialog

```cpp
#include <EasySSD1306.h>

DisplayManager display(RESOLUTION_128x64, ORIENTATION_NORMAL);

void setup() {
  if (!display.begin()) {
    Serial.println("Failed to initialize display");
    while (1);
  }
  
  Alert* alert = new Alert("Warning!");
  alert->setStyle(ALERT_STYLE_BOXED);
  
  display.addComponent(alert);
  display.update();
}

void loop() {
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

DisplayManager display(RESOLUTION_128x64, ORIENTATION_NORMAL);

void setup() {
  if (!display.begin()) {
    Serial.println("Failed to initialize display");
    while (1);
  }
  
  ImageView* image = new ImageView(ICON, 16, 16);
  image->setStyle(IMG_STYLE_NORMAL);
  
  display.addComponent(image);
  display.update();
}

void loop() {
  display.update();
}
```

## Resolution Change

```cpp
#include <EasySSD1306.h>

DisplayManager display(RESOLUTION_128x64, ORIENTATION_NORMAL);

void setup() {
  if (!display.begin()) {
    Serial.println("Failed to initialize display");
    while (1);
  }
  
  TextView* text = new TextView("Hello World");
  display.addComponent(text);
  
  display.update();
  delay(2000);
  
  display.setResolution(RESOLUTION_64x32);
  display.update();
}

void loop() {
  display.update();
}
```

## Orientation Change

```cpp
#include <EasySSD1306.h>

DisplayManager display(RESOLUTION_128x64, ORIENTATION_NORMAL);

void setup() {
  if (!display.begin()) {
    Serial.println("Failed to initialize display");
    while (1);
  }
  
  TextView* text = new TextView("Hello World");
  display.addComponent(text);
  
  display.update();
  delay(2000);
  
  display.setOrientation(ORIENTATION_RIGHT);
  display.update();
}

void loop() {
  display.update();
}
```

## Button Control

```cpp
#include <EasySSD1306.h>

DisplayManager display(RESOLUTION_128x64, ORIENTATION_NORMAL);

void setup() {
  if (!display.begin()) {
    Serial.println("Failed to initialize display");
    while (1);
  }
  
  display.setButtonPins(2, 3);
  
  TextView* text = new TextView("Press Button");
  display.addComponent(text);
  
  display.update();
}

void loop() {
  if (display.wasButton1Pressed()) {
    // Button 1 pressed
  }
  
  if (display.wasButton2Pressed()) {
    // Button 2 pressed
  }
  
  display.update();
}
```

## Callbacks

```cpp
#include <EasySSD1306.h>

DisplayManager display(RESOLUTION_128x64, ORIENTATION_NORMAL);

void onResolutionChanged(DisplayResolution newResolution) {
  Serial.print("Resolution changed to: ");
  Serial.print(getResolutionWidth(newResolution));
  Serial.print("x");
  Serial.println(getResolutionHeight(newResolution));
}

void onOrientationChanged(DisplayOrientation newOrientation) {
  Serial.print("Orientation changed to: ");
  Serial.print(getOrientationDegrees(newOrientation));
  Serial.println(" degrees");
}

void setup() {
  if (!display.begin()) {
    Serial.println("Failed to initialize display");
    while (1);
  }
  
  display.setResolutionChangedCallback(onResolutionChanged);
  display.setOrientationChangedCallback(onOrientationChanged);
  
  TextView* text = new TextView("Hello World");
  display.addComponent(text);
  
  display.update();
}

void loop() {
  display.update();
}
``` 