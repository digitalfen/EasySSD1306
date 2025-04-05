# DisplayColor Enum

The DisplayColor enum defines the available colors for the OLED display.

## Values

| Value | Description |
|-------|-------------|
| COLOR_BLACK | Black color |
| COLOR_WHITE | White color |
| COLOR_INVERTED | Inverted color |

## Usage

### Basic Usage
```cpp
DisplayManager manager(display);
manager.setColor(COLOR_WHITE);
```

### Dynamic Color
```cpp
void loop() {
  static int counter = 0;
  
  if (counter % 100 == 0) {
    DisplayColor color = (DisplayColor)(counter / 100 % 3);
    manager.setColor(color);
  }
  
  counter++;
  manager.update();
  delay(100);
}
```

## Methods

### setColor
```cpp
void setColor(DisplayColor color)
```
Sets the display color.

### getColor
```cpp
DisplayColor getColor()
```
Gets the current display color.

### setBackgroundColor
```cpp
void setBackgroundColor(DisplayColor color)
```
Sets the background color.

### setForegroundColor
```cpp
void setForegroundColor(DisplayColor color)
```
Sets the foreground color.

## Examples

### Multiple Colors
```cpp
void setup() {
  manager.begin();
  
  // Test all colors
  manager.setColor(COLOR_BLACK);
  delay(1000);
  
  manager.setColor(COLOR_WHITE);
  delay(1000);
  
  manager.setColor(COLOR_INVERTED);
  delay(1000);
}
```

### Color with Components
```cpp
void loop() {
  static int counter = 0;
  
  if (counter % 100 == 0) {
    DisplayColor color = (DisplayColor)(counter / 100 % 3);
    manager.setColor(color);
    
    // Update component colors
    text->setColor(color);
    image->setColor(color);
    alert->setColor(color);
  }
  
  counter++;
  manager.update();
  delay(100);
}
```

## Best Practices

1. Use appropriate colors for your application
2. Consider component visibility in different colors
3. Test all colors during development
4. Use consistent coloring across components
5. Consider memory usage in different colors
6. Test performance in different colors
7. Document color requirements 