# ImageView Component

The ImageView component displays bitmap images on the OLED display with various visual effects.

## Features

- Multiple image styles
- Image scaling
- Automatic centering
- Border styles (none, solid, rounded)
- Shadow effect
- Frame effect
- Inverted image option
- Automatic adaptation to display size and orientation

## Styles

| Style | Description |
|-------|-------------|
| IMG_STYLE_NORMAL | Standard image display |
| IMG_STYLE_BORDERED | Image with border |
| IMG_STYLE_ROUNDED | Image with rounded border |
| IMG_STYLE_INVERTED | Inverted image |
| IMG_STYLE_SHADOW | Image with shadow |
| IMG_STYLE_FRAME | Image with frame |

## Usage

### Basic Usage
```cpp
ImageView* image = new ImageView(logoBitmap);
manager.addComponent(image);
```

### Usage with Style
```cpp
ImageView* image = new ImageView(logoBitmap, IMG_STYLE_BORDERED);
image->setScale(2);
image->setPosition(10, 10);
manager.addComponent(image);
```

### Dynamic Image
```cpp
void loop() {
  static int counter = 0;
  image->setStyle(counter % 6);
  counter++;
  manager.update();
  delay(1000);
}
```

## Methods

### Constructor
```cpp
ImageView(const uint8_t* bitmap, ImageViewStyle style = IMG_STYLE_NORMAL)
```
Creates a new image view with the specified bitmap and style.

### setScale
```cpp
void setScale(int scale)
```
Sets the image scale (1-4).

### setStyle
```cpp
void setStyle(ImageViewStyle style)
```
Sets the image style.

### setBorderColor
```cpp
void setBorderColor(int color)
```
Sets the border color.

### setShadowOffset
```cpp
void setShadowOffset(int offset)
```
Sets the shadow offset.

### setAutoCenter
```cpp
void setAutoCenter(bool autoCenter)
```
Enables or disables automatic centering.

### setPosition
```cpp
void setPosition(int x, int y)
```
Sets the image position.

### setAutoAdapt
```cpp
void setAutoAdapt(bool autoAdapt)
```
Enables or disables automatic adaptation to display changes.

## Examples

### Multiple Styles
```cpp
void setup() {
  ImageView* normalImage = new ImageView(logoBitmap, IMG_STYLE_NORMAL);
  ImageView* borderedImage = new ImageView(logoBitmap, IMG_STYLE_BORDERED);
  ImageView* roundedImage = new ImageView(logoBitmap, IMG_STYLE_ROUNDED);
  
  normalImage->setPosition(0, 0);
  borderedImage->setPosition(40, 0);
  roundedImage->setPosition(80, 0);
  
  manager.addComponent(normalImage);
  manager.addComponent(borderedImage);
  manager.addComponent(roundedImage);
}
```

### Animated Images
```cpp
void loop() {
  static int frame = 0;
  image->setBitmap(animationFrames[frame]);
  frame = (frame + 1) % NUM_FRAMES;
  manager.update();
  delay(100);
}
```

## Best Practices

1. Use appropriate image sizes
2. Consider scaling for different resolutions
3. Use styles consistently
4. Position images carefully
5. Consider automatic adaptation
6. Test images in different orientations
7. Optimize image data for memory usage 