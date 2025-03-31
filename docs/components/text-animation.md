# TextAnimation Component

The TextAnimation component creates animated text effects.

## Usage

```cpp
#include <EasySSD1306.h>

void setup() {
    DisplayManager display(128, 64);
    TextAnimation* text = new TextAnimation("Scrolling Text");
    text->setPosition(0, 0);
    text->setSpeed(1);
    display.addComponent(text);
    display.begin();
}
```

## Methods

### Constructor
```cpp
TextAnimation(const char* text)
```

### Animation Control
```cpp
void start()
void stop()
void pause()
void resume()
bool isRunning()
```

### Text
```cpp
void setText(const char* text)
const char* getText()
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

### Scrolling Text
```cpp
void setup() {
    DisplayManager display(128, 64);
    
    TextAnimation* scroll = new TextAnimation("This is a scrolling text message");
    scroll->setPosition(0, 0);
    scroll->setSpeed(2);
    
    display.addComponent(scroll);
    display.begin();
    
    scroll->start();
}
```

### Multiple Animations
```cpp
void setup() {
    DisplayManager display(128, 64);
    
    TextAnimation* title = new TextAnimation("Welcome");
    title->setPosition(0, 0);
    title->setSpeed(1);
    
    TextAnimation* message = new TextAnimation("Please wait...");
    message->setPosition(0, 32);
    message->setSpeed(1);
    
    display.addComponent(title);
    display.addComponent(message);
    display.begin();
    
    title->start();
    message->start();
} 