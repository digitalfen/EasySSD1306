# Display Resolution

The Display Manager allows you to configure the resolution of the OLED display. This page covers how to set and work with different display resolutions.

## Available Resolutions

The EasySSD1306 library supports the following resolutions:

```cpp
enum DisplayResolution {
    RESOLUTION_128x64,  // 128x64 pixels (most common)
    RESOLUTION_128x32,  // 128x32 pixels
    RESOLUTION_96x16,   // 96x16 pixels
    RESOLUTION_64x48,   // 64x48 pixels
    RESOLUTION_64x32    // 64x32 pixels
};
```

## Setting the Resolution

### Constructor

You can set the resolution when creating the Display Manager:

```cpp
// Default resolution (128x64)
DisplayManager displayManager;

// Custom resolution
DisplayManager displayManager(128, 32);  // 128x32 resolution
```

### After Initialization

You can also change the resolution after the Display Manager has been initialized:

```cpp
void setResolution(DisplayResolution resolution)
```

```cpp
void setResolution(int width, int height)
```

## Getting the Current Resolution

```cpp
DisplayResolution getResolution() const
```

Returns the current resolution as a `DisplayResolution` enum value.

```cpp
int getWidth() const
int getHeight() const
```

Return the current width and height in pixels.

## Resolution Change Events

You can register a callback function to be called when the resolution changes:

```cpp
void onResolutionChanged(std::function<void(DisplayResolution)> callback)
```

## Adapting Components to Resolution

Components can adapt to resolution changes by overriding the `adaptToResolution` method:

```cpp
void adaptToResolution(int width, int height) override {
    // Adjust component based on new resolution
    if (width < 128) {
        // Adjust for smaller screens
    } else {
        // Adjust for larger screens
    }
}
```

## Helper Functions

The library provides helper functions to work with resolutions:

```cpp
uint8_t getResolutionWidth(DisplayResolution resolution)
uint8_t getResolutionHeight(DisplayResolution resolution)
```

These functions return the width and height in pixels for a given resolution.

## Complete Example

```cpp
#include <EasySSD1306.h>

DisplayManager displayManager;

void setup() {
    displayManager.begin();
    
    // Set resolution change callback
    displayManager.onResolutionChanged([](DisplayResolution res) {
        Serial.print("Resolution changed to: ");
        Serial.println(res);
    });
    
    // Change resolution
    displayManager.setResolution(RESOLUTION_128x32);
    
    // Get current resolution
    int width = displayManager.getWidth();
    int height = displayManager.getHeight();
    Serial.print("Current resolution: ");
    Serial.print(width);
    Serial.print("x");
    Serial.println(height);
    
    // Create components that adapt to resolution
    TextView* text = new TextView("Hello World");
    text->setPosition(10, 10);
    displayManager.addComponent(text);
}

void loop() {
    displayManager.update();
    delay(100);
}
```

## Best Practices

1. **Choose the Right Resolution**
   - Select a resolution that matches your physical display
   - Consider memory constraints when choosing higher resolutions

2. **Adapt Components**
   - Make sure components adapt to different resolutions
   - Test your UI at different resolutions

3. **Handle Resolution Changes**
   - Use the `onResolutionChanged` callback to respond to resolution changes
   - Update component layouts when resolution changes

4. **Consider Orientation**
   - Remember that orientation changes affect how resolution is interpreted
   - Test your UI in different orientations 