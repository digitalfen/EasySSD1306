# Display Resolutions

The EasySSD1306 library supports multiple display resolutions. This document explains how to configure and use different resolutions.

## Available Resolutions

This document explains the available resolutions in the EasySSD1306 library.

## Resolution Constants

- `RESOLUTION_128x64`: 128x64 pixels
- `RESOLUTION_128x32`: 128x32 pixels
- `RESOLUTION_96x16`: 96x16 pixels
- `RESOLUTION_64x48`: 64x48 pixels
- `RESOLUTION_64x32`: 64x32 pixels

## Setting Resolution

### Constructor

```cpp
DisplayManager display(RESOLUTION_128x64, ORIENTATION_NORMAL);
```

### Runtime Change

```cpp
void setup() {
  display.begin();
  
  // Initial resolution
  display.setResolution(RESOLUTION_128x64);
  display.update();
  
  delay(2000);
  
  // Change resolution
  display.setResolution(RESOLUTION_64x32);
  display.update();
}
```

## Resolution and Components

Components automatically adapt to resolution changes:

```cpp
void setup() {
  display.begin();
  
  TextView* text = new TextView("Hello World");
  display.addComponent(text);
  
  display.update();
  
  delay(2000);
  
  // Change resolution
  display.setResolution(RESOLUTION_64x32);
  display.update();
}
```

## Resolution Change Example

```cpp
#include <EasySSD1306.h>

DisplayManager display(RESOLUTION_128x64, ORIENTATION_NORMAL);

void setup() {
  display.begin();
  
  TextView* text = new TextView("Hello World");
  display.addComponent(text);
  
  display.update();
  
  delay(2000);
  
  // Cycle through resolutions
  display.setResolution(RESOLUTION_128x32);
  display.update();
  
  delay(2000);
  
  display.setResolution(RESOLUTION_96x16);
  display.update();
  
  delay(2000);
  
  display.setResolution(RESOLUTION_64x48);
  display.update();
  
  delay(2000);
  
  display.setResolution(RESOLUTION_64x32);
  display.update();
}

void loop() {
  display.update();
}
```

## Resolution Constants

The resolution constants are defined in an enum:

```cpp
enum DisplayResolution {
  RESOLUTION_128x64,
  RESOLUTION_128x32,
  RESOLUTION_96x16,
  RESOLUTION_64x48,
  RESOLUTION_64x32
};
```

## Helper Functions

### getResolutionWidth()

```cpp
uint8_t getResolutionWidth(DisplayResolution resolution)
```

Returns the width of the specified resolution:
- `RESOLUTION_128x64`: 128 pixels
- `RESOLUTION_128x32`: 128 pixels
- `RESOLUTION_96x16`: 96 pixels
- `RESOLUTION_64x48`: 64 pixels
- `RESOLUTION_64x32`: 64 pixels

### getResolutionHeight()

```cpp
uint8_t getResolutionHeight(DisplayResolution resolution)
```

Returns the height of the specified resolution:
- `RESOLUTION_128x64`: 64 pixels
- `RESOLUTION_128x32`: 32 pixels
- `RESOLUTION_96x16`: 16 pixels
- `RESOLUTION_64x48`: 48 pixels
- `RESOLUTION_64x32`: 32 pixels

## Resolution Change Callback

```cpp
void onResolutionChanged(DisplayResolution newResolution) {
  Serial.print("Resolution changed to: ");
  Serial.print(getResolutionWidth(newResolution));
  Serial.print("x");
  Serial.println(getResolutionHeight(newResolution));
}

void setup() {
  display.setResolutionChangedCallback(onResolutionChanged);
}
```

## Troubleshooting

1. Display not resizing
   - Check resolution value
   - Verify display update
   - Check component positions

2. Component positioning
   - Check resolution
   - Verify component creation
   - Update after changes

3. Memory issues
   - Reduce number of components
   - Use simpler styles
   - Check available memory 