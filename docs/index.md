# EasySSD1306

A lightweight library that simplifies SSD1306 OLED display implementation through pre-built components and custom development tools. Designed to be used as a complete solution or as a reference for display management implementations.

## Features

- Pre-built UI components for common display needs
- Component-based architecture with state management
- Component base class for drawing custom components
- Hardware abstraction for SSD1306 displays via I2C
- Dual-button navigation system with state tracking
- Screen saver with configurable timeout and animations
- Resolution support: 128x64, 128x32, 96x16, 64x48, 64x32
- Orientation control: 0°, 90°, 180°, 270°
- Configurable contrast, color inversion, and animation speed
- Extensible component system for custom UI elements

## Button Navigation

The library uses a simple two-button navigation system:

- **Button 1**: 
  - Press: Navigate within the current view (menu items, text pages, etc.)
  - Hold: Go back to the previous state or cancel

- **Button 2**: 
  - Press: Navigate within the current view (menu items, text pages, etc.)
  - Hold: Advance to the next state or confirm

This pattern works consistently across all components, making it intuitive for users to navigate through menus, scroll text, select options, and confirm actions.

## Basic Usage

1. Initialize the display and display manager (see [Display Manager](display_manager/displaymanager.md))
2. Configure button pins and other settings (see [Display Configuration](display_manager/configuration.md))
3. Build components and add them to the DisplayManager (see [Components](components/component.md))
4. Call display.render() in the loop (see [The render() Method](components/overview.md#the-render-method))

See [Getting Started](getting_started.md) for detailed instructions.

## Documentation

- [Getting Started](getting_started.md)
- [Display Manager](display_manager/configuration.md)
- [Components](components/overview.md)
- [API Reference](api-reference.md)
- [Examples](examples.md)

## Available Resolutions

- `RESOLUTION_128x64`: 128x64 pixels
- `RESOLUTION_128x32`: 128x32 pixels

## Available Orientations

- `ORIENTATION_NORMAL`: 0 degrees
- `ORIENTATION_RIGHT`: 90 degrees clockwise
- `ORIENTATION_INVERTED`: 180 degrees
- `ORIENTATION_LEFT`: 270 degrees clockwise

## Components

- `TextView`: Display text with various styles
- `ImageView`: Display images
- `Alert`: Display alert messages
- `Prompt`: Create interactive prompts
- `LoadAnimation`: Show loading animations
- `TextAnimation`: Animate text with various effects
- `ImageAnimation`: Animate images with various effects
- `Navigation`: Create navigation menus

## Examples

- [Basic Example](examples/basic.md)
- [Resolution Example](examples/resolution.md)
- [Orientation Example](examples/orientation.md)
- [Navigation Example](examples/navigation.md)
- [LoadAnimation Example](examples/load_animation.md)
- [Alert Example](examples/alert.md)

## Troubleshooting

1. Display not initializing
   - Check I2C connections
   - Verify I2C address
   - Check I2C pins

2. Components not displaying
   - Check component creation
   - Verify component addition
   - Check display render

3. Button issues
   - Check button connections
   - Verify button pins
   - Check button state

4. Memory issues
   - Reduce number of components
   - Use simpler styles
   - Check available memory

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
