# Alert Component

The Alert component displays notifications and messages on the OLED display with various visual styles.

## Features

- Multiple alert styles
- Custom icons support
- Progress bar options
- Blinking effects
- Automatic centering
- Border styles
- Automatic adaptation to display size and orientation

## Styles

| Style | Description |
|-------|-------------|
| ALERT_STYLE_SIMPLE | Simple text alert |
| ALERT_STYLE_BOXED | Alert with box border |
| ALERT_STYLE_ROUNDED | Alert with rounded border |
| ALERT_STYLE_ICON | Alert with icon |
| ALERT_STYLE_BLINK | Blinking alert |
| ALERT_STYLE_PROGRESS | Alert with progress bar |

## Usage

### Basic Usage
```cpp
Alert* alert = new Alert("Warning!");
manager.addComponent(alert);
```

### Usage with Style
```cpp
Alert* alert = new Alert("Warning!", ALERT_STYLE_BOXED);
alert->setIcon(warningIcon);
alert->setBlinkInterval(500);
manager.addComponent(alert);
```

### Progress Alert
```cpp
Alert* alert = new Alert("Loading...", ALERT_STYLE_PROGRESS);
alert->setProgress(0);
manager.addComponent(alert);

void loop() {
  static int progress = 0;
  alert->setProgress(progress);
  progress = (progress + 1) % 100;
  manager.update();
  delay(50);
}
```

## Methods

### Constructor
```cpp
Alert(const char* message, AlertStyle style = ALERT_STYLE_SIMPLE)
```
Creates a new alert with the specified message and style.

### setMessage
```cpp
void setMessage(const char* message)
```
Sets the alert message.

### setStyle
```cpp
void setStyle(AlertStyle style)
```
Sets the alert style.

### setIcon
```cpp
void setIcon(const uint8_t* icon)
```
Sets the alert icon.

### setProgress
```cpp
void setProgress(int progress)
```
Sets the progress value (0-100).

### setBlinkInterval
```cpp
void setBlinkInterval(int interval)
```
Sets the blink interval in milliseconds.

### setPosition
```cpp
void setPosition(int x, int y)
```
Sets the alert position.

### setAutoAdapt
```cpp
void setAutoAdapt(bool autoAdapt)
```
Enables or disables automatic adaptation to display changes.

## Examples

### Multiple Styles
```cpp
void setup() {
  Alert* simpleAlert = new Alert("Simple", ALERT_STYLE_SIMPLE);
  Alert* boxedAlert = new Alert("Boxed", ALERT_STYLE_BOXED);
  Alert* roundedAlert = new Alert("Rounded", ALERT_STYLE_ROUNDED);
  
  simpleAlert->setPosition(0, 0);
  boxedAlert->setPosition(0, 20);
  roundedAlert->setPosition(0, 40);
  
  manager.addComponent(simpleAlert);
  manager.addComponent(boxedAlert);
  manager.addComponent(roundedAlert);
}
```

### Dynamic Alerts
```cpp
void loop() {
  static int counter = 0;
  
  switch(counter % 6) {
    case 0:
      alert->setStyle(ALERT_STYLE_SIMPLE);
      break;
    case 1:
      alert->setStyle(ALERT_STYLE_BOXED);
      break;
    case 2:
      alert->setStyle(ALERT_STYLE_ROUNDED);
      break;
    case 3:
      alert->setStyle(ALERT_STYLE_ICON);
      break;
    case 4:
      alert->setStyle(ALERT_STYLE_BLINK);
      break;
    case 5:
      alert->setStyle(ALERT_STYLE_PROGRESS);
      break;
  }
  
  counter++;
  manager.update();
  delay(3000);
}
```

## Best Practices

1. Use appropriate styles for different alert types
2. Consider alert duration and visibility
3. Use icons for better visual feedback
4. Position alerts carefully
5. Consider automatic adaptation
6. Test alerts in different orientations
7. Use appropriate update intervals for animations 