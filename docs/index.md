# EasySSD1306

A library for creating graphical interfaces on SSD1306 OLED displays with ESP32 and ESP8266.

## Features

- Pre-built components
- Text and image support
- Menu navigation
- Loading animations
- Alert system

## Supported Platforms

- ESP32
- ESP8266
- Arduino (in development)

## Installation

### PlatformIO

Add to your `platformio.ini`:

```ini
lib_deps =
    digitalfen/EasySSD1306
```

### Arduino IDE

1. Download the ZIP file
2. Go to Sketch > Include Library > Add .ZIP Library
3. Select the downloaded ZIP file

## Quick Start

```cpp
#include <EasySSD1306.h>

void setup() {
    DisplayManager display(128, 64);
    TextView* text = new TextView("Hello!");
    display.addComponent(text);
    display.begin();
}

void loop() {
    display.update();
}
```

## Documentation

- [Quick Start Guide](quickstart.md)
- [API Reference](api-reference.md)
- [Examples](examples.md)
- [Components Overview](components/overview.md)

## Contributing

Contributions are welcome! See the [contributing guide](contributing.md).

## License

MIT License - see [LICENSE file](../LICENSE) for details.

## Support

- Open an issue on GitHub
- Check the documentation
- Review the examples
