# EasySSD1306
<br> 

The **Easy SSD1306 Library** simplifies the use of SSD1306 OLED displays by providing four core components.<br>  Instead of writing complex code for navigation, rendering, and interaction,<br> you only need to instantiate components and register them.<br> Everything else is handled automatically.

<b>No need to build navigation logic or design layouts—just declare what you need, and it's ready to use!</b>
<br>
---  

# Features  

The library offers a **modular approach**, where each component is instantiated and configured independently. Once registered, the component is automatically rendered when the `render()` method is called inside the main loop.  

## Animation  

Animation provides **dynamic visual effects** that enhance the user interface without affecting program execution. You can use predefined styles or customize your own.  

- **Intro animations**: Includes presets for animated title sequences.  
- **Render images**: Supports custom image rendering using monochrome bitmaps (1-bit per pixel).  
- **Screen savers**: Runs looping animations as a screensaver when inactive.  

## Event  

Event links **visual feedback** with **task execution**, ensuring users see progress indicators during processing.  

- **Process tracking**: Displays animations like loading bars or spinners while tasks run.  
- **Custom event handling**: Define event-triggered animations that execute specific logic.  

## Navigation  

Navigation simplifies user interaction by displaying selectable options linked to other components.  

- **Multiple styles**: Choose from cursor lists, highlighted lists, and vertical/horizontal selectors.  
- **Seamless navigation**: Options map directly to other components, enabling a structured UI flow.  

## View  

View provides an easy way to **display formatted text**, ideal for results, alerts, or documentation.  

- **Scrollable content**: Navigate long-form text efficiently.  
- **Simple & clean design**: Ensures readability without unnecessary complexity.  
- **Intuitive navigation**: Easily move between previous and next states.  

---  

# Project Layout  

```plaintext
mkdocs.yml    # The configuration file.
docs/
    index.md  # The documentation homepage.
    ...       # Other markdown pages, images, and files.
