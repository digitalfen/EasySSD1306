# Display Orientation

The Display Manager allows you to configure the orientation of the OLED display. This page covers how to set and work with different display orientations.

## Available Orientations

The EasySSD1306 library supports the following orientations:

```cpp
enum DisplayOrientation {
    ORIENTATION_NORMAL,   // 0 degrees (default)
    ORIENTATION_RIGHT,    // 90 degrees clockwise
    ORIENTATION_INVERTED, // 180 degrees
    ORIENTATION_LEFT      // 270 degrees clockwise (90 degrees counterclockwise)
};
```

## Setting the Orientation

### Constructor

You can set the orientation when creating the Display Manager:

```cpp
// Default orientation (normal)
DisplayManager displayManager;

// Custom orientation
DisplayManager displayManager(128, 64, ORIENTATION_RIGHT);

// New constructor with resolution
DisplayManager display(RESOLUTION_128x64);
```

### After Initialization

You can also change the orientation after the Display Manager has been initialized:

```cpp
void setOrientation(DisplayOrientation orientation)
```

## Getting the Current Orientation

```cpp
DisplayOrientation getOrientation() const
```

Returns the current orientation as a `DisplayOrientation` enum value.

## Orientation Change Events

You can register a callback function to be called when the orientation changes:

```cpp
void onOrientationChanged(std::function<void(DisplayOrientation)> callback)
```

## Adapting Components to Orientation

Components can adapt to orientation changes by overriding the `adaptToOrientation` method:

```cpp
void adaptToOrientation(DisplayOrientation orientation) override {
    // Adjust component based on new orientation
    switch(orientation) {
        case ORIENTATION_NORMAL:
            // Adjust for normal orientation
            break;
        case ORIENTATION_RIGHT:
            // Adjust for right orientation
            break;
        case ORIENTATION_INVERTED:
            // Adjust for inverted orientation
            break;
        case ORIENTATION_LEFT:
            // Adjust for left orientation
            break;
    }
}
```

## Helper Functions

The library provides helper functions to work with orientations:

```cpp
uint8_t getOrientationDegrees(DisplayOrientation orientation)
```

This function returns the rotation in degrees for a given orientation.

## Complete Example

```cpp
#include <EasySSD1306.h>

DisplayManager displayManager;

void setup() {
    displayManager.begin();
    
    // Set orientation change callback
    displayManager.onOrientationChanged([](DisplayOrientation orient) {
        Serial.print("Orientation changed to: ");
        Serial.println(orient);
    });
    
    // Change orientation
    displayManager.setOrientation(ORIENTATION_RIGHT);
    
    // Get current orientation
    DisplayOrientation current = displayManager.getOrientation();
    Serial.print("Current orientation: ");
    Serial.println(current);
    
    // Create components that adapt to orientation
    TextView* text = new TextView("Hello World");
    text->setPosition(10, 10);
    displayManager.addComponent(text);
}

void loop() {
    displayManager.update();
    delay(100);
}
```

## Automatic Orientation Detection

The library can automatically detect the orientation using an MPU6050 sensor:

```cpp
#include <EasySSD1306.h>
#include <OrientationSensor.h>

DisplayManager displayManager;
OrientationSensor orientationSensor;

void setup() {
    displayManager.begin();
    orientationSensor.begin();
    
    // Set up automatic orientation detection
    orientationSensor.setAutoOrientation(true);
    orientationSensor.setDisplayManager(&displayManager);
}

void loop() {
    // Update orientation sensor
    orientationSensor.update();
    
    // Update display
    displayManager.update();
    delay(100);
}
```

## Best Practices

1. **Choose the Right Orientation**
   - Select an orientation that makes sense for your application
   - Consider how users will interact with the display

2. **Adapt Components**
   - Make sure components adapt to different orientations
   - Test your UI in all orientations

3. **Handle Orientation Changes**
   - Use the `onOrientationChanged` callback to respond to orientation changes
   - Update component layouts when orientation changes

4. **Consider Resolution**
   - Remember that orientation changes affect how resolution is interpreted
   - Test your UI with different resolution and orientation combinations

5. **Automatic Orientation**
   - Use automatic orientation detection for a better user experience
   - Ensure the sensor is properly calibrated 