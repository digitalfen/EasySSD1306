# Display Color

The Display Manager allows you to configure the color settings of the OLED display. This page covers how to set and work with different color configurations.

## Available Colors

The EasySSD1306 library supports the following color modes:

```cpp
enum DisplayColor {
    COLOR_WHITE,    // White on black (default)
    COLOR_INVERSE,  // Black on white
    COLOR_CUSTOM    // Custom color (if supported by hardware)
};
```

## Setting the Color

### Constructor

You can set the color mode when creating the Display Manager:

```cpp
// Default color (white)
DisplayManager displayManager;

// Custom color mode
DisplayManager displayManager(128, 64, ORIENTATION_NORMAL, COLOR_INVERSE);

// New constructor
DisplayManager display(RESOLUTION_128x64);

### After Initialization

You can also change the color mode after the Display Manager has been initialized:

```cpp
void setColor(DisplayColor color)
```

## Getting the Current Color

```cpp
DisplayColor getColor() const
```

Returns the current color mode as a `DisplayColor` enum value.

## Color Change Events

You can register a callback function to be called when the color mode changes:

```cpp
void onColorChanged(std::function<void(DisplayColor)> callback)
```

## Adapting Components to Color

Components can adapt to color changes by overriding the `adaptToColor` method:

```cpp
void adaptToColor(DisplayColor color) override {
    // Adjust component based on new color
    switch(color) {
        case COLOR_WHITE:
            // Adjust for white on black
            break;
        case COLOR_INVERSE:
            // Adjust for black on white
            break;
        case COLOR_CUSTOM:
            // Adjust for custom color
            break;
    }
}
```

## Helper Functions

The library provides helper functions to work with colors:

```cpp
bool isInverseColor(DisplayColor color)
```

This function returns true if the color mode is inverse (black on white).

## Complete Example

```cpp
#include <EasySSD1306.h>

DisplayManager displayManager;

void setup() {
    displayManager.begin();
    
    // Set color change callback
    displayManager.onColorChanged([](DisplayColor color) {
        Serial.print("Color changed to: ");
        Serial.println(color);
    });
    
    // Change color mode
    displayManager.setColor(COLOR_INVERSE);
    
    // Get current color
    DisplayColor current = displayManager.getColor();
    Serial.print("Current color: ");
    Serial.println(current);
    
    // Create components that adapt to color
    TextView* text = new TextView("Hello World");
    text->setPosition(10, 10);
    displayManager.addComponent(text);
}

void loop() {
    displayManager.update();
    delay(100);
}
```

## Color Inversion

The library provides methods to invert specific regions of the display:

```cpp
void invertRegion(uint8_t x, uint8_t y, uint8_t width, uint8_t height)
```

This method inverts the colors in the specified region without changing the global color mode.

## Best Practices

1. **Choose the Right Color Mode**
   - Select a color mode that provides good contrast for your application
   - Consider the lighting conditions where the display will be used

2. **Adapt Components**
   - Make sure components adapt to different color modes
   - Test your UI in all color modes

3. **Handle Color Changes**
   - Use the `onColorChanged` callback to respond to color mode changes
   - Update component appearances when color changes

4. **Consider Readability**
   - Ensure text and graphics are readable in all color modes
   - Test with different lighting conditions

5. **Use Inversion Sparingly**
   - Use region inversion for emphasis or highlighting
   - Don't overuse inversion as it can reduce readability 