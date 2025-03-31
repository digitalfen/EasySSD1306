# TextView Component

The TextView component displays static text on the OLED display.

## Usage

```cpp
#include <EasySSD1306.h>

void setup() {
    DisplayManager display(128, 64);
    TextView* text = new TextView("Hello World!");
    text->setPosition(0, 0);
    text->setStyle(TextStyle::NORMAL);
    display.addComponent(text);
    display.begin();
}
```

## Available Styles

- `NORMAL`: Standard text style
- `BOLD`: Bold text style
- `ITALIC`: Italic text style
- `UNDERLINE`: Underlined text style

## Methods

### Constructor
```cpp
TextView(const char* text)
```

### Text Manipulation
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

### Style
```cpp
void setStyle(TextStyle style)
TextStyle getStyle()
```

### Visibility
```cpp
void setVisible(bool visible)
bool isVisible()
```

## Examples

### Multiple Text Views
```cpp
void setup() {
    DisplayManager display(128, 64);
    
    TextView* title = new TextView("System Status");
    title->setPosition(0, 0);
    title->setStyle(TextStyle::BOLD);
    
    TextView* status = new TextView("Running");
    status->setPosition(0, 16);
    status->setStyle(TextStyle::NORMAL);
    
    display.addComponent(title);
    display.addComponent(status);
    display.begin();
}
```

### Dynamic Text Update
```cpp
TextView* status;
char buffer[32];

void setup() {
    DisplayManager display(128, 64);
    status = new TextView("");
    status->setPosition(0, 0);
    display.addComponent(status);
    display.begin();
}

void loop() {
    sprintf(buffer, "Temperature: %d°C", getTemperature());
    status->setText(buffer);
    display.update();
}
``` 