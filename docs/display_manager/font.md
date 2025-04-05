# Display Font

The Display Manager allows you to configure the font settings of the OLED display. This page covers how to set and work with different font configurations.

## Available Fonts

The EasySSD1306 library supports the following font modes:

```cpp
enum DisplayFont {
    FONT_5x7,     // 5x7 pixel font (default)
    FONT_8x8,     // 8x8 pixel font
    FONT_8x16,    // 8x16 pixel font
    FONT_12x16,   // 12x16 pixel font
    FONT_16x16,   // 16x16 pixel font
    FONT_16x24,   // 16x24 pixel font
    FONT_24x32    // 24x32 pixel font
};
```

## Setting the Font

### Constructor

You can set the font mode when creating the Display Manager:

```cpp
// Default font (5x7)
DisplayManager displayManager;

// Custom font mode
DisplayManager displayManager(128, 64, ORIENTATION_NORMAL, COLOR_WHITE, FONT_8x16);
```

### After Initialization

You can also change the font mode after the Display Manager has been initialized:

```cpp
void setFont(DisplayFont font)
```

## Getting the Current Font

```cpp
DisplayFont getFont() const
```

Returns the current font mode as a `DisplayFont` enum value.

## Font Change Events

You can register a callback function to be called when the font mode changes:

```cpp
void onFontChanged(std::function<void(DisplayFont)> callback)
```

## Adapting Components to Font

Components can adapt to font changes by overriding the `adaptToFont` method:

```cpp
void adaptToFont(DisplayFont font) override {
    // Adjust component based on new font
    switch(font) {
        case FONT_5x7:
            // Adjust for 5x7 font
            break;
        case FONT_8x8:
            // Adjust for 8x8 font
            break;
        case FONT_8x16:
            // Adjust for 8x16 font
            break;
        // ... handle other font sizes
    }
}
```

## Helper Functions

The library provides helper functions to work with fonts:

```cpp
uint8_t getFontWidth(DisplayFont font)
uint8_t getFontHeight(DisplayFont font)
```

These functions return the width and height of a given font in pixels.

## Complete Example

```cpp
#include <EasySSD1306.h>

DisplayManager displayManager;

void setup() {
    displayManager.begin();
    
    // Set font change callback
    displayManager.onFontChanged([](DisplayFont font) {
        Serial.print("Font changed to: ");
        Serial.println(font);
    });
    
    // Change font mode
    displayManager.setFont(FONT_8x16);
    
    // Get current font
    DisplayFont current = displayManager.getFont();
    Serial.print("Current font: ");
    Serial.println(current);
    
    // Create components that adapt to font
    TextView* text = new TextView("Hello World");
    text->setPosition(10, 10);
    displayManager.addComponent(text);
}

void loop() {
    displayManager.update();
    delay(100);
}
```

## Font Metrics

The library provides methods to get font metrics:

```cpp
uint16_t getTextWidth(const char* text, DisplayFont font)
uint16_t getTextHeight(const char* text, DisplayFont font)
```

These methods return the width and height of a text string in a given font.

## Best Practices

1. **Choose the Right Font**
   - Select a font size that fits your display resolution
   - Consider the amount of text you need to display

2. **Adapt Components**
   - Make sure components adapt to different font sizes
   - Test your UI with all font sizes

3. **Handle Font Changes**
   - Use the `onFontChanged` callback to respond to font changes
   - Update component layouts when font changes

4. **Consider Space**
   - Remember that larger fonts take up more space
   - Plan your layout accordingly

5. **Use Font Metrics**
   - Use font metrics to calculate text dimensions
   - Center text properly using width and height 