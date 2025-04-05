#include "EasySSD1306.h"

// DisplayManager implementation
DisplayManager::DisplayManager()
    : display(DISPLAY_WIDTH, DISPLAY_HEIGHT, &Wire), 
      resolution(RESOLUTION_128x64),
      orientation(ORIENTATION_NORMAL) {
}

void DisplayManager::begin() {
    if (!initialized) {
        display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
        
        // Configure display orientation
        switch(orientation) {
            case ORIENTATION_RIGHT:
                display.setRotation(1);
                break;
            case ORIENTATION_INVERTED:
                display.setRotation(2);
                break;
            case ORIENTATION_LEFT:
                display.setRotation(3);
                break;
            case ORIENTATION_NORMAL:
            default:
                display.setRotation(0);
                break;
        }
        
        display.clearDisplay();
        display.display();
        
        // Configure button pins
        pinMode(btn1Pin, INPUT_PULLUP);
        pinMode(btn2Pin, INPUT_PULLUP);
        
        initialized = true;
    }
}

void DisplayManager::setOrientation(DisplayOrientation newOrientation) {
    if (newOrientation != orientation) {
        orientation = newOrientation;
        
        // If already initialized, apply the new orientation
        if (initialized) {
            switch(orientation) {
                case ORIENTATION_RIGHT:
                    display.setRotation(1);
                    break;
                case ORIENTATION_INVERTED:
                    display.setRotation(2);
                    break;
                case ORIENTATION_LEFT:
                    display.setRotation(3);
                    break;
                case ORIENTATION_NORMAL:
                default:
                    display.setRotation(0);
                    break;
            }
            
            // If orientation changes between horizontal and vertical, swap width and height
            if ((newOrientation == ORIENTATION_RIGHT || newOrientation == ORIENTATION_LEFT) != 
                (orientation == ORIENTATION_RIGHT || orientation == ORIENTATION_LEFT)) {
                int temp = width;
                width = height;
                height = temp;
            }
            
            display.clearDisplay();
            display.display();
        }
    }
}

void DisplayManager::update() {
    if (!initialized) return;
    
    updateButtonStates();
    
    display.clearDisplay();
    
    // Create a viewport for each component based on orientation
    for (auto& component : components) {
        // Antes de renderizar, ajustar o viewport baseado na orientação, se necessário
        component->render(display);
    }
    
    display.display();
}

void DisplayManager::addComponent(Component* component) {
    components.push_back(std::unique_ptr<Component>(component));
}

void DisplayManager::setI2CPins(int sda, int scl) {
    Wire.begin(sda, scl);
}

void DisplayManager::setSPIPins(int mosi, int sclk, int dc, int cs) {
    display = Adafruit_SSD1306(DISPLAY_WIDTH, DISPLAY_HEIGHT, mosi, sclk, dc, -1, cs);
}

void DisplayManager::setButtonPins(int btn1, int btn2) {
    btn1Pin = btn1;
    btn2Pin = btn2;
    
    if (initialized) {
        pinMode(btn1Pin, INPUT_PULLUP);
        pinMode(btn2Pin, INPUT_PULLUP);
    }
}

void DisplayManager::updateButtonStates() {
    btn1LastState = btn1State;
    btn2LastState = btn2State;
    
    btn1State = !digitalRead(btn1Pin);
    btn2State = !digitalRead(btn2Pin);
}

bool DisplayManager::isButton1Pressed() const {
    return btn1State;
}

bool DisplayManager::isButton2Pressed() const {
    return btn2State;
}

bool DisplayManager::wasButton1Pressed() const {
    return btn1LastState;
}

bool DisplayManager::wasButton2Pressed() const {
    return btn2LastState;
}

// TextView implementation
TextView::TextView(const char* text) : text(text), x(0), y(0), style(0), textSize(1), inverted(false) {}

void TextView::adaptToResolution(int width, int height) {
    // Garante que o texto está dentro dos limites do display
    if (x >= width) {
        x = width - 1;
    }
    if (y >= height) {
        y = height - 1;
    }
}

