# Navigation Component

The Navigation component provides a menu system for OLED displays.

## Features

- Multiple menu styles
- Custom menu items
- Automatic centering
- Border styles
- Inverted text option
- Automatic adaptation to display size and orientation

## Styles

| Style | Description |
|-------|-------------|
| NAV_STYLE_BORDERLESS | Menu without border |
| NAV_STYLE_SOLID_BORDER | Menu with solid border |
| NAV_STYLE_ROUNDED_BORDER | Menu with rounded border |
| NAV_STYLE_INVERTED | Inverted menu |

## Usage

### Basic Usage

```cpp
#include <EasySSD1306.h>

DisplayManager displayManager(128, 64);

void setup() {
    displayManager.begin();
    
    Navigation* menu = new Navigation();
    menu->addItem("Item 1");
    menu->addItem("Item 2");
    menu->addItem("Item 3");
    menu->setPosition(10, 10);
    displayManager.addComponent(menu);
}

void loop() {
    displayManager.update();
    delay(100);
}
```

### With Style

```cpp
Navigation* menu = new Navigation();
menu->setStyle(NavigationStyle::SOLID_BORDER);
menu->addItem("Item 1");
menu->setPosition(10, 10);
displayManager.addComponent(menu);
```

### With Custom Items

```cpp
Navigation* menu = new Navigation();
menu->addItem("Item 1");
menu->addItem("Item 2");
menu->addItem("Item 3");
menu->setPosition(10, 10);
displayManager.addComponent(menu);
```

### With Inverted Style

```cpp
Navigation* menu = new Navigation();
menu->setInverted(true);
menu->addItem("Item 1");
menu->setPosition(10, 10);
displayManager.addComponent(menu);
```

## Methods

### Constructor
```cpp
Navigation()
```
Creates a new Navigation menu.

### addItem
```cpp
void addItem(const char* text)
```
Adds a new item to the menu.

### removeItem
```cpp
void removeItem(uint8_t index)
```
Removes an item from the menu.

### getItemCount
```cpp
uint8_t getItemCount()
```
Returns the number of items in the menu.

### getItem
```cpp
const char* getItem(uint8_t index)
```
Returns the text of the specified item.

### setStyle
```cpp
void setStyle(NavigationStyle style)
```
Sets the menu style.

### getStyle
```cpp
NavigationStyle getStyle()
```
Returns the current menu style.

### setInverted
```cpp
void setInverted(bool inverted)
```
Sets whether the menu is inverted.

### isInverted
```cpp
bool isInverted()
```
Returns whether the menu is inverted.

## Example with Multiple Styles

Here's a complete example showing different menu styles:

```cpp
#include <EasySSD1306.h>

DisplayManager displayManager(128, 64);
Navigation* menus[4];

void setup() {
    displayManager.begin();
    
    // Create different menu styles
    menus[0] = new Navigation();
    menus[0]->setPosition(10, 10);
    menus[0]->setStyle(NavigationStyle::BORDERLESS);
    menus[0]->addItem("Borderless Menu");
    
    menus[1] = new Navigation();
    menus[1]->setPosition(10, 30);
    menus[1]->setStyle(NavigationStyle::SOLID_BORDER);
    menus[1]->addItem("Solid Border Menu");
    
    menus[2] = new Navigation();
    menus[2]->setPosition(10, 50);
    menus[2]->setStyle(NavigationStyle::ROUNDED_BORDER);
    menus[2]->addItem("Rounded Border Menu");
    
    // Add all menus to display
    for (int i = 0; i < 3; i++) {
        displayManager.addComponent(menus[i]);
    }
}

void loop() {
    displayManager.update();
    delay(100);
}
```

## Best Practices

1. **Menu Size**
   - Choose appropriate menu size for readability
   - Consider display resolution
   - Test different sizes

2. **Style Selection**
   - Use styles that match your application
   - Consider contrast and visibility
   - Test in different lighting conditions

3. **Positioning**
   - Use relative positioning when possible
   - Consider menu length
   - Test in different orientations

4. **Memory Usage**
   - Minimize menu items
   - Use static items when possible
   - Consider memory constraints

5. **Performance**
   - Update menu only when needed
   - Use appropriate update intervals
   - Consider display refresh rate 