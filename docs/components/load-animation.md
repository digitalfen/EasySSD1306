# LoadAnimation Component

The LoadAnimation component shows loading states and progress indicators.

## Usage

```cpp
#include <EasySSD1306.h>

void setup() {
    DisplayManager display(128, 64);
    LoadAnimation* loading = new LoadAnimation("Loading...");
    loading->setPosition(0, 0);
    display.addComponent(loading);
    display.begin();
}
```

## Methods

### Constructor
```cpp
LoadAnimation(const char* text)
```

### Animation Control
```cpp
void start()
void stop()
bool isRunning()
```

### Text
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

## Examples

### Loading with Status
```cpp
void setup() {
    DisplayManager display(128, 64);
    
    LoadAnimation* loading = new LoadAnimation("Connecting");
    loading->setPosition(0, 0);
    
    TextView* status = new TextView("Please wait...");
    status->setPosition(0, 32);
    
    display.addComponent(loading);
    display.addComponent(status);
    display.begin();
    
    loading->start();
}
```

### Dynamic Loading Text
```cpp
LoadAnimation* loading;
char buffer[32];

void setup() {
    DisplayManager display(128, 64);
    loading = new LoadAnimation("");
    loading->setPosition(0, 0);
    display.addComponent(loading);
    display.begin();
}

void loop() {
    sprintf(buffer, "Loading data %d%%", getProgress());
    loading->setText(buffer);
    display.update();
}
```

## Available Styles

### Spinner
```cpp
LoadAnimation* loading = new LoadAnimation("Loading");
loading->setStyle(LOAD_SPINNER);
```

### Progress Bar
```cpp
LoadAnimation* loading = new LoadAnimation("Progress");
loading->setStyle(LOAD_PROGRESS);
loading->setProgress(50);  // 50%
```

### Dots
```cpp
LoadAnimation* loading = new LoadAnimation("Please wait");
loading->setStyle(LOAD_DOTS);
```

## Configuration

### Duration
```cpp
LoadAnimation* loading = new LoadAnimation("Loading");
loading->setDuration(3000);  // 3 seconds
```

### Speed
```cpp
LoadAnimation* loading = new LoadAnimation("Loading");
loading->setSpeed(100);  // 100ms per frame
```

### Callback
```cpp
void onComplete() {
    // Called when animation ends
    Serial.println("Loading complete!");
}

void setup() {
    DisplayManager display(128, 64);
    LoadAnimation* loading = new LoadAnimation("Loading");
    loading->setOnComplete(onComplete);
    display.addComponent(loading);
    display.begin();
}
```

## Complete Example

```cpp
void onComplete() {
    // Update status after loading
    TextView* status = new TextView("Ready!");
    display.addComponent(status);
}

void setup() {
    DisplayManager display(128, 64);
    
    LoadAnimation* loading = new LoadAnimation("Initializing");
    loading->setStyle(LOAD_SPINNER);
    loading->setDuration(2000);
    loading->setSpeed(50);
    loading->setOnComplete(onComplete);
    
    display.addComponent(loading);
    display.begin();
}
```

## Reference API

### Constructors
- `LoadAnimation(unsigned int id, const char *message)`

### Public Methods
- `unsigned int render(Adafruit_SSD1306 *disp)`
- `void setMessage(const char *message)`
- `void setDuration(unsigned long duration)`
- `void setShowProgress(bool show)`
- `void setProgress(int progress)`
- `void setOnComplete(std::function<void()> callback)`
- `void reset()`

## Usage Tips

1. **Messages**
   - Use clear and informative messages
   - Keep texts short
   - Indicate the operation in progress

2. **Duration**
   - Configure appropriate time
   - Consider the actual operation
   - Avoid too long times

3. **Progress**
   - Use for long operations
   - Update regularly
   - Provide visual feedback

4. **Performance**
   - Avoid too frequent updates
   - Use appropriate delays
   - Consider memory usage

## Practical Examples

### Simple Loading

```cpp
LoadAnimation loading(1, "Initializing...");
loading.setDuration(2000);  // 2 seconds
```

### Loading with Progress

```cpp
LoadAnimation loading(1, "Downloading...");
loading.setShowProgress(true);
loading.setProgress(50);  // 50%
```

### Loading with Callback

```cpp
LoadAnimation loading(1, "Connecting...");
loading.setDuration(3000);
loading.setOnComplete([]() {
    display.setState(2);
});
```

## Usage Patterns

### System Initialization

```cpp
void showInitialization() {
    LoadAnimation init(1, "Starting...");
    init.setDuration(2000);
    init.setOnComplete([]() {
        display.setState(1);
    });
}
```

### Firmware Update

```cpp
void showFirmwareUpdate() {
    LoadAnimation update(1, "Updating...");
    update.setShowProgress(true);
    
    // Simulate progress
    for (int i = 0; i <= 100; i += 10) {
        update.setProgress(i);
        delay(500);
    }
}
```

### Network Connection

```cpp
void showNetworkConnection() {
    LoadAnimation conn(1, "Connecting...");
    conn.setDuration(5000);  // 5 seconds
    conn.setOnComplete([]() {
        display.setState(3);
    });
}
``` 