# Prompt Component

The Prompt component handles user text input.

## Usage

```cpp
#include <EasySSD1306.h>

void setup() {
    DisplayManager display(128, 64);
    Prompt* prompt = new Prompt("Enter value:", "");
    prompt->setMaxLength(10);
    display.addComponent(prompt);
    display.begin();
}
```

## Methods

### Constructor
```cpp
Prompt(const char* label, const char* initialValue)
```

### Input Control
```cpp
void start()
void stop()
void clear()
bool isActive()
```

### Content
```cpp
void setLabel(const char* label)
void setValue(const char* value)
const char* getLabel()
const char* getValue()
```

### Input Settings
```cpp
void setMaxLength(int length)
int getMaxLength()
void setInputType(InputType type)
InputType getInputType()
```

## Examples

### Text Input
```cpp
void setup() {
    DisplayManager display(128, 64);
    
    Prompt* prompt = new Prompt("Enter name:", "");
    prompt->setMaxLength(20);
    prompt->setInputType(InputType::TEXT);
    
    display.addComponent(prompt);
    display.begin();
    
    prompt->start();
}
```

### Numeric Input
```cpp
void setup() {
    DisplayManager display(128, 64);
    
    Prompt* prompt = new Prompt("Enter number:", "");
    prompt->setMaxLength(5);
    prompt->setInputType(InputType::NUMBER);
    
    display.addComponent(prompt);
    display.begin();
    
    prompt->start();
}
``` 