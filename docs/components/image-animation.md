# ImageAnimation Component

The ImageAnimation component creates animated image effects.

## Usage

```cpp
#include <EasySSD1306.h>

void setup() {
    DisplayManager display(128, 64);
    ImageAnimation* anim = new ImageAnimation(logoBitmap, 32, 32);
    anim->setPosition(0, 0);
    anim->setSpeed(1);
    display.addComponent(anim);
    display.begin();
}
```

## Methods

### Constructor
```cpp
ImageAnimation(const uint8_t* bitmap, int width, int height)
```

### Animation Control
```cpp
void start()
void stop()
void pause()
void resume()
bool isRunning()
```

### Image
```cpp
void setImage(const uint8_t* bitmap, int width, int height)
const uint8_t* getBitmap()
int getWidth()
int getHeight()
```

### Position
```cpp
void setPosition(int x, int y)
int getX()
int getY()
```

### Speed
```cpp
void setSpeed(int speed)
int getSpeed()
```

## Examples

### Fade Animation
```cpp
void setup() {
    DisplayManager display(128, 64);
    
    ImageAnimation* logo = new ImageAnimation(logoBitmap, 32, 32);
    logo->setPosition(48, 16);  // Center the logo
    logo->setSpeed(2);
    
    TextView* title = new TextView("Loading...");
    title->setPosition(0, 48);
    
    display.addComponent(logo);
    display.addComponent(title);
    display.begin();
    
    logo->start();
}
```

### Multiple Animations
```cpp
void setup() {
    DisplayManager display(128, 64);
    
    ImageAnimation* icon1 = new ImageAnimation(icon1Bitmap, 16, 16);
    icon1->setPosition(0, 0);
    icon1->setSpeed(1);
    
    ImageAnimation* icon2 = new ImageAnimation(icon2Bitmap, 16, 16);
    icon2->setPosition(16, 0);
    icon2->setSpeed(1);
    
    display.addComponent(icon1);
    display.addComponent(icon2);
    display.begin();
    
    icon1->start();
    icon2->start();
}
``` 