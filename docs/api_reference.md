# API Reference

This document provides a reference for the EasySSD1306 library API.

## DisplayManager

The main class for managing the OLED display.

### Constructor

```cpp
DisplayManager(DisplayResolution resolution)
```
Creates a new display manager with the specified resolution.

### Initialization

```cpp
void begin();
bool isInitialized();
```

### Display Configuration

```cpp
void setOrientation(DisplayOrientation orientation);
DisplayOrientation getOrientation();

void setColor(DisplayColor color);
DisplayColor getColor();

void setFont(DisplayFont font);
DisplayFont getFont();

void setContrast(uint8_t contrast);
uint8_t getContrast();

void setAnimationSpeed(uint8_t speed);
uint8_t getAnimationSpeed();
```

### Resolution

```cpp
void setResolution(DisplayResolution resolution);
DisplayResolution getResolution();
uint8_t getWidth();
uint8_t getHeight();
```

### I2C Configuration

```cpp
void setI2CPins(uint8_t sda, uint8_t scl);
void setI2CAddress(uint8_t address);
```

### Button Configuration

```cpp
void setButtonPins(uint8_t up, uint8_t down);
bool isButton1Pressed();
bool isButton2Pressed();
bool wasButton1Pressed();
bool wasButton2Pressed();
```

### Component Management

```cpp
void addComponent(IDisplayComponent* component);
void removeComponent(Component* component);
void clearComponents();
```

### Display Update

```cpp
void render();  // Atualiza a tela e o estado atual
```

### Methods

```cpp
void setButtons(uint8_t buttonUp, uint8_t buttonDown)
```
Sets the pins for up and down buttons.

```cpp
void setState(unsigned int state)
```
Sets the current display state.

## Components

### TextView

Displays text on the screen.

#### Constructor

```cpp
TextView(const char* text)
```
Creates a new text view with the specified text.

#### Methods

```cpp
void setText(const char* text);
void setPosition(int x, int y);
void setStyle(TextViewStyle style);
void setFont(const uint8_t* font);
```

### Navigation

Creates a navigation menu.

#### Constructor

```cpp
Navigation()
```
Creates a new navigation component.

#### Methods

```cpp
void addItem(const char* text);
void removeItem(int index);
void selectNext();
void selectPrevious();
int getSelectedIndex();
void setSelectedItem(int index);
```

### LoadAnimation

Displays a loading animation.

#### Constructor

```cpp
LoadAnimation(LoaderType type)
```
Creates a new loading animation with the specified type.

#### Methods

```cpp
void start();
void stop();
bool isRunning();
void setType(LoaderType type);
void setPosition(int x, int y);
```

### Alert

Displays an alert message.

#### Constructor

```cpp
Alert(const char* message, AlertType type)
```
Creates a new alert with the specified message and type.

#### Methods

```cpp
void show();
void hide();
bool isVisible();
void setStyle(AlertStyle style);
void setIcon(const uint8_t* icon);
void setProgress(int progress);
void setMessage(const char* message);
void setType(AlertType type);
```

### ImageView

Displays an image.

#### Constructor

```cpp
ImageView(const uint8_t* bitmap, int width, int height)
```
Creates a new image view with the specified bitmap and dimensions.

#### Methods

```cpp
void setPosition(int x, int y);
void setScale(float scale);
void setAutoCenter(bool center);
void setStyle(ImageViewStyle style);
void setBitmap(const uint8_t* bitmap);
```

### Prompt

Creates a prompt for user input.

#### Constructor

```cpp
Prompt(const char* title, const char* initialValue)
```
Creates a new prompt with the specified title and initial value.

#### Methods

```cpp
void setMaxLength(int length);
void setKeyboardType(KeyboardType type);
void setPasswordMode(bool enabled);
void setValidator(std::function<bool(const char*)> validator);
void setOnComplete(std::function<void(const char*)> callback);
```

## Enums

### DisplayResolution

```cpp
enum DisplayResolution {
    RESOLUTION_128x64,
    RESOLUTION_128x32,
    RESOLUTION_96x16,
    RESOLUTION_64x48,
    RESOLUTION_64x32
};
```

### DisplayOrientation

```cpp
enum DisplayOrientation {
    ORIENTATION_NORMAL,
    ORIENTATION_RIGHT,
    ORIENTATION_INVERTED,
    ORIENTATION_LEFT
};
```

### DisplayColor

```cpp
enum DisplayColor {
    COLOR_WHITE,
    COLOR_INVERSE,
    COLOR_CUSTOM
};
```

### DisplayFont

```cpp
enum DisplayFont {
    FONT_5x7,
    FONT_8x8,
    FONT_8x16,
    FONT_12x16,
    FONT_16x16,
    FONT_16x24,
    FONT_24x32
};
```

### KeyboardType

```cpp
enum KeyboardType {
    KEYBOARD_ALPHA,    // Alphabetic keyboard (default)
    KEYBOARD_NUMERIC,  // Numeric keyboard
    KEYBOARD_SPECIAL   // Special characters keyboard
};
```

## Styles

### TextViewStyle

```cpp
TextViewStyle style;
style.fontSize = 2;
style.alignment = TEXT_ALIGN_CENTER;
style.color = COLOR_WHITE;
```

### NavigationStyle

```cpp
NavigationStyle style;
style.itemHeight = 16;
style.selectedColor = COLOR_WHITE;
style.unselectedColor = COLOR_GRAY;
```

### LoadAnimationStyle

```cpp
LoadAnimationStyle style;
style.size = 16;
style.color = COLOR_WHITE;
style.speed = 100;
```

### AlertStyle

```cpp
AlertStyle style;
style.duration = 2000;
style.color = COLOR_WHITE;
style.backgroundColor = COLOR_BLACK;
```

### ImageViewStyle

```cpp
ImageViewStyle style;
style.scale = 1;
style.alignment = IMAGE_ALIGN_CENTER;
```

## Constants

### Resolution Constants

```cpp
enum DisplayResolution {
  RESOLUTION_128x64,
  RESOLUTION_128x32,
  RESOLUTION_96x16,
  RESOLUTION_64x48,
  RESOLUTION_64x32
};
```

### Orientation Constants

```cpp
enum DisplayOrientation {
  ORIENTATION_NORMAL,
  ORIENTATION_RIGHT,
  ORIENTATION_INVERTED,
  ORIENTATION_LEFT
};
```

### Button Constants

```cpp
enum ButtonType {
  UP,
  DOWN,
  SELECT
};
```

### Color Constants

```cpp
#define COLOR_BLACK 0
#define COLOR_WHITE 1
#define COLOR_GRAY 2
```

### Alignment Constants

```cpp
#define TEXT_ALIGN_LEFT 0
#define TEXT_ALIGN_CENTER 1
#define TEXT_ALIGN_RIGHT 2

#define IMAGE_ALIGN_LEFT 0
#define IMAGE_ALIGN_CENTER 1
#define IMAGE_ALIGN_RIGHT 2
```

## Helper Functions

### Resolution Helpers

```cpp
uint8_t getResolutionWidth(DisplayResolution resolution);
uint8_t getResolutionHeight(DisplayResolution resolution);
```

### Orientation Helpers

```cpp
uint8_t getOrientationDegrees(DisplayOrientation orientation);
```

## Troubleshooting

1. Display not initializing
   - Check I2C connections
   - Verify I2C address
   - Check I2C pins

2. Components not displaying
   - Check component creation
   - Verify component addition
   - Check display update

3. Button issues
   - Check button connections
   - Verify button pins
   - Check button state

4. Memory issues
   - Reduce number of components
   - Use simpler styles
   - Check available memory 