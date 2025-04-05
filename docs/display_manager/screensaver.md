# Screen Saver

> **Nota**: Esta funcionalidade ainda não está implementada na versão atual da biblioteca.

O Screen Saver será implementado em uma versão futura da biblioteca EasySSD1306.

The Display Manager includes a screen saver feature to protect your OLED display from burn-in and save power. This page covers how to configure and use the screen saver.

## Configuration

You can configure the screen saver with the following settings:

```cpp
struct ScreenSaverConfig {
    bool enabled;           // Whether the screen saver is enabled
    uint32_t timeout;       // Time in milliseconds before screen saver activates
    uint32_t interval;      // Interval between screen saver updates
    uint8_t brightness;     // Brightness level when in screen saver mode
    bool invertColors;      // Whether to invert colors in screen saver mode
};
```

## Setting Up the Screen Saver

### Constructor

You can set up the screen saver when creating the Display Manager:

```cpp
// Default screen saver (disabled)
DisplayManager displayManager;

// Custom screen saver configuration
ScreenSaverConfig config = {
    .enabled = true,
    .timeout = 60000,    // 1 minute
    .interval = 1000,    // 1 second
    .brightness = 32,    // 25% brightness
    .invertColors = false
};
DisplayManager displayManager(128, 64, ORIENTATION_NORMAL, COLOR_WHITE, FONT_5x7, config);
```

### After Initialization

You can also configure the screen saver after the Display Manager has been initialized:

```cpp
void setScreenSaver(const ScreenSaverConfig& config)
```

## Screen Saver Events

You can register callback functions to be called when the screen saver activates or deactivates:

```cpp
void onScreenSaverActivated(std::function<void()> callback)
void onScreenSaverDeactivated(std::function<void()> callback)
```

## Complete Example

```cpp
#include <EasySSD1306.h>

DisplayManager displayManager;

void setup() {
    displayManager.begin();
    
    // Configure screen saver
    ScreenSaverConfig config = {
        .enabled = true,
        .timeout = 60000,    // 1 minute
        .interval = 1000,    // 1 second
        .brightness = 32,    // 25% brightness
        .invertColors = false
    };
    displayManager.setScreenSaver(config);
    
    // Set screen saver callbacks
    displayManager.onScreenSaverActivated([]() {
        Serial.println("Screen saver activated");
    });
    
    displayManager.onScreenSaverDeactivated([]() {
        Serial.println("Screen saver deactivated");
    });
    
    // Create components
    TextView* text = new TextView("Hello World");
    text->setPosition(10, 10);
    displayManager.addComponent(text);
}

void loop() {
    displayManager.update();
    delay(100);
}
```

## Screen Saver Patterns

The library provides several built-in screen saver patterns:

```cpp
enum ScreenSaverPattern {
    PATTERN_BLANK,      // Blank screen
    PATTERN_SCROLL,     // Scrolling text
    PATTERN_BOUNCE,     // Bouncing object
    PATTERN_WAVE,       // Wave pattern
    PATTERN_CUSTOM      // Custom pattern
};
```

You can set the pattern using:

```cpp
void setScreenSaverPattern(ScreenSaverPattern pattern)
```

## Custom Screen Saver

You can create a custom screen saver by implementing the `IScreenSaver` interface:

```cpp
class CustomScreenSaver : public IScreenSaver {
public:
    void render(DisplayManager& display) override {
        // Custom rendering code
    }
    
    void reset() override {
        // Reset any state
    }
};
```

Then set it as the active pattern:

```cpp
CustomScreenSaver customSaver;
displayManager.setScreenSaverPattern(PATTERN_CUSTOM);
displayManager.setCustomScreenSaver(&customSaver);
```

## Best Practices

1. **Choose Appropriate Timeout**
   - Set a timeout that makes sense for your application
   - Consider user interaction patterns

2. **Use Appropriate Brightness**
   - Lower brightness in screen saver mode
   - Balance between visibility and power savings

3. **Handle Activation/Deactivation**
   - Use callbacks to respond to screen saver state changes
   - Save state when screen saver activates
   - Restore state when screen saver deactivates

4. **Choose the Right Pattern**
   - Select a pattern that won't cause burn-in
   - Consider power consumption of different patterns

5. **Test Thoroughly**
   - Test screen saver with all components
   - Verify proper state restoration
   - Check power consumption 

DisplayManager display(RESOLUTION_128x64); 