# Component Base Class

The `Component` class is the base class for all display components in the EasySSD1306 library. It provides the fundamental structure and common functionality that all components must have.

## Overview

The `Component` class is designed to be inherited by custom components. It provides:

- Position and size management
- Visibility control
- Automatic adaptation to resolution and orientation changes
- Event handling
- Memory management

## Implementing Custom Components

### Basic Structure

To create a custom component, you must inherit from the `Component` class and implement the necessary virtual methods:

```cpp
#include <EasySSD1306.h>

class MyComponent : public Component {
public:
    // Constructor
    MyComponent() : Component() {
        // Component-specific initialization
    }
    
    // Required rendering method
    void render(Adafruit_SSD1306& display) override {
        if (!isVisible()) return;
        
        // Component-specific rendering code
        int x, y;
        getPosition(x, y);
        
        display.setCursor(x, y);
        display.print("My Component");
    }
    
    // Optional adaptation methods
    void adaptToResolution(int width, int height) override {
        // Logic to adapt the component to resolution
        Component::adaptToResolution(width, height);
        
        // Component-specific adjustments
        if (width < 128) {
            // Adjust for smaller screens
        }
    }
    
    void adaptToOrientation(DisplayOrientation orientation) override {
        // Logic to adapt the component to orientation
        Component::adaptToOrientation(orientation);
        
        // Component-specific adjustments
        switch(orientation) {
            case ORIENTATION_NORMAL:
                // Adjust for normal orientation
                break;
            case ORIENTATION_RIGHT:
                // Adjust for right orientation
                break;
            // Other cases...
        }
    }
};
```

### Component Lifecycle

1. **Creation**: The component is instantiated using `new`
2. **Configuration**: Properties such as position, size, and visibility are set
3. **Addition to DisplayManager**: The component is added to the display manager
4. **Rendering**: The `render()` method is called periodically by the `DisplayManager`
5. **Adaptation**: The `adaptToResolution()` and `adaptToOrientation()` methods are called when needed
6. **Destruction**: The component is destroyed when it is no longer needed

### Complete Example: Counter Component

```cpp
#include <EasySSD1306.h>

class Counter : public Component {
private:
    int value;
    int increment;
    unsigned long lastUpdate;
    unsigned long updateInterval;
    
public:
    Counter(int initialValue = 0, int increment = 1, unsigned long interval = 1000) 
        : Component(), value(initialValue), increment(increment), 
          lastUpdate(0), updateInterval(interval) {}
    
    void setValue(int newValue) {
        value = newValue;
    }
    
    void setIncrement(int newIncrement) {
        increment = newIncrement;
    }
    
    void setInterval(unsigned long newInterval) {
        updateInterval = newInterval;
    }
    
    void render(Adafruit_SSD1306& display) override {
        if (!isVisible()) return;
        
        // Update value based on interval
        unsigned long currentTime = millis();
        if (currentTime - lastUpdate >= updateInterval) {
            value += increment;
            lastUpdate = currentTime;
        }
        
        // Get current position
        int x, y;
        getPosition(x, y);
        
        // Render counter
        display.setTextSize(2);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(x, y);
        display.print(value);
    }
    
    void adaptToResolution(int width, int height) override {
        Component::adaptToResolution(width, height);
        
        // Adjust text size based on resolution
        if (width < 64) {
            // For smaller screens, use smaller text
            displayManager.getDisplay().setTextSize(1);
        } else {
            displayManager.getDisplay().setTextSize(2);
        }
    }
};

void setup() {
    displayManager.begin();
    
    // Create and configure the component
    Counter* counter = new Counter(0, 1, 1000);
    counter->setPosition(10, 10);
    counter->setVisible(true);
    
    // Add to display manager
    displayManager.addComponent(counter);
}

void loop() {
    displayManager.update();
    delay(100);
}
```

## Main Methods

### Constructor
```cpp
Component()
```
Creates a new component. You can add specific parameters to your custom component's constructor.

### render
```cpp
virtual void render(Adafruit_SSD1306& display)
```
Main method that must be overridden to draw the component on the screen. This method is called by the `DisplayManager` during each update cycle.

### adaptToResolution
```cpp
virtual void adaptToResolution(int width, int height)
```
Method called when the display resolution changes. Override to adjust the component to the new resolution.

### adaptToOrientation
```cpp
virtual void adaptToOrientation(DisplayOrientation orientation)
```
Method called when the display orientation changes. Override to adjust the component to the new orientation.

### Position and Size Management
```cpp
void setPosition(int x, int y)
void getPosition(int& x, int& y)
void setSize(int width, int height)
void getSize(int& width, int& height)
```
Methods to manage the component's position and size.

### Visibility Control
```cpp
void setVisible(bool visible)
bool isVisible()
```
Methods to control the component's visibility.

### Automatic Adaptation
```cpp
void setAutoAdapt(bool autoAdapt)
bool getAutoAdapt()
```
Methods to control whether the component automatically adapts to resolution and orientation changes.

## Best Practices

1. **Override Only What's Necessary**
   - Implement only the virtual methods your component actually needs
   - Call base class methods when appropriate

2. **Memory Management**
   - Use `new` to create components dynamically
   - The `DisplayManager` handles memory deallocation when the component is removed

3. **Rendering Optimization**
   - Check visibility before rendering
   - Minimize unnecessary drawing operations
   - Use `setTextSize()` and `setTextColor()` only when needed

4. **Adaptation to Different Configurations**
   - Test your component at different resolutions
   - Verify behavior in different orientations
   - Consider memory and processing limitations

5. **Interaction with Other Components**
   - Use unique IDs to identify components
   - Implement callbacks for component communication
   - Consider rendering order

## Debugging Tips

1. Use `Serial.print()` to debug component behavior
2. Verify the component is properly added to the `DisplayManager`
3. Confirm the `render()` method is being called
4. Test component visibility and position
5. Verify resolution and orientation adaptation is working correctly 