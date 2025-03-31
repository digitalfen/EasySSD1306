# API Reference

Detailed information about the EasySSD1306 API.

## DisplayManager

The main class for managing the OLED display and its components.

### Constructor
```cpp
DisplayManager(int width, int height)
```

### Methods

#### Display Control
```cpp
void begin()
void update()
void clear()
```

#### Component Management
```cpp
void addComponent(Component* component)
void removeComponent(Component* component)
void removeAllComponents()
```

## Components

### TextView

Component for displaying static text.

#### Constructor
```cpp
TextView(const char* text)
```

#### Methods
```cpp
void setText(const char* text)
void setPosition(int x, int y)
void setStyle(TextStyle style)
void setVisible(bool visible)
```

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