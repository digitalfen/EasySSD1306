# Display Manager Utilization

This page covers how to effectively utilize the Display Manager in your projects. It provides practical examples and best practices for working with the Display Manager.

## Basic Configuration

```cpp
// Create display manager with resolution
DisplayManager display(RESOLUTION_128x64);

// Configure display settings
display.setOrientation(ORIENTATION_NORMAL);
display.setColor(COLOR_WHITE);
display.setFont(FONT_5x7);
display.setContrast(128);
display.setAnimationSpeed(5);

// Configure buttons
display.setButtonPins(2, 3);
```

## Basic Usage

### Initialization

```cpp
#include <EasySSD1306.h>

// Create a display manager with default resolution (128x64)
DisplayManager displayManager;

void setup() {
    // Initialize the display
    displayManager.begin();
    
    // Configure display settings
    displayManager.setOrientation(ORIENTATION_NORMAL);
    displayManager.setColor(COLOR_WHITE);
    displayManager.setFont(FONT_5x7);
    
    // Add components
    TextView* text = new TextView("Hello World");
    text->setPosition(10, 10);
    displayManager.addComponent(text);
}

void loop() {
    // Update the display
    displayManager.update();
    delay(100);
}
```

### With Button Input

```cpp
#include <EasySSD1306.h>

DisplayManager displayManager;

void setup() {
    // Initialize with buttons on pins 2 and 3
    displayManager.begin();
    displayManager.setButtonPins(2, 3);
    
    // Add components
    TextView* text = new TextView("Hello World");
    text->setPosition(10, 10);
    displayManager.addComponent(text);
}

void loop() {
    // Update display and handle buttons
    displayManager.update();
    
    if (displayManager.isButton1Pressed()) {
        // Handle button 1 press
    }
    
    if (displayManager.isButton2Pressed()) {
        // Handle button 2 press
    }
    
    delay(100);
}
```

## Component Management

### Adding Components

```cpp
// Create components
TextView* text = new TextView("Hello World");
ImageView* image = new ImageView(myImageData, width, height);
Alert* alert = new Alert("Important Message");

// Add components to display manager
displayManager.addComponent(text);
displayManager.addComponent(image);
displayManager.addComponent(alert);
```

### Removing Components

```cpp
// Remove by pointer
displayManager.removeComponent(text);

// Remove all components
displayManager.clearComponents();
```

### Component Access

```cpp
// Get component by ID
Component* component = displayManager.getComponentById(128);
if (component != nullptr) {
    // Use component
}
```

### Clear All Components

```cpp
// Clear all components
displayManager.clearComponents();
```

## Display Updates

### Basic Rendering

```cpp
void loop() {
    // Update display
    displayManager.update();
    delay(100);
}
```

### Clearing the Display

```cpp
// Clear the display buffer
displayManager.clear();

// Clear the physical display
displayManager.clearDisplay();
```

### Force Immediate Render

```cpp
// Force immediate render
displayManager.render();
```

## Buttons

The Display Manager can handle button inputs for navigation and interaction. You can configure the button pins:

```cpp
// Define button pins
const uint8_t UP_BUTTON_PIN = 2;
const uint8_t DOWN_BUTTON_PIN = 3;

// Configure button pins
displayManager.setButtonPins(UP_BUTTON_PIN, DOWN_BUTTON_PIN);
```

Button handling is automatic - the Display Manager will:
- Detect button presses
- Handle debouncing
- Update component states

You can check button states:

```cpp
// Check if a button is pressed
if (displayManager.isButton1Pressed()) {
    // Handle button 1 press
}

if (displayManager.isButton2Pressed()) {
    // Handle button 2 press
}

// Check if a button was pressed in the last update
if (displayManager.wasButton1Pressed()) {
    // Handle button 1 press
}

if (displayManager.wasButton2Pressed()) {
    // Handle button 2 press
}
```

## Screen Saver

### Basic Setup

```cpp
// Configure screen saver
ScreenSaverConfig config = {
    .enabled = true,
    .timeout = 60000,    // 1 minute
    .interval = 1000,    // 1 second
    .brightness = 32,    // 25% brightness
    .invertColors = false
};
displayManager.setScreenSaver(config);
```

### Screen Saver Events

```cpp
// Set callbacks
displayManager.onScreenSaverActivated([]() {
    Serial.println("Screen saver activated");
});

displayManager.onScreenSaverDeactivated([]() {
    Serial.println("Screen saver deactivated");
});
```

### Enable Screen Saver

```cpp
// Enable screen saver (turns off display after 5 minutes)
displayManager.enableScreenSaver();

// Custom timeout (10 minutes)
displayManager.enableScreenSaver(600);

// Disable screen saver
displayManager.disableScreenSaver();
```

## Display Access

```cpp
// Get display instance
Adafruit_SSD1306* display = displayManager.getDisplay();

// Direct display commands
display->clearDisplay();
display->display();
```

## Event Handling

```cpp
// Register callback for resolution changes
displayManager.onResolutionChanged([](uint16_t width, uint16_t height) {
    Serial.print("Resolution changed to: ");
    Serial.print(width);
    Serial.print("x");
    Serial.println(height);
});

// Register callback for orientation changes
displayManager.onOrientationChanged([](DisplayOrientation orientation) {
    Serial.print("Orientation changed to: ");
    Serial.println(orientation == ORIENTATION_NORMAL ? "Normal" : "Inverted");
});
```

## Complete Example

```cpp
#include <EasySSD1306.h>

DisplayManager displayManager;
TextView* text;
Navigation* menu;

void setup() {
    // Initialize with buttons
    displayManager.begin();
    displayManager.setButtonPins(2, 3);
    
    // Create components
    text = new TextView("Hello World");
    text->setPosition(10, 10);
    displayManager.addComponent(text);
    
    menu = new Navigation();
    menu->addItem("Item 1");
    menu->addItem("Item 2");
    displayManager.addComponent(menu);
}

void loop() {
    // Update display and handle buttons
    displayManager.update();
    
    if (displayManager.isButton1Pressed()) {
        menu->selectNext();
    }
    
    if (displayManager.isButton2Pressed()) {
        menu->selectPrevious();
    }
    
    delay(100);
}
```

## Best Practices

1. **Initialization**
   - Always call `begin()` before using the display
   - Set configuration options before adding components

2. **Component Management**
   - Add components in the correct order (background to foreground)
   - Remove components when they are no longer needed
   - Use unique IDs for components

3. **Performance**
   - Minimize the number of components
   - Use appropriate update intervals
   - Consider memory constraints

4. **Error Handling**
   - Check for initialization errors
   - Handle component allocation failures
   - Implement proper cleanup

5. **Screen Saver**
   - Configure appropriate timeout
   - Use callbacks to handle state changes
   - Test with different patterns 