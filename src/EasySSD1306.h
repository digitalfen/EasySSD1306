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

enum DisplayResolution {
    RESOLUTION_128x32,  // 128x32 pixels
    RESOLUTION_128x64,  // 128x64 pixels
    RESOLUTION_96x16,   // 96x16 pixels
    RESOLUTION_64x48,   // 64x48 pixels
    RESOLUTION_64x32    // 64x32 pixels
};

enum DisplayOrientation {
    ORIENTATION_NORMAL,    // 0 degrees (normal)
    ORIENTATION_RIGHT,     // 90 degrees (rotated right)
    ORIENTATION_INVERTED,  // 180 degrees (upside down)
    ORIENTATION_LEFT       // 270 degrees (rotated left)
};

// Estilos para TextView
enum TextViewStyle {
    TXT_VIEW_BORDERLESS_LEFT,    // Texto alinhado à esquerda sem borda
    TXT_VIEW_BORDERLESS_CENTER,  // Texto centralizado sem borda
    TXT_VIEW_BORDERLESS_RIGHT,   // Texto alinhado à direita sem borda
    TXT_VIEW_SOLID_BORDER_LEFT,  // Texto alinhado à esquerda com borda sólida
    TXT_VIEW_SOLID_BORDER_CENTER,// Texto centralizado com borda sólida
    TXT_VIEW_SOLID_BORDER_RIGHT, // Texto alinhado à direita com borda sólida
    TXT_VIEW_ROUNDED_BORDER_LEFT,// Texto alinhado à esquerda com borda arredondada
    TXT_VIEW_ROUNDED_BORDER_CENTER,// Texto centralizado com borda arredondada
    TXT_VIEW_ROUNDED_BORDER_RIGHT,// Texto alinhado à direita com borda arredondada
    TXT_VIEW_INVERTED_LEFT,      // Texto invertido alinhado à esquerda
    TXT_VIEW_INVERTED_CENTER,    // Texto invertido centralizado
    TXT_VIEW_INVERTED_RIGHT      // Texto invertido alinhado à direita
};

// Estilos para Navigation
enum NavigationStyle {
    NAV_STYLE_SIMPLE,           // Navegação simples com indicador '>'
    NAV_STYLE_BOXED,           // Navegação com caixa ao redor do item selecionado
    NAV_STYLE_UNDERLINE,       // Navegação com linha sob o item selecionado
    NAV_STYLE_HIGHLIGHT,       // Navegação com item selecionado destacado
    NAV_STYLE_DOTS,            // Navegação com pontos indicadores
    NAV_STYLE_NUMBERS          // Navegação com números
};

// Estilos para Alert
enum AlertStyle {
    ALERT_STYLE_SIMPLE,        // Alerta simples
    ALERT_STYLE_BOXED,         // Alerta com caixa
    ALERT_STYLE_ROUNDED,       // Alerta com caixa arredondada
    ALERT_STYLE_ICON,          // Alerta com ícone
    ALERT_STYLE_BLINK,         // Alerta piscante
    ALERT_STYLE_PROGRESS       // Alerta com barra de progresso
};

// Estilos para ImageView
enum ImageViewStyle {
    IMG_STYLE_NORMAL,          // Imagem normal
    IMG_STYLE_BORDERED,        // Imagem com borda
    IMG_STYLE_ROUNDED,         // Imagem com borda arredondada
    IMG_STYLE_INVERTED,        // Imagem invertida
    IMG_STYLE_SHADOW,          // Imagem com sombra
    IMG_STYLE_FRAME            // Imagem com moldura
};

// Component base class
class Component {
public:
    virtual void render(Adafruit_SSD1306& display) = 0;
    virtual ~Component() = default;
    
    // Métodos para adaptar componentes à orientação e resolução
    virtual void adaptToResolution(int width, int height) {}
    virtual void adaptToOrientation(DisplayOrientation orientation) {}
    
    // Define se o componente deve se adaptar automaticamente à resolução/orientação
    void setAutoAdapt(bool adapt) { autoAdapt = adapt; }
    bool getAutoAdapt() const { return autoAdapt; }
    
protected:
    bool autoAdapt = true;  // Por padrão, componentes se adaptam automaticamente
};

// Display manager class
class DisplayManager {
public:
    DisplayManager(DisplayResolution resolution = RESOLUTION_128x64) {
        switch(resolution) {
            case RESOLUTION_128x32:
                width = 128;
                height = 32;
                break;
            case RESOLUTION_96x16:
                width = 96;
                height = 16;
                break;
            case RESOLUTION_64x48:
                width = 64;
                height = 48;
                break;
            case RESOLUTION_64x32:
                width = 64;
                height = 32;
                break;
            case RESOLUTION_128x64:
            default:
                width = 128;
                height = 64;
                break;
        }
        
        display = new Adafruit_SSD1306(width, height, &Wire);
        
        // Valores padrão
        orientation = ORIENTATION_NORMAL;
        color = COLOR_WHITE;
        font = FONT_5x7;
        contrast = 128;
        animationSpeed = 5;
    }
    
