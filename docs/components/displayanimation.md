# DisplayAnimation Enum

The DisplayAnimation enum defines the available animations for the OLED display.

## Values

| Value | Description |
|-------|-------------|
| ANIMATION_NONE | No animation |
| ANIMATION_FADE | Fade animation |
| ANIMATION_SLIDE | Slide animation |
| ANIMATION_BLINK | Blink animation |
| ANIMATION_SCROLL | Scroll animation |
| ANIMATION_ROTATE | Rotate animation |
| ANIMATION_ZOOM | Zoom animation |
| ANIMATION_BOUNCE | Bounce animation |

## Usage

### Basic Usage
```cpp
DisplayManager manager(display);
manager.setAnimation(ANIMATION_FADE);
```

### Dynamic Animation
```cpp
void loop() {
  static int counter = 0;
  
  if (counter % 100 == 0) {
    DisplayAnimation animation = (DisplayAnimation)(counter / 100 % 8);
    manager.setAnimation(animation);
  }
  
  counter++;
  manager.update();
  delay(100);
}
```

## Methods

### setAnimation
```cpp
void setAnimation(DisplayAnimation animation)
```
Sets the display animation.

### getAnimation
```cpp
DisplayAnimation getAnimation()
```
Gets the current display animation.

### setAnimationSpeed
```cpp
void setAnimationSpeed(int speed)
```
Sets the animation speed in milliseconds.

### getAnimationSpeed
```cpp
int getAnimationSpeed()
```
Gets the current animation speed.

## Examples

### Multiple Animations
```cpp
void setup() {
  manager.begin();
  
  // Test all animations
  manager.setAnimation(ANIMATION_FADE);
  delay(1000);
  
  manager.setAnimation(ANIMATION_SLIDE);
  delay(1000);
  
  manager.setAnimation(ANIMATION_BLINK);
  delay(1000);
  
  manager.setAnimation(ANIMATION_SCROLL);
  delay(1000);
  
  manager.setAnimation(ANIMATION_ROTATE);
  delay(1000);
  
  manager.setAnimation(ANIMATION_ZOOM);
  delay(1000);
  
  manager.setAnimation(ANIMATION_BOUNCE);
  delay(1000);
}
```

### Animation with Components
```cpp
void loop() {
  static int counter = 0;
  
  if (counter % 100 == 0) {
    DisplayAnimation animation = (DisplayAnimation)(counter / 100 % 8);
    manager.setAnimation(animation);
    
    // Update component animations
    text->setAnimation(animation);
    image->setAnimation(animation);
    alert->setAnimation(animation);
  }
  
  counter++;
  manager.update();
  delay(100);
}
```

## Best Practices

1. Use appropriate animations for your application
2. Consider animation speed and smoothness
3. Test all animations during development
4. Use consistent animations across components
5. Consider memory usage in different animations
6. Test performance in different animations
7. Document animation requirements 