# Display Contrast

The Display Manager allows you to control the contrast settings of the OLED display. This page covers how to set and work with different contrast configurations.

## Contrast Control

The SSD1306 display supports contrast control through the command 0x81 followed by a contrast value (0-255). The EasySSD1306 library provides methods to control this:

```cpp
// Set contrast level (0-255)
void setContrast(uint8_t contrast)

// Get current contrast level
uint8_t getContrast() const

// Register callback for contrast changes
void onContrastChanged(std::function<void(uint8_t)> callback)
```

## Setting the Contrast

You can set the contrast when creating the Display Manager:

```cpp
// Default contrast (128)
DisplayManager displayManager(128, 64);

// Custom contrast level
DisplayManager displayManager(128, 64, ORIENTATION_NORMAL, COLOR_WHITE, FONT_5x7, 200); // 200/255 contrast
```

You can also change the contrast after the Display Manager has been initialized:

```cpp
// Set contrast to 75%
displayManager.setContrast(192); // 192/255 ≈ 75%
```

## Getting the Current Contrast

```cpp
uint8_t contrast = displayManager.getContrast();
Serial.print("Current contrast: ");
Serial.println(contrast);
```

## Contrast Change Events

You can register a callback function to be called when the contrast changes:

```cpp
displayManager.onContrastChanged([](uint8_t contrast) {
    Serial.print("Contrast changed to: ");
    Serial.println(contrast);
});
```

## Complete Example

```cpp
#include <EasySSD1306.h>

void setup() {
    // Initialize display with custom contrast
    DisplayManager displayManager(128, 64, ORIENTATION_NORMAL, COLOR_WHITE, FONT_5x7, 200);

    // Set contrast change callback
    displayManager.onContrastChanged([](uint8_t contrast) {
        Serial.print("Contrast changed to: ");
        Serial.println(contrast);
    });

    // Change contrast
    displayManager.setContrast(192); // 75% contrast

    // Get current contrast
    uint8_t current = displayManager.getContrast();
    Serial.print("Current contrast: ");
    Serial.println(current);
}

void loop() {
    // Your code here
}
```

## Best Practices

1. **Choose Appropriate Contrast**
   - Higher contrast (200-255) for bright environments
   - Lower contrast (0-100) for dark environments
   - Medium contrast (100-200) for general use

2. **Adapt to Environment**
   - Consider using a light sensor to automatically adjust contrast
   - Allow user control for manual adjustment

3. **Save Power**
   - Lower contrast can reduce power consumption
   - Consider reducing contrast in screen saver mode 