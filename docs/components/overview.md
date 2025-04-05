# Components Overview

The EasySSD1306 library provides various components for creating rich user interfaces on OLED SSD1306 displays.

## DisplayManager

The main component that manages the display and its components.

### Initialization

```cpp
#include <EasySSD1306.h>

// Create a display manager instance with the desired resolution
DisplayManager display(RESOLUTION_128x64);

void setup() {
    // Configure button pins
    display.setButtons(2, 3);
    
    // Initialize the display
    display.begin();
}

void loop() {
    // Update the display in the main loop
    display.render();
}
```

### Available Resolutions

- `RESOLUTION_128x64`: 128x64 pixel display
- `RESOLUTION_128x32`: 128x32 pixel display

## Interface Components

### TextView

Displays static text on the display.

```cpp
// Create a text component
TextView text("Hello World!", 10, 10);

// Add to display
display.addComponent(&text);
```

### Navigation

Manages navigation between different screens.

```cpp
// Create a navigation menu
Navigation menu;

// Add items to the menu
menu.addItem("Item 1");
menu.addItem("Item 2");
menu.addItem("Item 3");

// Add to display
display.addComponent(&menu);
```

### Alert

Displays temporary alert messages.

```cpp
// Create an alert
Alert alert("Important message!", 2000); // 2000ms = 2 seconds

// Add to display
display.addComponent(&alert);
```

### ImageView

Displays images on the display.

```cpp
// Create an image component
ImageView image(myImage, 0, 0);

// Add to display
display.addComponent(&image);
```

### LoadAnimation

Displays loading animations.

```cpp
// Create a loading animation
LoadAnimation loading;

// Add to display
display.addComponent(&loading);
```

### Prompt

Requests user input.

```cpp
// Create a prompt
Prompt prompt("Enter your name:");

// Add to display
display.addComponent(&prompt);
```

## State Management

The DisplayManager maintains a state system for managing different screens:

```cpp
// Change to a new state
display.setState(1);

// Return to the previous state
display.setState(display.lastState);
```

## Button Handling

Buttons are automatically managed by the DisplayManager:

- Up Button: Navigate up in the current list
- Down Button: Navigate down in the current list
- Hold Up Button: Cancel the current operation
- Hold Down Button: Confirm the current selection

## The render() Method

The `render()` method is the core function of the DisplayManager that updates the display and manages the state of components. It should be called in the `loop()` function of your Arduino sketch.

### What render() Does

When you call `display.render()`, the following happens:

1. **Button State Update**: The method checks the current state of the buttons and updates internal variables.
2. **State Management**: If a button was pressed to cancel an operation, it returns to the previous state.
3. **Component Rendering**: It renders the component associated with the current state.
4. **State Transition**: If the component returns a new state, it updates the current state.

### Example Usage

```cpp
void loop() {
    display.render();  // Updates the display and current state
    delay(100);       // Small delay to prevent overwhelming the display
}
```

### Important Notes

- Always call `render()` in your `loop()` function to keep the display updated.
- The `render()` method handles both display updates and button state management.
- Components are rendered based on the current state of the DisplayManager.
- State transitions are managed automatically by the `render()` method.

## Display Configurations

### ScreenSaver
Configures display protection using animation or image components.

```cpp
// Using animation
LoadAnimation* screensaver = new LoadAnimation(1, LOAD_ANIM_CIRCLE_SWEEP);
displayManager.setScreenSaver(screensaver, 3); // 3 minutes timeout

// Using image
ImageView* screensaver = new ImageView();
screensaver->setImage(myImageData);
displayManager.setScreenSaver(screensaver, 3); // 3 minutes timeout
```

### Basic Setup

```cpp
#include <EasySSD1306.h>

DisplayManager display(RESOLUTION_128x64);

void setup() {
    display.begin();
    
    // Configure display settings
    display.setOrientation(ORIENTATION_NORMAL);
    display.setColor(COLOR_WHITE);
    display.setFont(FONT_5x7);
    display.setContrast(128);
    display.setAnimationSpeed(5);
    
    // Configure buttons
    display.setButtonPins(2, 3);
}

void loop() {
    display.render();  // Atualiza a tela e o estado atual
}
```

## UI Components

### DisplayManager
The main component that manages the display and other components.

```cpp
DisplayManager displayManager(128, 64);
displayManager.begin();
```

