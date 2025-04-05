# DisplayResolution Enum

The DisplayResolution enum defines the supported resolutions for the OLED display.

## Values

| Value | Description |
|-------|-------------|
| RESOLUTION_128x64 | 128x64 pixels |
| RESOLUTION_128x32 | 128x32 pixels |
| RESOLUTION_96x16 | 96x16 pixels |
| RESOLUTION_64x48 | 64x48 pixels |
| RESOLUTION_64x32 | 64x32 pixels |

## Usage

### Basic Usage
```cpp
DisplayManager manager(display);
manager.setResolution(RESOLUTION_128x64);
```

### Dynamic Resolution
```cpp
void loop() {
  static int counter = 0;
  
  if (counter % 100 == 0) {
    DisplayResolution resolution = (DisplayResolution)(counter / 100 % 5);
    manager.setResolution(resolution);
  }
  
  counter++;
  manager.update();
  delay(100);
}
```

## Methods

### setResolution
```cpp
void setResolution(DisplayResolution resolution)
```
Sets the display resolution.

### getResolution
```cpp
DisplayResolution getResolution()
```
Gets the current display resolution.

### getWidth
```cpp
int getWidth()
```
Gets the display width.

### getHeight
```cpp
int getHeight()
```
Gets the display height.

## Examples

### Multiple Resolutions
```cpp
void setup() {
  manager.begin();
  
  // Test all resolutions
  manager.setResolution(RESOLUTION_128x64);
  delay(1000);
  
  manager.setResolution(RESOLUTION_128x32);
  delay(1000);
  
  manager.setResolution(RESOLUTION_96x16);
  delay(1000);
  
  manager.setResolution(RESOLUTION_64x48);
  delay(1000);
  
  manager.setResolution(RESOLUTION_64x32);
  delay(1000);
}
```

### Resolution with Components
```cpp
void loop() {
  static int counter = 0;
  
  if (counter % 100 == 0) {
    DisplayResolution resolution = (DisplayResolution)(counter / 100 % 5);
    manager.setResolution(resolution);
    
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

1. Use appropriate resolutions for your application
2. Consider component sizing in different resolutions
3. Test all resolutions during development
4. Use automatic adaptation when possible
5. Consider memory usage in different resolutions
6. Test performance in different resolutions
7. Document resolution requirements 