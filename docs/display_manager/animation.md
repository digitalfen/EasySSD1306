# Animation Settings

The Display Manager provides control over animation settings for all animated components. This page covers how to configure animation settings.

## Animation Control

The EasySSD1306 library provides methods to control animation behavior:

```cpp
// Get current animation speed
uint8_t getAnimationSpeed() const

// Pause all animations
void pauseAnimations()

// Resume all animations
void resumeAnimations()
```

## Setting the Animation Speed

The animation speed must be set when creating the Display Manager:

```cpp
// Default speed (5)
DisplayManager displayManager(128, 64);

// Custom speed (3 - faster than default)
DisplayManager displayManager(128, 64, ORIENTATION_NORMAL, COLOR_WHITE, FONT_5x7, 128, 3);
```

## Controlling Animation State

```cpp
// Pause all animations
displayManager.pauseAnimations();

// Resume all animations
displayManager.resumeAnimations();
```

## Complete Example

```cpp
#include <EasySSD1306.h>

void setup() {
    // Initialize display with custom animation speed
    DisplayManager displayManager(128, 64, ORIENTATION_NORMAL, COLOR_WHITE, FONT_5x7, 128, 3);

    // Create some animated components
    LoadAnimation loadAnim(64, 32);
    TextAnimation textAnim("Hello World", 64, 32);
    
    // Add components to display
    displayManager.addComponent(&loadAnim);
    displayManager.addComponent(&textAnim);

    // Pause animations
    displayManager.pauseAnimations();
    delay(1000);

    // Resume animations
    displayManager.resumeAnimations();
}

void loop() {
    // Your code here
}
```

## Best Practices

1. **Choose Appropriate Speed**
   - Speed 1-3: Fast animations, good for loading indicators
   - Speed 4-7: Medium speed, good for general use
   - Speed 8-10: Slow animations, good for emphasis

2. **Consider Performance**
   - Faster animations may consume more CPU
   - Slower animations may appear choppy
   - Test different speeds on your hardware

3. **User Experience**
   - Choose the appropriate speed for your use case
   - Consider pausing animations when not in view
   - Use consistent speeds across your application 