void TextView::adaptToOrientation(DisplayOrientation orientation) {
    // Ajusta a posição baseado na orientação
    int displayWidth = display->width();
    int displayHeight = display->height();
    
    switch(orientation) {
        case ORIENTATION_RIGHT:
            // Para orientação 90°, ajusta para manter legibilidade
            if (x + strlen(text) * 6 * textSize > displayHeight) {
                x = displayHeight - strlen(text) * 6 * textSize;
            }
            break;
        case ORIENTATION_LEFT:
            // Para orientação 270°, ajusta para manter legibilidade
            if (x + strlen(text) * 6 * textSize > displayHeight) {
                x = displayHeight - strlen(text) * 6 * textSize;
            }
            break;
        case ORIENTATION_INVERTED:
            // Para orientação 180°, ajusta para manter legibilidade
            if (x + strlen(text) * 6 * textSize > displayWidth) {
                x = displayWidth - strlen(text) * 6 * textSize;
            }
            break;
        case ORIENTATION_NORMAL:
        default:
            // Para orientação normal, ajusta para manter legibilidade
            if (x + strlen(text) * 6 * textSize > displayWidth) {
                x = displayWidth - strlen(text) * 6 * textSize;
            }
            break;
    }
}

void TextView::render(Adafruit_SSD1306& display) {
    display.setTextSize(textSize);
    display.setTextColor(inverted ? SSD1306_BLACK : SSD1306_WHITE);
    
    // Calcula a largura do texto
    int textWidth = strlen(text) * 6 * textSize;
    int textHeight = 8 * textSize;
    
    // Ajusta a posição baseado no estilo
    int renderX = x;
    int renderY = y;
    
    switch(style) {
        case TXT_VIEW_BORDERLESS_CENTER:
        case TXT_VIEW_SOLID_BORDER_CENTER:
        case TXT_VIEW_ROUNDED_BORDER_CENTER:
        case TXT_VIEW_INVERTED_CENTER:
            renderX = (display.width() - textWidth) / 2;
            break;
        case TXT_VIEW_BORDERLESS_RIGHT:
        case TXT_VIEW_SOLID_BORDER_RIGHT:
        case TXT_VIEW_ROUNDED_BORDER_RIGHT:
        case TXT_VIEW_INVERTED_RIGHT:
            renderX = display.width() - textWidth - 2;
            break;
        default:
            renderX = x + 2;
            break;
    }
    
    // Desenha a borda se necessário
    if (style >= TXT_VIEW_SOLID_BORDER_LEFT && style <= TXT_VIEW_ROUNDED_BORDER_RIGHT) {
        int borderX = renderX - 2;
        int borderY = renderY - 2;
        int borderWidth = textWidth + 4;
        int borderHeight = textHeight + 4;
        
        if (style >= TXT_VIEW_ROUNDED_BORDER_LEFT) {
            // Borda arredondada
            display.drawRoundRect(borderX, borderY, borderWidth, borderHeight, 3, SSD1306_WHITE);
        } else {
            // Borda sólida
            display.drawRect(borderX, borderY, borderWidth, borderHeight, SSD1306_WHITE);
        }
        
        if (inverted) {
            display.fillRect(borderX + 1, borderY + 1, borderWidth - 2, borderHeight - 2, SSD1306_WHITE);
        }
    }
    
    display.setCursor(renderX, renderY);
    display.print(text);
}

void TextView::setText(const char* text) {
    this->text = text;
}

void TextView::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
}

void TextView::setStyle(TextViewStyle style) {
    this->style = style;
}

void TextView::setTextSize(uint8_t size) {
    this->textSize = size;
}

void TextView::setInverted(bool inverted) {
    this->inverted = inverted;
}

// Navigation implementation
Navigation::Navigation(const char* items[], int count)
    : items(items), count(count), selectedIndex(0), style(NAV_STYLE_SIMPLE), itemHeight(20), spacing(5) {}

