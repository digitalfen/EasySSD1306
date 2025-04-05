# DisplayManager Component

The DisplayManager is the main component that manages the OLED display and its components.

## Features

- Component management
- Display updates
- Resolution and orientation configuration
- Screen saver
- Memory management
- Automatic adaptation

## Usage

### Basic Configuration

```cpp
#include <EasySSD1306.h>

DisplayManager display(RESOLUTION_128x64);

void setup() {
    display.begin();
}

void loop() {
    display.render();  // Atualiza a tela e o estado atual
}
```

### With Screen Saver

```cpp
void setup() {
    displayManager.begin();
    
    // Configure screen saver
    ScreenSaver* screensaver = new ScreenSaver();
    screensaver->setTimeout(300000); // 5 minutes
    screensaver->setStyle(ScreenSaverStyle::ANIMATION);
    displayManager.setScreenSaver(screensaver);
}
```

## Methods

### Constructor
```cpp
DisplayManager(DisplayResolution resolution)
```
Creates a new DisplayManager with the specified resolution.

### begin
```cpp
void begin()
```
Initializes the display and configures necessary components.

### render
```cpp
void render()
```
Atualiza a tela e o estado atual, incluindo o estado dos botões e componentes.

### addComponent
```cpp
void addComponent(IDisplayComponent* component)
```
Adds a component to the manager.

### removeComponent
```cpp
void removeComponent(IDisplayComponent* component)
```
Removes a component from the manager.

### setOrientation
```cpp
void setOrientation(DisplayOrientation orientation)
```
Sets the display orientation.

### getOrientation
```cpp
DisplayOrientation getOrientation()
```
Returns the current display orientation.

### setResolution
```cpp
void setResolution(DisplayResolution resolution)
```
Sets the display resolution.

### getResolution
```cpp
DisplayResolution getResolution()
```
Returns the current display resolution.

### setScreenSaver
```cpp
void setScreenSaver(ScreenSaver* screensaver)
```
Sets the screen saver component.

### getScreenSaver
```cpp
ScreenSaver* getScreenSaver()
```
Returns the current screen saver component.

### resetScreenSaver
```cpp
void resetScreenSaver()
```
Resets the screen saver timer.

## Complete Example

```cpp
#include <EasySSD1306.h>

DisplayManager displayManager(128, 64);
TextView* text;
ScreenSaver* screensaver;

void setup() {
    displayManager.begin();
    
    // Create text
    text = new TextView("Hello World");
    text->setPosition(10, 10);
    displayManager.addComponent(text);
    
    // Configure screen saver
    screensaver = new ScreenSaver();
    screensaver->setTimeout(180000); // 3 minutes
    screensaver->setStyle(ScreenSaverStyle::ANIMATION);
    displayManager.setScreenSaver(screensaver);
}

void loop() {
    // Update display
    displayManager.render();
    
    // Check buttons
    if (digitalRead(BUTTON_PIN) == LOW) {
        displayManager.resetScreenSaver();
    }
    
    delay(100);
}
```

## Best Practices

1. **Component Management**
   - Add components before starting the display
   - Remove components when no longer needed
   - Manage memory properly

2. **Screen Saver**
   - Configure appropriate inactivity timeout
   - Choose a suitable style for your application
   - Test user interaction

3. **Performance**
   - Minimize unnecessary updates
   - Use appropriate intervals
   - Consider power consumption

4. **Orientation and Resolution**
   - Configure correctly for your display
   - Test in different configurations
   - Consider hardware limitations 