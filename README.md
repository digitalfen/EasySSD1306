# EasySSD1306

[![PlatformIO](https://img.shields.io/badge/platform-PlatformIO-blue.svg)](https://platformio.org/)
[![Arduino Library](https://img.shields.io/badge/Arduino%20Library-EasySSD1306-blue.svg)](https://www.ardu-badge.com/EasySSD1306)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE)
[![Documentation](https://img.shields.io/badge/docs-GitHub%20Pages-blue.svg)](https://digitalfen.github.io/EasySSD1306)
[![Discord](https://img.shields.io/badge/discord-Join%20us-7289DA.svg)](https://discord.gg/your-server)

An easy-to-use library for creating rich graphical interfaces on SSD1306 OLED displays with ESP32 and ESP8266.

## Quick Start

### Installation

#### Arduino IDE
1. Open Arduino IDE
2. Go to Tools > Manage Libraries
3. Search for "EasySSD1306"
4. Click Install

#### PlatformIO
Add to your `platformio.ini`:
```ini
lib_deps =
    digitalfen/EasySSD1306
```

### Basic Example

```cpp
#include <EasySSD1306.h>

void setup() {
    DisplayManager display;
    display.setI2CPins(21, 22);  // SDA, SCL for ESP32
    
    TextView* text = new TextView("Hello!");
    display.addComponent(text);
    display.begin();
}

void loop() {
    display.update();
}
```

## Documentation

- [Full Documentation](https://digitalfen.github.io/EasySSD1306)
- [Examples](https://digitalfen.github.io/EasySSD1306/examples/)
- [API Reference](https://digitalfen.github.io/EasySSD1306/api-reference/)

## Supported Platforms

- ESP32
- ESP8266
- Arduino UNO

## Button Configuration

The library supports two buttons for navigation and interaction. Each platform has default button pins:

### Default Button Pins

- **ESP32**
  - Button 1: GPIO4
  - Button 2: GPIO5

- **ESP8266**
  - Button 1: D3 (GPIO0)
  - Button 2: D4 (GPIO2)

- **Arduino UNO**
  - Button 1: Pin 2 (INT0)
  - Button 2: Pin 3 (INT1)

### Customizing Button Pins

```cpp
DisplayManager display;
display.setButtonPins(6, 7);  // Set custom pins for Button 1 and Button 2
```

## Display Resolutions

The library supports multiple SSD1306 display resolutions:

- 128x64 pixels (default)
- 128x32 pixels
- 96x64 pixels

To change resolution, modify `src/EasySSD1306.h`:
```cpp
#define SSD1306_128_64  // Default resolution
//#define SSD1306_128_32  // Uncomment for 128x32
//#define SSD1306_96_64   // Uncomment for 96x64
```

## Examples

### Menu Navigation
```cpp
#include <EasySSD1306.h>

void setup() {
    DisplayManager display;
    
    Navigation* menu = new Navigation("Settings");
    menu->addItem("Temperature", "25°C");
    menu->addItem("Humidity", "60%");
    menu->addItem("Pressure", "1013hPa");
    
    display.addComponent(menu);
    display.begin();
}
```

### System Monitor
```cpp
#include <EasySSD1306.h>

void setup() {
    DisplayManager display;
    
    TextView* temp = new TextView("Temp: 25°C");
    TextView* hum = new TextView("Humidity: 60%");
    TextView* press = new TextView("Pressure: 1013hPa");
    
    display.addComponent(temp);
    display.addComponent(hum);
    display.addComponent(press);
    display.begin();
}
```

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Support

- [GitHub Issues](https://github.com/digitalfen/EasySSD1306/issues)
- [Documentation](https://digitalfen.github.io/EasySSD1306)

## Authors

- Vinícius Maffioli - [@linkedin](https://www.linkedin.com/in/vinicius-maffioli/)

## Acknowledgments

- [Adafruit](https://www.adafruit.com/) for the SSD1306 library
- [PlatformIO](https://platformio.org/) for the development environment
- [MkDocs](https://www.mkdocs.org/) for the documentation