void Navigation::adaptToResolution(int width, int height) {
    // Calcula quantos itens podem ser exibidos na tela
    visibleItems = height / itemHeight;
    
    // Garante que pelo menos um item seja visível
    if (visibleItems < 1) {
        visibleItems = 1;
    }
}

void Navigation::adaptToOrientation(DisplayOrientation orientation) {
    // Ajusta o layout baseado na orientação
    int displayWidth = display->width();
    int displayHeight = display->height();
    
    switch(orientation) {
        case ORIENTATION_RIGHT:
        case ORIENTATION_LEFT:
            // Para orientações retrato, ajusta o número de itens visíveis
            visibleItems = displayHeight / itemHeight;
            break;
        case ORIENTATION_INVERTED:
        case ORIENTATION_NORMAL:
        default:
            // Para orientações paisagem, ajusta o número de itens visíveis
            visibleItems = displayHeight / itemHeight;
            break;
    }
    
    // Garante que pelo menos um item seja visível
    if (visibleItems < 1) {
        visibleItems = 1;
    }
}

void Navigation::render(Adafruit_SSD1306& display) {
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    
    int startIndex = 0;
    if (selectedIndex >= visibleItems) {
        startIndex = selectedIndex - visibleItems + 1;
    }
    
    for (int i = 0; i < visibleItems && (i + startIndex) < count; i++) {
        int itemY = y + (i * (itemHeight + spacing));
        bool isSelected = (i + startIndex) == selectedIndex;
        
        switch(style) {
            case NAV_STYLE_SIMPLE:
                display.setCursor(x + 2, itemY);
                if (isSelected) display.print("> ");
                display.print(items[i + startIndex]);
                break;
                
            case NAV_STYLE_BOXED:
                if (isSelected) {
                    display.drawRect(x, itemY - 1, display.width() - x, itemHeight + 1, SSD1306_WHITE);
                }
                display.setCursor(x + 4, itemY);
                display.print(items[i + startIndex]);
                break;
                
            case NAV_STYLE_UNDERLINE:
                display.setCursor(x + 2, itemY);
                display.print(items[i + startIndex]);
                if (isSelected) {
                    display.drawFastHLine(x, itemY + itemHeight - 1, display.width() - x, SSD1306_WHITE);
                }
                break;
                
            case NAV_STYLE_HIGHLIGHT:
                if (isSelected) {
                    display.fillRect(x, itemY - 1, display.width() - x, itemHeight + 1, SSD1306_WHITE);
                    display.setTextColor(SSD1306_BLACK);
                }
                display.setCursor(x + 2, itemY);
                display.print(items[i + startIndex]);
                if (isSelected) {
                    display.setTextColor(SSD1306_WHITE);
                }
                break;
                
            case NAV_STYLE_DOTS:
                display.setCursor(x + 2, itemY);
                display.print(items[i + startIndex]);
                if (isSelected) {
                    display.fillCircle(display.width() - 4, itemY + itemHeight/2, 2, SSD1306_WHITE);
                }
                break;
                
            case NAV_STYLE_NUMBERS:
                display.setCursor(x + 2, itemY);
                display.print(i + 1);
                display.print(". ");
                display.print(items[i + startIndex]);
                break;
        }
    }
}

void Navigation::next() {
    selectedIndex = (selectedIndex + 1) % count;
}

void Navigation::previous() {
    selectedIndex = (selectedIndex - 1 + count) % count;
}

int Navigation::getSelectedIndex() const {
    return selectedIndex;
}

void Navigation::setStyle(NavigationStyle style) {
    this->style = style;
}

void Navigation::setItemHeight(int height) {
    this->itemHeight = height;
}

void Navigation::setSpacing(int spacing) {
    this->spacing = spacing;
}

// LoadAnimation implementation
LoadAnimation::LoadAnimation() {}

void LoadAnimation::adaptToResolution(int width, int height) {
    // Ajusta a posição para o centro do display
    x = (width - 8) / 2;  // 8 pixels de largura para o caractere de animação
    y = (height - 8) / 2; // 8 pixels de altura para o caractere de animação
}

