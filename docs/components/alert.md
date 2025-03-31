# Alert Component

The Alert component displays notifications and alerts.

## Usage

```cpp
#include <EasySSD1306.h>

void setup() {
    DisplayManager display(128, 64);
    Alert* alert = new Alert("Warning", "System error detected");
    alert->setDuration(3000);  // Show for 3 seconds
    display.addComponent(alert);
    display.begin();
}
```

## Methods

### Constructor
```cpp
Alert(const char* title, const char* message)
```

### Alert Control
```cpp
void show()
void hide()
void dismiss()
bool isVisible()
```

### Content
```cpp
void setTitle(const char* title)
void setMessage(const char* message)
const char* getTitle()
const char* getMessage()
```

### Duration
```cpp
void setDuration(unsigned long duration)
unsigned long getDuration()
```

## Examples

### Simple Alert
```cpp
void setup() {
    DisplayManager display(128, 64);
    
    Alert* alert = new Alert("Success", "Operation completed");
    alert->setDuration(2000);
    
    display.addComponent(alert);
    display.begin();
    
    alert->show();
}
```

### Multiple Alerts
```cpp
void setup() {
    DisplayManager display(128, 64);
    
    Alert* error = new Alert("Error", "Connection failed");
    Alert* warning = new Alert("Warning", "Low battery");
    
    display.addComponent(error);
    display.addComponent(warning);
    display.begin();
    
    error->show();
    delay(3000);
    warning->show();
}
``` 