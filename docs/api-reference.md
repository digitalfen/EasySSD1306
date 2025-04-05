# API Reference

## DisplayManager

### Constructor

```cpp
DisplayManager(DisplayResolution resolution);
```

Creates a new display manager instance with the specified resolution.

Parameters:
- `resolution`: Display resolution (RESOLUTION_128x64 or RESOLUTION_128x32)

### Methods

#### void begin()
Initializes the display and configures button pins.

#### void setButtons(uint8_t up, uint8_t down)
Configures the navigation button pins.

Parameters:
- `up`: Up button pin
- `down`: Down button pin

#### void render()
Updates the screen and current state of the display. This method should be called in the main loop.

#### void addComponent(IDisplayComponent *component)
Adds a component to the current display state.

Parameters:
- `component`: Pointer to the component to be added

#### void setState(unsigned int n)
Sets the current state of the display.

Parameters:
- `n`: ID of the new state

### Static Variables

#### int selectedItem
Index of the currently selected item.

#### bool confirmItem
Flag indicating if the current item has been confirmed.

#### bool cancelItem
Flag indicating if the current operation has been cancelled.

## Components

### TextView

#### Constructor
```cpp
TextView(const char* text, uint8_t x, uint8_t y);
```

Creates a new text component.

Parameters:
- `text`: Text to be displayed
- `x`: X position of the text
- `y`: Y position of the text

#### Methods

##### void setText(const char* text)
Sets the component's text.

##### void setPosition(uint8_t x, uint8_t y)
Sets the text position.

##### void render(Adafruit_SSD1306* display)
Renders the text on the display.

### Navigation

Component for creating menus and navigation interfaces.

#### Constructor
```cpp
Navigation(const char* title)
```

#### Methods
```cpp
void addItem(const char* label, const char* value)
void removeItem(int index)
void clearItems()
void selectItem(int index)
void nextItem()
void previousItem()
```

### LoadAnimation

Component for displaying loading animations.

#### Constructor
```cpp
LoadAnimation(const char* text)
```

#### Methods
```cpp
void start()
void stop()
void setText(const char* text)
void setPosition(int x, int y)
```

### Alert

Component for displaying notifications and alerts.

#### Constructor
```cpp
Alert(const char* title, const char* message)
```

#### Methods
```cpp
void show()
void hide()
void dismiss()
void setDuration(unsigned long duration)
```

### ImageView

Component for displaying static images.

#### Constructor
```cpp
ImageView(const uint8_t* bitmap, int width, int height)
```

#### Methods
```cpp
void setImage(const uint8_t* bitmap, int width, int height)
void setPosition(int x, int y)
void setVisible(bool visible)
```

### ImageAnimation

Component for displaying animated images.

#### Constructor
```cpp
ImageAnimation(const uint8_t* bitmap, int width, int height)
```

#### Methods
```cpp
void start()
void stop()
void pause()
void resume()
void setSpeed(int speed)
```

### TextAnimation

Component for displaying animated text.

#### Constructor
```cpp
TextAnimation(const char* text)
```

#### Methods
```cpp
void start()
void stop()
void pause()
void resume()
void setSpeed(int speed)
```

### Prompt

Component for getting user input.

#### Constructor
```cpp
Prompt(const char* label, const char* initialValue)
```

#### Methods
```cpp
void start()
void stop()
void clear()
void setMaxLength(int length)
void setInputType(InputType type)
```

## Enums

### TextStyle
```cpp
enum TextStyle {
    NORMAL,
    BOLD,
    ITALIC,
    UNDERLINE
};
```

### InputType
```cpp
enum InputType {
    TEXT,
    NUMBER,
    PASSWORD
};
``` 