void LoadAnimation::adaptToOrientation(DisplayOrientation orientation) {
    // Ajusta a posição baseado na orientação
    int displayWidth = display->width();
    int displayHeight = display->height();
    
    switch(orientation) {
        case ORIENTATION_RIGHT:
        case ORIENTATION_LEFT:
            x = (displayHeight - 8) / 2;
            y = (displayWidth - 8) / 2;
            break;
        case ORIENTATION_INVERTED:
        case ORIENTATION_NORMAL:
        default:
            x = (displayWidth - 8) / 2;
            y = (displayHeight - 8) / 2;
            break;
    }
}

void LoadAnimation::render(Adafruit_SSD1306& display) {
    if (!running) return;
    
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(x, y);
    
    const char* frames[] = {"|", "/", "-", "\\"};
    display.print(frames[frame]);
    
    frame = (frame + 1) % 4;
}

void LoadAnimation::start() {
    running = true;
}

void LoadAnimation::stop() {
    running = false;
}

bool LoadAnimation::isRunning() const {
    return running;
}

// Alert implementation
Alert::Alert(const char* message) : message(message), style(ALERT_STYLE_SIMPLE), progress(0), blinkInterval(500) {}

void Alert::adaptToResolution(int width, int height) {
    // Ajusta a posição para o centro do display
    x = (width - strlen(message) * 6) / 2;  // 6 pixels por caractere
    y = (height - 8) / 2;  // 8 pixels de altura para o texto
}

void Alert::adaptToOrientation(DisplayOrientation orientation) {
    // Ajusta a posição baseado na orientação
    int displayWidth = display->width();
    int displayHeight = display->height();
    
    switch(orientation) {
        case ORIENTATION_RIGHT:
        case ORIENTATION_LEFT:
            x = (displayHeight - strlen(message) * 6) / 2;
            y = (displayWidth - 8) / 2;
            break;
        case ORIENTATION_INVERTED:
        case ORIENTATION_NORMAL:
        default:
            x = (displayWidth - strlen(message) * 6) / 2;
            y = (displayHeight - 8) / 2;
            break;
    }
}

void Alert::render(Adafruit_SSD1306& display) {
    if (!visible) return;
    
    // Verifica se deve piscar
    if (style == ALERT_STYLE_BLINK) {
        unsigned long currentMillis = millis();
        if (currentMillis - lastBlink >= blinkInterval) {
            lastBlink = currentMillis;
            blinkState = !blinkState;
        }
        if (!blinkState) return;
    }
    
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    
    int textWidth = strlen(message) * 6;
    int textHeight = 8;
    int alertWidth = textWidth + 8;
    int alertHeight = textHeight + 8;
    
    // Calcula a posição centralizada
    int alertX = (display.width() - alertWidth) / 2;
    int alertY = (display.height() - alertHeight) / 2;
    
    switch(style) {
        case ALERT_STYLE_SIMPLE:
            display.setCursor(alertX + 4, alertY + 4);
            display.print(message);
            break;
            
        case ALERT_STYLE_BOXED:
            display.drawRect(alertX, alertY, alertWidth, alertHeight, SSD1306_WHITE);
            display.setCursor(alertX + 4, alertY + 4);
            display.print(message);
            break;
            
        case ALERT_STYLE_ROUNDED:
            display.drawRoundRect(alertX, alertY, alertWidth, alertHeight, 3, SSD1306_WHITE);
            display.setCursor(alertX + 4, alertY + 4);
            display.print(message);
            break;
            
        case ALERT_STYLE_ICON:
            if (icon) {
                display.drawBitmap(alertX + 4, alertY + 4, icon, 16, 16, SSD1306_WHITE);
                display.setCursor(alertX + 24, alertY + 4);
            } else {
                display.setCursor(alertX + 4, alertY + 4);
            }
            display.print(message);
            break;
            
        case ALERT_STYLE_PROGRESS:
            display.drawRect(alertX, alertY, alertWidth, alertHeight, SSD1306_WHITE);
            display.setCursor(alertX + 4, alertY + 4);
            display.print(message);
            if (progress > 0) {
                int barWidth = (alertWidth - 4) * progress / 100;
                display.fillRect(alertX + 2, alertY + alertHeight - 4, barWidth, 2, SSD1306_WHITE);
            }
            break;
            
        default:
            display.setCursor(alertX + 4, alertY + 4);
            display.print(message);
            break;
    }
}