### TextView
Displays text with various styles and effects.

```cpp
TextView* text = new TextView("Hello World");
text->setPosition(10, 10);
displayManager.addComponent(text);
```

### Navigation
Creates interactive menus.

```cpp
Navigation* menu = new Navigation();
menu->addItem("Item 1");
menu->addItem("Item 2");
displayManager.addComponent(menu);
```

### Alert
Shows alert messages.

```cpp
Alert* alert = new Alert("Warning!");
displayManager.addComponent(alert);
```

### ImageView
Displays images.

```cpp
ImageView* image = new ImageView();
image->setImage(myImageData);
displayManager.addComponent(image);
```

### LoadAnimation
Shows loading animations.

```cpp
LoadAnimation* loading = new LoadAnimation();
displayManager.addComponent(loading);
```

### Prompt
Shows input prompts.

```cpp
Prompt* prompt = new Prompt("Enter value:");
displayManager.addComponent(prompt);
```

### CustomComponent
Create your own custom components by inheriting from the IDisplayComponent interface.

```cpp
class MyCustomComponent : public IDisplayComponent {
public:
    MyCustomComponent() {}
    
    void render(Adafruit_SSD1306* display) override {
        // Your rendering code here
    }
    
    int id = 0;  // Component ID
};
```

## Component Lifecycle

1. **Creation**
   ```cpp
   Component* component = new MyComponent();
   ```

2. **Configuration**
   ```cpp
   component->setPosition(10, 10);
   component->setVisible(true);
   ```

3. **Registration**
   ```cpp
   displayManager.addComponent(component);
   ```

4. **Updating**
   ```cpp
   displayManager.update();
   ```

5. **Removal**
   ```cpp
   displayManager.removeComponent(component);
   delete component;
   ```

## Best Practices

1. **Component Selection**
   - Choose appropriate components for your needs
   - Consider memory constraints
   - Test component combinations

2. **Configuration**
   - Set proper positions and sizes
   - Configure styles and effects
   - Consider display limitations

3. **Memory Management**
   - Properly allocate and deallocate memory
   - Remove unused components
   - Monitor memory usage

4. **Performance**
   - Minimize updates
   - Use appropriate intervals
   - Consider display refresh rate

5. **Layout Planning**
   - Plan component positions
   - Consider different orientations
   - Test in various conditions

6. **Error Handling**
   - Check for null pointers
   - Handle allocation failures
   - Implement proper cleanup

## Complete Example

```cpp
#include <EasySSD1306.h>

DisplayManager displayManager(128, 64);
TextView* text;
Navigation* menu;
LoadAnimation* screensaver;

void setup() {
    displayManager.begin();
    
    // Create text
    text = new TextView("Hello World");
    text->setPosition(10, 10);
    displayManager.addComponent(text);
    
    // Create menu
    menu = new Navigation();
    menu->addItem("Item 1");
    menu->addItem("Item 2");
    displayManager.addComponent(menu);
    
    // Configure screensaver
    screensaver = new LoadAnimation(1, LOAD_ANIM_CIRCLE_SWEEP);
    displayManager.setScreenSaver(screensaver, 3); // 3 minutes timeout
}

void loop() {
    displayManager.update();
    
    if (digitalRead(BUTTON_PIN) == LOW) {
        displayManager.resetScreenSaver();
    }
    
    delay(100);
}

## Prompt Component

The Prompt component creates interactive prompts with a built-in virtual keyboard for text input. This component allows users to enter text using on-screen navigation, making it perfect for settings, configuration, or any scenario requiring user text input.

```cpp
// Create a prompt with a title and initial value
Prompt* prompt = new Prompt("Enter Name:", "User");
prompt->setMaxLength(20);  // Limit input length
prompt->setKeyboardType(KEYBOARD_ALPHA);  // Use alphabetic keyboard

// Add callback for when input is complete
prompt->setOnComplete([](const char* value) {
    Serial.print("User entered: ");
    Serial.println(value);
});

display.addComponent(prompt);
```

The Prompt component features:
- Virtual keyboard with different layouts (alphabetic, numeric, special characters)
- Customizable input validation
- Maximum length restrictions
- Callback functions for input completion
- Visual feedback during typing
- Support for different input modes (text, numbers, passwords)

This makes it ideal for creating interactive forms, settings menus, or any interface requiring text input from the user. 