# ScreenSaver

The ScreenSaver is a display protection feature that automatically shows a custom component after a period of inactivity.

## Features

- Automatic activation after configurable timeout
- Support for any component (image, animation, text, etc.)
- Easy activation/deactivation
- Automatic timer reset on button press

## Basic Usage

```cpp
#include <EasySSD1306.h>

DisplayManager display(RESOLUTION_128x64);
ImageView* screensaverImage;
LoadAnimation* screensaverAnimation;

void setup() {
    display.begin();
    
    // Create your screensaver component
    screensaverImage = new ImageView(myBitmap);
    // or
    screensaverAnimation = new LoadAnimation();
    
    // Configure screensaver with 5 minutes timeout
    display.setScreenSaver(screensaverImage, 5);
    // or
    display.setScreenSaver(screensaverAnimation, 5);
}

void loop() {
    display.update();
    
    // Reset screensaver timer on any button press
    if (digitalRead(BUTTON_PIN) == LOW) {
        display.resetScreenSaver();
    }
    
    delay(100);
}
```

## DisplayManager Methods

- `setScreenSaver(Component* component, int minutes)`
  Sets the screensaver component and timeout in minutes.
  ```cpp
  display.setScreenSaver(myComponent, 3); // 3 minutes timeout
  ```

- `getScreenSaver()`
  Gets the current screensaver component.
  ```cpp
  Component* screensaver = display.getScreenSaver();
  ```

- `resetScreenSaver()`
  Resets the screensaver timer.
  ```cpp
  display.resetScreenSaver();
  ```

## Best Practices

1. **Component Selection**
   - Choose appropriate components for your screensaver
   - Consider power consumption
   - Test different components

2. **Timeout Configuration**
   - Set reasonable timeout values
   - Consider user interaction patterns
   - Test in real usage scenarios

3. **Performance**
   - Use lightweight components
   - Minimize updates
   - Consider display refresh rate

4. **User Experience**
   - Provide clear visual feedback
   - Ensure easy reactivation
   - Test with different components

## Complete Example

```cpp
#include <EasySSD1306.h>

DisplayManager display(RESOLUTION_128x64);
TextView* mainText;
LoadAnimation* screensaver;

void setup() {
    display.begin();
    
    // Create main text
    mainText = new TextView("System Active");
    mainText->setPosition(10, 10);
    display.addComponent(mainText);
    
    // Create screensaver animation
    screensaver = new LoadAnimation();
    screensaver->setStyle(LoadAnimationStyle::SPINNER);
    screensaver->setSpeed(100);
    
    // Configure screensaver with 3 minutes timeout
    display.setScreenSaver(screensaver, 3);
}

void loop() {
    display.update();
    
    // Reset screensaver timer on any button press
    if (digitalRead(BUTTON_PIN) == LOW) {
        display.resetScreenSaver();
    }
    
    delay(100);
}
``` 