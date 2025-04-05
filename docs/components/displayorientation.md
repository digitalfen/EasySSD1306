# DisplayOrientation Enum

The DisplayOrientation enum defines the possible orientations for the OLED display.

## Values

| Value | Description |
|-------|-------------|
| ORIENTATION_NORMAL | Normal orientation (0 degrees) |
| ORIENTATION_RIGHT | Rotated 90 degrees clockwise |
| ORIENTATION_INVERTED | Rotated 180 degrees |
| ORIENTATION_LEFT | Rotated 90 degrees counterclockwise |

## Usage

### Basic Usage
```cpp
DisplayManager manager(display);
manager.setOrientation(ORIENTATION_NORMAL);
```

### Dynamic Orientation
```cpp
void loop() {
  static int counter = 0;
  
  if (counter % 100 == 0) {
    DisplayOrientation orientation = (DisplayOrientation)(counter / 100 % 4);
    manager.setOrientation(orientation);
  }
  
  counter++;
  manager.update();
  delay(100);
}
```

## Methods

### setOrientation
```cpp
void setOrientation(DisplayOrientation orientation)
```
Sets the display orientation.

### getOrientation
```cpp
DisplayOrientation getOrientation()
```
Gets the current display orientation.

## Examples

### Multiple Orientations
```cpp
void setup() {
  manager.begin();
  
  // Test all orientations
  manager.setOrientation(ORIENTATION_NORMAL);
  delay(1000);
  
  manager.setOrientation(ORIENTATION_RIGHT);
  delay(1000);
  
  manager.setOrientation(ORIENTATION_INVERTED);
  delay(1000);
  
  manager.setOrientation(ORIENTATION_LEFT);
  delay(1000);
}
```

### Orientation with Components
```cpp
void loop() {
  static int counter = 0;
  
  if (counter % 100 == 0) {
    DisplayOrientation orientation = (DisplayOrientation)(counter / 100 % 4);
    manager.setOrientation(orientation);
    
    // Update component positions
    text->setPosition(0, 0);
    image->setPosition(40, 0);
    alert->setPosition(80, 0);
  }
  
  counter++;
  manager.update();
  delay(100);
}
```

## Best Practices

1. Use appropriate orientations for your application
2. Consider component positioning in different orientations
3. Test all orientations during development
4. Use automatic adaptation when possible
5. Consider memory usage in different orientations
6. Test performance in different orientations
7. Document orientation requirements 