# Getting Started

## Required Libraries

- Adafruit SSD1306

## Quick Start

1. Include the required libraries:

```cpp
#include <Adafruit_SSD1306.h>
#include <EasySSD1306.h>
```

2. Create a display manager instance with your desired resolution:

```cpp
// Available resolutions:
// - RESOLUTION_128x64: 128x64 pixels
// - RESOLUTION_128x32: 128x32 pixels

DisplayManager display(RESOLUTION_128x64);  // Create with 128x64 resolution
```

3. Configure button pins:

```cpp
void setup() {
    // Set this if you want to use buttons
    display.setButtons(2, 3);  // Set up/down buttons on pins 2 and 3
}
```

4. Add a component to the display:

```cpp
void setup() {
    // Create a simple text component
    TextView* text = new TextView("Hello World!");
    text->setPosition(10, 10);
    display.addComponent(text);
}
```

5. Update the display in your loop:

```cpp
void loop() {
    display.render();  // Update display and current state
}
```

## Components

### DisplayManager
The main component that manages the display and handles component rendering.

```cpp
DisplayManager display(RESOLUTION_128x64);  // Resolution is required
display.begin();
display.render();  // Update display and current state
```

### TextView
Displays text on the screen with various formatting options.

```cpp
TextView* text = new TextView("Hello World!");
text->setPosition(10, 10);
display.addComponent(text);
```

### Navigation
Provides menu navigation functionality with up/down selection.

```cpp
Navigation* nav = new Navigation();
nav->addItem("Item 1");
nav->addItem("Item 2");
display.addComponent(nav);
```

### Alert
Shows alert messages with different styles (info, warning, error).

```cpp
Alert* alert = new Alert("Message", ALERT_INFO);
display.addComponent(alert);
```

### ImageView
Displays bitmap images on the screen.

```cpp
ImageView* image = new ImageView(logoBitmap, 32, 32);
image->setPosition(48, 16);
display.addComponent(image);
```

### LoadAnimation
Shows loading animations with customizable styles.

```cpp
LoadAnimation* loader = new LoadAnimation(LOADER_DOTS);
display.addComponent(loader);
```

### Prompt
Creates interactive prompts with a built-in virtual keyboard for text input. This component implements a complete on-screen keyboard that allows users to enter text without a physical keyboard, making it perfect for settings, configuration, or any scenario requiring user text input.

```cpp
// Create a prompt with a title and initial value
Prompt* prompt = new Prompt("Enter Name:", "User");
prompt->setMaxLength(20);  // Limit input length
prompt->setKeyboardType(KEYBOARD_ALPHA);  // Use alphabetic keyboard

// Add callback for when input is complete
prompt->setOnComplete([](const char* value) {
    Serial.print("User entered: ");
    Serial.println(value);
});

display.addComponent(prompt);
```

The Prompt component features:
- Complete virtual keyboard with different layouts (alphabetic, numeric, special characters)
- Customizable input validation
- Maximum length restrictions
- Callback functions for input completion
- Visual feedback during typing
- Support for different input modes (text, numbers, passwords)

This makes it ideal for creating interactive forms, settings menus, or any interface requiring text input from the user.

## Examples

Check out the examples directory for complete working examples.

## Basic Example

Here's a complete example that shows a text message on the display:

```cpp
#include <Adafruit_SSD1306.h>
#include <EasySSD1306.h>

DisplayManager display(RESOLUTION_128x64);
TextView* text;

void setup() {
    // Configure display
    display.setOrientation(ORIENTATION_NORMAL);
    display.setColor(COLOR_WHITE);
    display.setFont(FONT_5x7);
    display.setContrast(128);
    display.setAnimationSpeed(5);
    
    // Create and configure text
    text = new TextView("Hello World!");
    text->setPosition(10, 10);
    display.addComponent(text);
}

void loop() {
    display.render();  // Updates the screen and current state
    delay(100);       // Small delay to prevent overwhelming the display
}
```

## Next Steps

1. Check the [Components](components/overview.md) section to learn about available display components
2. See [Display Configuration](display_manager/configuration.md) for all available settings
3. Learn about [Custom Components](components/custom.md) to create your own components 