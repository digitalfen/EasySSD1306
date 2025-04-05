# EasySSD1306

A lightweight library that simplifies SSD1306 OLED display implementation through pre-built components and custom development tools. Designed to be used as a complete solution or as a reference for display management implementations.

Key aspects:
- Ready-to-use components (TextView, ImageView, LoadAnimation)
- Framework for custom component development
- Navigation through two buttons:
  - Button 1: Press returns to previous screen, hold cancels current operation
  - Button 2: Press advances to next screen, hold confirms current operation
- Multiple display resolutions support
- Component-based architecture

# Display Manager

The Display Manager is the core class that handles display operations, component rendering, and user input processing.

## Features

- Pre-built components for common display tasks
- Framework for creating custom components
- Support for multiple display resolutions
- Display orientation control
- Font and contrast settings

## Configuration Options

The Display Manager provides several configuration options:

- **Resolution**: Set the display resolution (e.g., 128x64, 128x32)
- **Orientation**: Change the display orientation (normal, right, inverted, left)
- **Color**: Set the display color (white, black, inverted)
- **Font**: Choose from different font sizes
- **Contrast**: Adjust display contrast (0-255)
- **Animation Speed**: Control animation speed (1-10)

See the individual configuration pages for more details on each option.

## Component Lifecycle

The Display Manager handles the complete lifecycle of components:

1. **Creation**: Components are created using `new`
2. **Configuration**: Components are configured with position, size, etc.
3. **Registration**: Components are added to the Display Manager
4. **Rendering**: Components are rendered during each update cycle
5. **Removal**: Components are removed when no longer needed

## Best Practices

1. **Initialization**
   - Always call `begin()` before using the display
   - Set configuration options before adding components

2. **Component Management**
   - Add components in the correct order (background to foreground)
   - Remove components when they are no longer needed
   - Use unique IDs for components

3. **Performance**
   - Minimize the number of components
   - Use appropriate update intervals
   - Consider memory constraints

4. **Error Handling**
   - Check for initialization errors
   - Handle component allocation failures
   - Implement proper cleanup 