# Image View

The ImageView component displays static images on the OLED display.

## Usage

```cpp
#include <EasySSD1306.h>

void setup() {
    DisplayManager display(128, 64);
    
    // Create image component
    ImageView* image = new ImageView(bitmapData, width, height);
    image->setPosition(0, 0);
    
    display.addComponent(image);
    display.begin();
}

void loop() {
    display.update();
}
```

## Methods

- `setPosition(int x, int y)`: Set image position
- `setScale(float scale)`: Set image scale (default: 1.0)
- `setVisible(bool visible)`: Show/hide image
- `getWidth()`: Get image width
- `getHeight()`: Get image height

## Examples

### Basic Image Display

```cpp
#include <EasySSD1306.h>

// Image data (1-bit per pixel)
const uint8_t logo[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    // ... more image data ...
};

void setup() {
    DisplayManager display(128, 64);
    
    // Create logo component
    ImageView* logoImage = new ImageView(logo, 32, 32);
    logoImage->setPosition(48, 16);
    
    display.addComponent(logoImage);
    display.begin();
}

void loop() {
    display.update();
}
```

### Scaled Image

```cpp
#include <EasySSD1306.h>

void setup() {
    DisplayManager display(128, 64);
    
    // Create scaled image
    ImageView* image = new ImageView(bitmapData, 16, 16);
    image->setPosition(0, 0);
    image->setScale(2.0); // Double size
    
    display.addComponent(image);
    display.begin();
}

void loop() {
    display.update();
}
``` 