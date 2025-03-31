#ifndef EASYSSD1306_H
#define EASYSSD1306_H

#include <Adafruit_SSD1306.h>
#include <vector>
#include <memory>

// Display resolutions
#define SSD1306_128_64
//#define SSD1306_128_32
//#define SSD1306_96_64

// Platform-specific pin definitions
#if defined(ARDUINO_AVR_UNO)
    #define DEFAULT_SDA A4
    #define DEFAULT_SCL A5
    #define DEFAULT_BTN1 2  // INT0 pin for better interrupt support
    #define DEFAULT_BTN2 3  // INT1 pin for better interrupt support
#elif defined(ESP32)
    #define DEFAULT_SDA 21
    #define DEFAULT_SCL 22
    #define DEFAULT_BTN1 4  // GPIO4
    #define DEFAULT_BTN2 5  // GPIO5
#elif defined(ESP8266)
    #define DEFAULT_SDA D2
    #define DEFAULT_SCL D1
    #define DEFAULT_BTN1 D3  // GPIO0
    #define DEFAULT_BTN2 D4  // GPIO2
#else
    #define DEFAULT_SDA -1
    #define DEFAULT_SCL -1
    #define DEFAULT_BTN1 -1
    #define DEFAULT_BTN2 -1
#endif

// Display dimensions based on resolution
#if defined(SSD1306_128_64)
    #define DISPLAY_WIDTH 128
    #define DISPLAY_HEIGHT 64
#elif defined(SSD1306_128_32)
    #define DISPLAY_WIDTH 128
    #define DISPLAY_HEIGHT 32
#elif defined(SSD1306_96_64)
    #define DISPLAY_WIDTH 96
    #define DISPLAY_HEIGHT 64
#else
    #define DISPLAY_WIDTH 128
    #define DISPLAY_HEIGHT 64
#endif

// Component base class
class Component {
public:
    virtual void render(Adafruit_SSD1306& display) = 0;
    virtual ~Component() = default;
};

// Display manager class
class DisplayManager {
public:
    DisplayManager();
    
    void begin();
    void update();
    void addComponent(Component* component);
    void setI2CPins(int sda, int scl);
    void setSPIPins(int mosi, int sclk, int dc, int cs);
    void setButtonPins(int btn1, int btn2);
    
    // Button state methods
    bool isButton1Pressed() const;
    bool isButton2Pressed() const;
    bool wasButton1Pressed() const;
    bool wasButton2Pressed() const;
    
    Adafruit_SSD1306& getDisplay() { return display; }
    
    // Get display dimensions
    int getWidth() const { return DISPLAY_WIDTH; }
    int getHeight() const { return DISPLAY_HEIGHT; }
    
private:
    Adafruit_SSD1306 display;
    std::vector<std::unique_ptr<Component>> components;
    bool initialized = false;
    
    // Button pins
    int btn1Pin = DEFAULT_BTN1;
    int btn2Pin = DEFAULT_BTN2;
    
    // Button states
    bool btn1State = false;
    bool btn2State = false;
    bool btn1LastState = false;
    bool btn2LastState = false;
    
    // Button reading methods
    void updateButtonStates();
};

// Text view component
class TextView : public Component {
public:
    TextView(const char* text);
    void render(Adafruit_SSD1306& display) override;
    void setText(const char* text);
    void setPosition(int x, int y);
    void setStyle(uint8_t style);
    
private:
    const char* text;
    int x = 0;
    int y = 0;
    uint8_t style = 0;
};

// Navigation component
class Navigation : public Component {
public:
    Navigation(const char* items[], int count);
    void render(Adafruit_SSD1306& display) override;
    void next();
    void previous();
    int getSelectedIndex() const;
    
private:
    const char** items;
    int count;
    int selectedIndex = 0;
};

// Load animation component
class LoadAnimation : public Component {
public:
    LoadAnimation();
    void render(Adafruit_SSD1306& display) override;
    void start();
    void stop();
    bool isRunning() const;
    
private:
    bool running = false;
    int frame = 0;
};

// Alert component
class Alert : public Component {
public:
    Alert(const char* message);
    void render(Adafruit_SSD1306& display) override;
    void show();
    void hide();
    bool isVisible() const;
    
private:
    const char* message;
    bool visible = false;
};

// Image view component
class ImageView : public Component {
public:
    ImageView(const uint8_t* bitmap, int width, int height);
    void render(Adafruit_SSD1306& display) override;
    void setPosition(int x, int y);
    void setScale(float scale);
    
private:
    const uint8_t* bitmap;
    int width;
    int height;
    int x = 0;
    int y = 0;
    float scale = 1.0;
};

// Text animation component
class TextAnimation : public Component {
public:
    TextAnimation(const char* text);
    void render(Adafruit_SSD1306& display) override;
    void start();
    void stop();
    bool isRunning() const;
    
private:
    const char* text;
    bool running = false;
    int position = 0;
};

// Image animation component
class ImageAnimation : public Component {
public:
    ImageAnimation(const uint8_t* frames[], int count, int width, int height);
    void render(Adafruit_SSD1306& display) override;
    void start();
    void stop();
    bool isRunning() const;
    
private:
    const uint8_t** frames;
    int count;
    int width;
    int height;
    bool running = false;
    int currentFrame = 0;
};

// Prompt component
class Prompt : public Component {
public:
    Prompt(const char* message);
    void render(Adafruit_SSD1306& display) override;
    void show();
    void hide();
    bool isVisible() const;
    void setInputType(uint8_t type);
    void setMaxLength(int length);
    
private:
    const char* message;
    bool visible = false;
    uint8_t inputType = 0;
    int maxLength = 32;
};

#endif // EASYSSD1306_H 