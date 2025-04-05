# Display Configuration

The Display Manager provides various configuration options to customize the display behavior.

## Basic Configuration

```cpp
// Create display manager with resolution
DisplayManager display(RESOLUTION_128x64);

// Configure display settings
display.setOrientation(ORIENTATION_NORMAL);
display.setColor(COLOR_WHITE);
display.setFont(FONT_5x7);
display.setContrast(128);
display.setAnimationSpeed(5);
```

## Component Management

```cpp
// Add components
TextView* text = new TextView("Hello World");
text->setPosition(10, 10);
display.addComponent(text);

// Remove components
display.removeComponent(text);

// Clear all components
display.clearComponents();
```

## Display Updates

```cpp
// Atualiza a tela e o estado atual
display.render();

// Limpa a tela
display.clear();
display.clearDisplay();
```

## Button Configuration

```cpp
// Configure button pins
display.setButtonPins(2, 3);

// Check button states
if (display.isButton1Pressed()) {
    // Botão 1 pressionado - retorna à tela anterior
}

if (display.isButton2Pressed()) {
    // Botão 2 pressionado - avança para próxima tela
}

if (display.wasButton1Pressed()) {
    // Botão 1 foi pressionado e solto - cancela operação atual
}

if (display.wasButton2Pressed()) {
    // Botão 2 foi pressionado e solto - confirma operação atual
}
```

## Complete Example

```cpp
#include <EasySSD1306.h>

DisplayManager display(RESOLUTION_128x64);

void setup() {
    // Initialize display
    display.begin();
    
    // Configure display settings
    display.setOrientation(ORIENTATION_NORMAL);
    display.setColor(COLOR_WHITE);
    display.setFont(FONT_5x7);
    display.setContrast(128);
    display.setAnimationSpeed(5);
    
    // Configure buttons
    display.setButtonPins(2, 3);
    
    // Add components
    TextView* text = new TextView("Hello World");
    text->setPosition(10, 10);
    display.addComponent(text);
    
    Navigation* menu = new Navigation();
    menu->addItem("Item 1");
    menu->addItem("Item 2");
    display.addComponent(menu);
}

void loop() {
    // Atualiza a tela e o estado atual
    display.render();
    delay(100);
}
``` 