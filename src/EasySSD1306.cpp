#include "EasySSD1306.h"

// DisplayManager implementation
DisplayManager::DisplayManager()
    : display(DISPLAY_WIDTH, DISPLAY_HEIGHT, &Wire) {
}

void DisplayManager::begin() {
    if (!initialized) {
        display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
        display.clearDisplay();
        display.display();
        
        // Configure button pins
        pinMode(btn1Pin, INPUT_PULLUP);
        pinMode(btn2Pin, INPUT_PULLUP);
        
        initialized = true;
    }
}

void DisplayManager::update() {
    if (!initialized) return;
    
    updateButtonStates();
    
    display.clearDisplay();
    
    for (auto& component : components) {
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
TextView::TextView(const char* text) : text(text) {}

void TextView::render(Adafruit_SSD1306& display) {
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(x, y);
    display.print(text);
}

void TextView::setText(const char* text) {
    this->text = text;
}

void TextView::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
}

void TextView::setStyle(uint8_t style) {
    this->style = style;
}

// Navigation implementation
Navigation::Navigation(const char* items[], int count)
    : items(items), count(count) {}

void Navigation::render(Adafruit_SSD1306& display) {
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    
    // Ajusta o número de itens visíveis baseado na altura do display
    int visibleItems = DISPLAY_HEIGHT / 8;
    int startIndex = 0;
    
    if (selectedIndex >= visibleItems) {
        startIndex = selectedIndex - visibleItems + 1;
    }
    
    for (int i = 0; i < visibleItems && (i + startIndex) < count; i++) {
        display.setCursor(0, i * 8);
        if ((i + startIndex) == selectedIndex) {
            display.print("> ");
        }
        display.print(items[i + startIndex]);
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

// LoadAnimation implementation
LoadAnimation::LoadAnimation() {}

void LoadAnimation::render(Adafruit_SSD1306& display) {
    if (!running) return;
    
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    
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
Alert::Alert(const char* message) : message(message) {}

void Alert::render(Adafruit_SSD1306& display) {
    if (!visible) return;
    
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print(message);
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

// ImageView implementation
ImageView::ImageView(const uint8_t* bitmap, int width, int height)
    : bitmap(bitmap), width(width), height(height) {}

void ImageView::render(Adafruit_SSD1306& display) {
    // Verifica se a imagem está dentro dos limites do display
    if (x + width > DISPLAY_WIDTH || y + height > DISPLAY_HEIGHT) {
        return;
    }
    
    display.drawBitmap(x, y, bitmap, width, height, 1);
}

void ImageView::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
}

void ImageView::setScale(float scale) {
    this->scale = scale;
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