# TextView Component

The TextView component displays text with various styles and effects.

## Features

- Multiple text styles
- Custom text size
- Automatic centering
- Border styles
- Inverted text option
- Automatic adaptation to display size and orientation

## Styles

| Style | Description |
|-------|-------------|
| TXT_VIEW_BORDERLESS_LEFT | Left-aligned text without border |
| TXT_VIEW_BORDERLESS_CENTER | Centered text without border |
| TXT_VIEW_BORDERLESS_RIGHT | Right-aligned text without border |
| TXT_VIEW_SOLID_BORDER_LEFT | Left-aligned text with solid border |
| TXT_VIEW_SOLID_BORDER_CENTER | Centered text with solid border |
| TXT_VIEW_SOLID_BORDER_RIGHT | Right-aligned text with solid border |
| TXT_VIEW_ROUNDED_BORDER_LEFT | Left-aligned text with rounded border |
| TXT_VIEW_ROUNDED_BORDER_CENTER | Centered text with rounded border |
| TXT_VIEW_ROUNDED_BORDER_RIGHT | Right-aligned text with rounded border |
| TXT_VIEW_INVERTED_LEFT | Left-aligned inverted text |
| TXT_VIEW_INVERTED_CENTER | Centered inverted text |
| TXT_VIEW_INVERTED_RIGHT | Right-aligned inverted text |

## Usage

### Basic Usage

```cpp
#include <EasySSD1306.h>

DisplayManager display(RESOLUTION_128x64);

void setup() {
    display.begin();
    
    TextView* text = new TextView("Hello World");
    text->setPosition(10, 10);
    display.addComponent(text);
}

void loop() {
    display.update();
    delay(100);
}
```

### With Style

```cpp
TextView* text = new TextView("Styled Text");
text->setStyle(TextViewStyle::BOLD);
text->setPosition(10, 10);
display.addComponent(text);
```

### With Custom Size

```cpp
TextView* text = new TextView("Large Text");
text->setTextSize(2);
text->setPosition(10, 10);
display.addComponent(text);
```

### With Inverted Text

```cpp
TextView* text = new TextView("Inverted Text");
text->setInverted(true);
text->setPosition(10, 10);
display.addComponent(text);
```

## Methods

### Constructor
```cpp
TextView(const char* text)
```
Creates a new TextView with the specified text.

### setText
```cpp
void setText(const char* text)
```
Sets the text to display.

### getText
```cpp
const char* getText()
```
Returns the current text.

### setStyle
```cpp
void setStyle(TextViewStyle style)
```
Sets the text style.

### getStyle
```cpp
TextViewStyle getStyle()
```
Returns the current text style.

### setTextSize
```cpp
void setTextSize(uint8_t size)
```
Sets the text size.

### getTextSize
```cpp
uint8_t getTextSize()
```
Returns the current text size.

### setInverted
```cpp
void setInverted(bool inverted)
```
Sets whether the text is inverted.

### isInverted
```cpp
bool isInverted()
```
Returns whether the text is inverted.

## Example with Multiple Styles

Here's a complete example showing different text styles:

```cpp
#include <EasySSD1306.h>

DisplayManager display(RESOLUTION_128x64);
TextView* texts[4];

void setup() {
    display.begin();
    
    // Create different text styles
    texts[0] = new TextView("Normal Text");
    texts[0]->setPosition(10, 10);
    texts[0]->setStyle(TextViewStyle::NORMAL);
    
    texts[1] = new TextView("Bold Text");
    texts[1]->setPosition(10, 30);
    texts[1]->setStyle(TextViewStyle::BOLD);
    
    texts[2] = new TextView("Inverted Text");
    texts[2]->setPosition(10, 50);
    texts[2]->setInverted(true);
    
    // Add all texts to display
    for (int i = 0; i < 4; i++) {
        display.addComponent(texts[i]);
    }
}

void loop() {
    display.update();
    delay(100);
}
```

## Best Practices

1. **Text Size**
   - Choose appropriate text size for readability
   - Consider display resolution
   - Test different sizes

2. **Style Selection**
   - Use styles that match your application
   - Consider contrast and visibility
   - Test in different lighting conditions

3. **Positioning**
   - Use relative positioning when possible
   - Consider text length
   - Test in different orientations

4. **Memory Usage**
   - Minimize text length
   - Use static text when possible
   - Consider memory constraints

5. **Performance**
   - Update text only when needed
   - Use appropriate update intervals
   - Consider display refresh rate 