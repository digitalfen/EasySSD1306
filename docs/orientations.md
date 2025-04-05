# Display Orientations

The EasySSD1306 library supports multiple display orientations. This document explains how to configure and use different orientations.

# Available Orientations

This document explains the available orientations in the EasySSD1306 library.

## Orientation Constants

- `ORIENTATION_NORMAL`: 0 degrees (default)
- `ORIENTATION_RIGHT`: 90 degrees clockwise
- `ORIENTATION_INVERTED`: 180 degrees
- `ORIENTATION_LEFT`: 270 degrees clockwise

## Setting Orientation

### Constructor

```cpp
DisplayManager display(RESOLUTION_128x64);
```

### Runtime Change

```cpp
void setup() {
  display.begin();
  
  if (!display.isInitialized()) {
    Serial.println("Failed to initialize display");
    return;
  }
  
  // Initial orientation
  display.setOrientation(ORIENTATION_NORMAL);
  display.update();
  
  delay(2000);
  
  // Change orientation
  display.setOrientation(ORIENTATION_RIGHT);
  display.update();
}
```

## Orientation and Components

Components automatically adapt to orientation changes:

```cpp
void setup() {
  display.begin();
  
  if (!display.isInitialized()) {
    Serial.println("Failed to initialize display");
    return;
  }
  
  TextView* text = new TextView("Hello World");
  display.addComponent(text);
  
  display.update();
  
  delay(2000);
  
  // Change orientation
  display.setOrientation(ORIENTATION_RIGHT);
  display.update();
}
```

## Orientation Change Example

```cpp
#include <EasySSD1306.h>

DisplayManager display(RESOLUTION_128x64);

void setup() {
  display.begin();
  
  if (!display.isInitialized()) {
    Serial.println("Failed to initialize display");
    return;
  }
  
  TextView* text = new TextView("Hello World");
  display.addComponent(text);
  
  display.update();
  
  delay(2000);
  
  // Cycle through orientations
  display.setOrientation(ORIENTATION_RIGHT);
  display.update();
  
  delay(2000);
  
  display.setOrientation(ORIENTATION_INVERTED);
  display.update();
  
  delay(2000);
  
  display.setOrientation(ORIENTATION_LEFT);
  display.update();
  
  delay(2000);
  
  display.setOrientation(ORIENTATION_NORMAL);
  display.update();
}

void loop() {
  display.update();
}
```

## Orientation Constants

The orientation constants are defined in an enum:

```cpp
enum DisplayOrientation {
  ORIENTATION_NORMAL,
  ORIENTATION_RIGHT,
  ORIENTATION_INVERTED,
  ORIENTATION_LEFT
};
```

## Helper Functions

### getOrientationDegrees()

```cpp
uint8_t getOrientationDegrees(DisplayOrientation orientation)
```

Returns the degrees of the specified orientation:
- `ORIENTATION_NORMAL`: 0 degrees
- `ORIENTATION_RIGHT`: 90 degrees
- `ORIENTATION_INVERTED`: 180 degrees
- `ORIENTATION_LEFT`: 270 degrees

## Orientation Change Callback

```cpp
void onOrientationChanged(DisplayOrientation newOrientation) {
  Serial.print("Orientation changed to: ");
  Serial.println(getOrientationDegrees(newOrientation));
}

void setup() {
  display.setOrientationChangedCallback(onOrientationChanged);
}
```

## Troubleshooting

1. Display not rotating
   - Check orientation value
   - Verify display update
   - Check component positions

2. Component positioning
   - Check orientation
   - Verify component creation
   - Update after changes

3. Memory issues
   - Reduce number of components
   - Use simpler styles
   - Check available memory

## Considerations by Orientation

### NORMAL
- **Advantages**:
  - Standard orientation
  - Most common use case
  - Natural reading direction
- **Limitations**:
  - May not fit all mounting positions
  - Limited flexibility

### RIGHT
- **Advantages**:
  - Good for vertical displays
  - Useful for specific layouts
  - Alternative viewing angle
- **Limitations**:
  - Text may be harder to read
  - Requires adjusted layout

### INVERTED
- **Advantages**:
  - Alternative mounting option
  - Useful for specific applications
  - Complete orientation change
- **Limitations**:
  - Text is upside down
  - Requires complete layout adjustment

### LEFT
- **Advantages**:
  - Alternative vertical orientation
  - Useful for specific layouts
  - Different viewing angle
- **Limitations**:
  - Text may be harder to read
  - Requires adjusted layout

## Best Practices

1. **Choose Appropriate Orientation**
   - Consider your application needs
   - Think about mounting position
   - Test readability in each orientation

2. **Layout Design**
   - Design for target orientation
   - Use relative positioning
   - Test in all orientations

3. **Text Handling**
   - Consider text readability
   - Adjust font sizes if needed
   - Test text alignment

4. **Component Placement**
   - Use auto-adapting components
   - Consider component positions
   - Test component layouts

## Example with Different Orientations

Here's a complete example demonstrating orientation changes:

```cpp
#include <EasySSD1306.h>

DisplayManager displayManager(128, 64);
TextView* text;

void setup() {
    displayManager.begin();
    
    text = new TextView("Orientation Test");
    text->setAutoAdapt(true);
    displayManager.addComponent(text);
}

void changeOrientation(DisplayOrientation orientation) {
    displayManager.setOrientation(orientation);
    
    const char* orientationName;
    switch(orientation) {
        case DisplayOrientation::NORMAL:
            orientationName = "Normal";
            break;
        case DisplayOrientation::RIGHT:
            orientationName = "Right";
            break;
        case DisplayOrientation::INVERTED:
            orientationName = "Inverted";
            break;
        case DisplayOrientation::LEFT:
            orientationName = "Left";
            break;
    }
    
    char buffer[32];
    sprintf(buffer, "Orientation: %s", orientationName);
    text->setText(buffer);
}

void loop() {
    // Cycle through orientations
    static int currentOrientation = 0;
    
    switch(currentOrientation) {
        case 0:
            changeOrientation(DisplayOrientation::NORMAL);
            break;
        case 1:
            changeOrientation(DisplayOrientation::RIGHT);
            break;
        case 2:
            changeOrientation(DisplayOrientation::INVERTED);
            break;
        case 3:
            changeOrientation(DisplayOrientation::LEFT);
            break;
    }
    
    currentOrientation = (currentOrientation + 1) % 4;
    delay(5000);
    
    displayManager.update();
    delay(100);
} 