# DisplayFont Enum

The DisplayFont enum defines the available fonts for the OLED display.

## Values

| Value | Description |
|-------|-------------|
| FONT_SMALL | Small font (5x7) |
| FONT_MEDIUM | Medium font (8x12) |
| FONT_LARGE | Large font (12x16) |
| FONT_XLARGE | Extra large font (16x24) |

## Usage

### Basic Usage
```cpp
DisplayManager manager(display);
manager.setFont(FONT_MEDIUM);
```

### Dynamic Font
```cpp
void loop() {
  static int counter = 0;
  
  if (counter % 100 == 0) {
    DisplayFont font = (DisplayFont)(counter / 100 % 4);
    manager.setFont(font);
  }
  
  counter++;
  manager.update();
  delay(100);
}
```

## Methods

### setFont
```cpp
void setFont(DisplayFont font)
```
Sets the display font.

### getFont
```cpp
DisplayFont getFont()
```
Gets the current display font.

### setFontSize
```cpp
void setFontSize(int size)
```
Sets the font size (1-4).

### getFontSize
```cpp
int getFontSize()
```
Gets the current font size.

## Examples

### Multiple Fonts
```cpp
void setup() {
  manager.begin();
  
  // Test all fonts
  manager.setFont(FONT_SMALL);
  delay(1000);
  
  manager.setFont(FONT_MEDIUM);
  delay(1000);
  
  manager.setFont(FONT_LARGE);
  delay(1000);
  
  manager.setFont(FONT_XLARGE);
  delay(1000);
}
```

### Font with Components
```cpp
void loop() {
  static int counter = 0;
  
  if (counter % 100 == 0) {
    DisplayFont font = (DisplayFont)(counter / 100 % 4);
    manager.setFont(font);
    
    // Update component fonts
    text->setFont(font);
    alert->setFont(font);
  }
  
  counter++;
  manager.update();
  delay(100);
}
```

## Best Practices

1. Use appropriate fonts for your application
2. Consider text readability in different fonts
3. Test all fonts during development
4. Use consistent fonts across components
5. Consider memory usage in different fonts
6. Test performance in different fonts
7. Document font requirements 