void Alert::show() {
    visible = true;
}

void Alert::hide() {
    visible = false;
}

bool Alert::isVisible() const {
    return visible;
}

void Alert::setStyle(AlertStyle style) {
    this->style = style;
}

void Alert::setIcon(const uint8_t* icon) {
    this->icon = icon;
}

void Alert::setProgress(int progress) {
    this->progress = constrain(progress, 0, 100);
}

void Alert::setBlinkInterval(unsigned long interval) {
    this->blinkInterval = interval;
}

// ImageView implementation
ImageView::ImageView(const uint8_t* bitmap, int width, int height)
    : bitmap(bitmap), width(width), height(height), style(IMG_STYLE_NORMAL), scale(1), x(0), y(0), autoCenter(false), inverted(false), borderColor(SSD1306_WHITE), shadowOffset(1) {}

void ImageView::adaptToResolution(int displayWidth, int displayHeight) {
    // Ajusta a escala para caber no display se for maior
    if (width > displayWidth || height > displayHeight) {
        float scaleX = (float)displayWidth / width;
        float scaleY = (float)displayHeight / height;
        scale = min(scaleX, scaleY);
    }
    
    // Se auto-centralizar estiver habilitado, ajusta a posição
    if (autoCenter) {
        x = (displayWidth - (width * scale)) / 2;
        y = (displayHeight - (height * scale)) / 2;
    }
    
    // Garante que a imagem está dentro dos limites do display
    if (x + (width * scale) > displayWidth) {
        x = displayWidth - (width * scale);
    }
    if (y + (height * scale) > displayHeight) {
        y = displayHeight - (height * scale);
    }
    
    // Evita posições negativas
    if (x < 0) x = 0;
    if (y < 0) y = 0;
}

void ImageView::adaptToOrientation(DisplayOrientation orientation) {
    // Ajusta a posição e escala baseado na orientação
    int displayWidth = display->width();
    int displayHeight = display->height();
    
    // Se auto-centralizar estiver habilitado, ajusta a posição
    if (autoCenter) {
        switch(orientation) {
            case ORIENTATION_RIGHT:
            case ORIENTATION_LEFT:
                x = (displayHeight - (width * scale)) / 2;
                y = (displayWidth - (height * scale)) / 2;
                break;
            case ORIENTATION_INVERTED:
            case ORIENTATION_NORMAL:
            default:
                x = (displayWidth - (width * scale)) / 2;
                y = (displayHeight - (height * scale)) / 2;
                break;
        }
    }
    
    // Garante que a imagem está dentro dos limites do display
    switch(orientation) {
        case ORIENTATION_RIGHT:
        case ORIENTATION_LEFT:
            if (x + (width * scale) > displayHeight) {
                x = displayHeight - (width * scale);
            }
            if (y + (height * scale) > displayWidth) {
                y = displayWidth - (height * scale);
            }
            break;
        case ORIENTATION_INVERTED:
        case ORIENTATION_NORMAL:
        default:
            if (x + (width * scale) > displayWidth) {
                x = displayWidth - (width * scale);
            }
            if (y + (height * scale) > displayHeight) {
                y = displayHeight - (height * scale);
            }
            break;
    }
    
    // Evita posições negativas
    if (x < 0) x = 0;
    if (y < 0) y = 0;
}