    bool begin(uint8_t i2cAddress = 0x3C) {
        if(!display->begin(SSD1306_SWITCHCAPVCC, i2cAddress)) {
            return false;
        }
        
        // Configure display orientation
        switch(orientation) {
            case ORIENTATION_RIGHT:
                display->setRotation(1);
                break;
            case ORIENTATION_INVERTED:
                display->setRotation(2);
                break;
            case ORIENTATION_LEFT:
                display->setRotation(3);
                break;
            case ORIENTATION_NORMAL:
            default:
                display->setRotation(0);
                break;
        }
        
        display->clearDisplay();
        display->display();
        return true;
    }

    void update() {
        if (!initialized) return;
        
        updateButtonStates();
        
        display->clearDisplay();
        
        for (auto& component : components) {
            // Se componente estiver configurado para adaptação automática, ajustá-lo
            if (component->getAutoAdapt()) {
                component->adaptToResolution(width, height);
                component->adaptToOrientation(orientation);
            }
            component->render(*display);
        }
        
        display->display();
    }

    void addComponent(Component* component);
    void setI2CPins(int sda, int scl);
    void setSPIPins(int mosi, int sclk, int dc, int cs);
    void setButtonPins(int btn1, int btn2);
    
    // Button state methods
    bool isButton1Pressed() const;
    bool isButton2Pressed() const;
    bool wasButton1Pressed() const;
    bool wasButton2Pressed() const;
    
    // Orientação e resolução
    void setOrientation(DisplayOrientation newOrientation);
    DisplayOrientation getOrientation() const { return orientation; }
    DisplayResolution getResolution() const { return resolution; }
    
    // Método simplificado para rotação em tempo real
    void setDisplayRotation(uint8_t rotation) {
        if (initialized && display) {
            display->setRotation(rotation % 4); // Garante que a rotação esteja entre 0-3
            display->clearDisplay();
            display->display();
        }
    }
    
    Adafruit_SSD1306& getDisplay() { return *display; }
    
    // Get display dimensions
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    
private:
    int width;
    int height;
    DisplayResolution resolution;
    DisplayOrientation orientation;
    std::vector<Component*> components;
    Adafruit_SSD1306* display;
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
    void adaptToResolution(int width, int height) override;
    void adaptToOrientation(DisplayOrientation orientation) override;
    void setText(const char* text);
    void setPosition(int x, int y);
    void setStyle(TextViewStyle style);
    void setTextSize(uint8_t size);
    void setInverted(bool inverted);
    
private:
    const char* text;
    int x = 0;
    int y = 0;
    TextViewStyle style = TXT_VIEW_BORDERLESS_LEFT;
    uint8_t textSize = 1;
    bool inverted = false;
};

// Navigation component
class Navigation : public Component {
public:
    Navigation(const char* items[], int count);
    void render(Adafruit_SSD1306& display) override;
    void adaptToResolution(int width, int height) override;
    void adaptToOrientation(DisplayOrientation orientation) override;
    void next();
    void previous();
    int getSelectedIndex() const;
    void setStyle(NavigationStyle style);
    void setItemHeight(int height);
    void setSpacing(int spacing);
    
private:
    const char** items;
    int count;
    int selectedIndex = 0;
    int itemHeight = 8;
    int spacing = 2;
    int visibleItems = 0;
    NavigationStyle style = NAV_STYLE_SIMPLE;
};

// Load animation component
class LoadAnimation : public Component {
public:
    LoadAnimation();
    void render(Adafruit_SSD1306& display) override;
    void adaptToResolution(int width, int height) override;
    void adaptToOrientation(DisplayOrientation orientation) override;
    void start();
    void stop();
    bool isRunning() const;
    
private:
    bool running = false;
    int frame = 0;
    int x = 0;
    int y = 0;
};

// Alert component
class Alert : public Component {
public:
    Alert(const char* message);
    void render(Adafruit_SSD1306& display) override;
    void adaptToResolution(int width, int height) override;
    void adaptToOrientation(DisplayOrientation orientation) override;
    void show();
    void hide();
    bool isVisible() const;
    void setStyle(AlertStyle style);
    void setIcon(const uint8_t* icon);
    void setProgress(int progress);
    void setBlinkInterval(unsigned long interval);
    
private:
    const char* message;
    const uint8_t* icon = nullptr;
    bool visible = false;
    int x = 0;
    int y = 0;
    AlertStyle style = ALERT_STYLE_SIMPLE;
    int progress = 0;
    unsigned long blinkInterval = 500;
    unsigned long lastBlink = 0;
    bool blinkState = true;
};

// Image view component
class ImageView : public Component {
public:
    ImageView(const uint8_t* bitmap, int width, int height);
    void render(Adafruit_SSD1306& display) override;
    void adaptToResolution(int width, int height) override;
    void adaptToOrientation(DisplayOrientation orientation) override;
    void setPosition(int x, int y);
    void setScale(float scale);
    void setAutoCenter(bool center) { autoCenter = center; }
    void setStyle(ImageViewStyle style);
    void setBorderColor(uint16_t color);
    void setShadowOffset(int offset);
    
private:
    const uint8_t* bitmap;
    int width;
    int height;
    int x = 0;
    int y = 0;
    float scale = 1.0;
    bool autoCenter = false;
    ImageViewStyle style = IMG_STYLE_NORMAL;
    uint16_t borderColor = SSD1306_WHITE;
    int shadowOffset = 2;
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