void ImageView::render(Adafruit_SSD1306& display) {
    int renderWidth = width * scale;
    int renderHeight = height * scale;
    
    switch(style) {
        case IMG_STYLE_NORMAL:
            display.drawBitmap(x, y, bitmap, width, height, SSD1306_WHITE);
            break;
            
        case IMG_STYLE_BORDERED:
            display.drawBitmap(x, y, bitmap, width, height, SSD1306_WHITE);
            display.drawRect(x - 1, y - 1, renderWidth + 2, renderHeight + 2, borderColor);
            break;
            
        case IMG_STYLE_ROUNDED:
            display.drawBitmap(x, y, bitmap, width, height, SSD1306_WHITE);
            display.drawRoundRect(x - 1, y - 1, renderWidth + 2, renderHeight + 2, 3, borderColor);
            break;
            
        case IMG_STYLE_INVERTED:
            display.drawBitmap(x, y, bitmap, width, height, SSD1306_BLACK);
            display.fillRect(x, y, renderWidth, renderHeight, SSD1306_WHITE);
            break;
            
        case IMG_STYLE_SHADOW:
            // Desenha a sombra
            display.fillRect(x + shadowOffset, y + shadowOffset, renderWidth, renderHeight, SSD1306_BLACK);
            // Desenha a imagem
            display.drawBitmap(x, y, bitmap, width, height, SSD1306_WHITE);
            break;
            
        case IMG_STYLE_FRAME:
            // Desenha a moldura
            display.drawRect(x - 2, y - 2, renderWidth + 4, renderHeight + 4, borderColor);
            display.drawRect(x - 1, y - 1, renderWidth + 2, renderHeight + 2, borderColor);
            // Desenha a imagem
            display.drawBitmap(x, y, bitmap, width, height, SSD1306_WHITE);
            break;
    }
}

void ImageView::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
}

void ImageView::setScale(float scale) {
    this->scale = scale;
}

void ImageView::setStyle(ImageViewStyle style) {
    this->style = style;
}

void ImageView::setBorderColor(uint16_t color) {
    this->borderColor = color;
}

void ImageView::setShadowOffset(int offset) {
    this->shadowOffset = offset;
}

// TextAnimation implementation
TextAnimation::TextAnimation(const char* text) : text(text) {}

void TextAnimation::render(Adafruit_SSD1306& display) {
    if (!running) return;
    
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(position, 0);
    display.print(text);
    
    position--;
    if (position < -strlen(text) * 6) {
        position = DISPLAY_WIDTH;
    }
}

void TextAnimation::start() {
    running = true;
    position = DISPLAY_WIDTH;
}

void TextAnimation::stop() {
    running = false;
}

bool TextAnimation::isRunning() const {
    return running;
}

// ImageAnimation implementation
ImageAnimation::ImageAnimation(const uint8_t* frames[], int count, int width, int height)
    : frames(frames), count(count), width(width), height(height) {}

void ImageAnimation::render(Adafruit_SSD1306& display) {
    if (!running) return;
    
    // Verifica se o frame atual está dentro dos limites do display
    if (width > DISPLAY_WIDTH || height > DISPLAY_HEIGHT) {
        return;
    }
    
    display.drawBitmap(0, 0, frames[currentFrame], width, height, 1);
    
    currentFrame = (currentFrame + 1) % count;
}

void ImageAnimation::start() {
    running = true;
    currentFrame = 0;
}

void ImageAnimation::stop() {
    running = false;
}

bool ImageAnimation::isRunning() const {
    return running;
}

// Prompt implementation
Prompt::Prompt(const char* message) : message(message) {}

void Prompt::render(Adafruit_SSD1306& display) {
    if (!visible) return;
    
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print(message);
}

void Prompt::show() {
    visible = true;
}

void Prompt::hide() {
    visible = false;
}

bool Prompt::isVisible() const {
    return visible;
}

void Prompt::setInputType(uint8_t type) {
    inputType = type;
}

void Prompt::setMaxLength(int length) {
    maxLength = length;
}

void DisplayManager::setResolution(DisplayResolution newResolution) {
    if (newResolution != resolution) {
        resolution = newResolution;
        
        // If already initialized, apply the new resolution
        if (initialized) {
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
            
            // Adjust width and height based on orientation
            if (orientation == ORIENTATION_RIGHT || orientation == ORIENTATION_LEFT) {
                int temp = width;
                width = height;
                height = temp;
            }
            
            display.clearDisplay();
            display.display();
        }
    }
} 