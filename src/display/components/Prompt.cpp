#include "display/components/Prompt.h"
#include <Arduino.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Inicialização dos menus para o teclado virtual
void Prompt::initializeMenus() {
    // Initialize letters menu
    MenuState lettersMenu;
    lettersMenu.type = InputType::LETTERS;
    lettersMenu.currentIndex = 0;
    for (char c = 'A'; c <= 'Z'; c++) {
        lettersMenu.items.push_back(c);
    }
    
    // Initialize numbers menu
    MenuState numbersMenu;
    numbersMenu.type = InputType::NUMBERS;
    numbersMenu.currentIndex = 0;
    for (char c = '0'; c <= '9'; c++) {
        numbersMenu.items.push_back(c);
    }
    
    // Initialize symbols menu
    MenuState symbolsMenu;
    symbolsMenu.type = InputType::SYMBOLS;
    symbolsMenu.currentIndex = 0;
    const char symbols[] = "!@#$%^&*()_+-=[]{}|;:,.<>?";
    for (char c : symbols) {
        symbolsMenu.items.push_back(c);
    }
    
    // Inicializa o estado do prompt
    state.input = "";
    state.currentMenu = lettersMenu;
}

// Método de renderização principal
unsigned int Prompt::render(Adafruit_SSD1306 *display) {
    unsigned int nextView = 0;

    if (exec) {
        next = exec();
    }

    display->clearDisplay();

    // Renderiza o prompt com base no estilo atual
    switch (currentStyle) {
        case PromptStyle::NORMAL:
            renderNormal(display);
            break;
        case PromptStyle::BORDERED:
            renderBordered(display);
            break;
        case PromptStyle::ROUNDED:
            renderRounded(display);
            break;
        case PromptStyle::SHADOW:
            renderShadow(display);
            break;
        case PromptStyle::FRAME:
            renderFrame(display);
            break;
        default:
            // Fallback para os presets antigos
            if (preset == PROMPT_DEFAULT) {
                nextView = preset1(display);
            } else if (preset == PROMPT_WITH_BORDERS) {
                nextView = preset2(display);
            } else {
                display->clearDisplay();
                display->setTextSize(1);
                display->setCursor(0, SCREEN_HEIGHT / 2 - 4);
                display->print("Unknown Prompt request.");
                display->display();
                delay(3000);
            }
            break;
    }
    
    renderButtons(display);
    display->display();

    return nextView;
}

// Métodos de navegação
void Prompt::selectNext() {
    state.currentMenu.currentIndex++;
    if (state.currentMenu.currentIndex >= state.currentMenu.items.size()) {
        state.currentMenu.currentIndex = 0;
    }
}

void Prompt::selectPrevious() {
    state.currentMenu.currentIndex--;
    if (state.currentMenu.currentIndex < 0) {
        state.currentMenu.currentIndex = state.currentMenu.items.size() - 1;
    }
}

void Prompt::confirmSelection() {
    if (state.input.length() < maxLength) {
        state.input += state.currentMenu.items[state.currentMenu.currentIndex];
    }
}

void Prompt::goBack() {
    if (state.input.length() > 0) {
        state.input = state.input.substring(0, state.input.length() - 1);
    }
}

// Métodos de configuração
void Prompt::setMessage(const char *message) {
    this->message = message;
}

const char *Prompt::getMessage() {
    return message;
}

void Prompt::setValue(const char *value) {
    this->value = value;
    state.input = String(value);
}

const char *Prompt::getValue() {
    return value;
}

void Prompt::setMaxLength(int length) {
    maxLength = length;
}

void Prompt::setInputType(InputType type) {
    switchMenu(type);
}

void Prompt::setStyle(PromptStyle style) {
    currentStyle = style;
}

void Prompt::setBorderColor(uint16_t color) {
    borderColor = color;
}

void Prompt::setShadowOffset(int offset) {
    shadowOffset = offset;
}

// Métodos de visibilidade
void Prompt::show() {
    visible = true;
}

void Prompt::hide() {
    visible = false;
}

// Método para executar uma função quando o prompt for confirmado
void Prompt::execute(std::function<unsigned int()> execute) {
    this->exec = execute;
}

void Prompt::nextComponent(unsigned int nextComponent) {
    this->next = nextComponent;
}

// Métodos de renderização dos presets antigos
unsigned int Prompt::preset1(Adafruit_SSD1306 *display) {
    display->setTextSize(1);
    display->setTextColor(WHITE);
    display->setCursor(10, 10);
    display->print(message);

    if (DisplayManager::confirmItem) {
        return next;
    }

    return id;
}

unsigned int Prompt::preset2(Adafruit_SSD1306 *display) {
    display->drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE); // Desenha a borda

    display->setTextSize(1);
    display->setTextColor(WHITE);
    display->setCursor(10, 10);
    display->print(message);

    if (DisplayManager::confirmItem) {
        return next;
    }

    return id;
}

void Prompt::renderButtons(Adafruit_SSD1306 *display) {
    display->setTextSize(1);
    display->setTextColor(WHITE);

    display->fillRect(10, SCREEN_HEIGHT - 20, 50, 15, WHITE); // Fundo branco
    display->setTextColor(BLACK);                             // Texto preto
    display->setCursor(15, SCREEN_HEIGHT - 18);               // Posição do texto
    display->print("Cancel");

    display->fillRect(SCREEN_WIDTH - 60, SCREEN_HEIGHT - 20, 50, 15, WHITE); // Fundo branco
    display->setTextColor(BLACK);                                            // Texto preto
    display->setCursor(SCREEN_WIDTH - 55, SCREEN_HEIGHT - 18);               // Posição do texto
    display->print("Confirm");
}

// Métodos do teclado virtual
void Prompt::switchMenu(InputType type) {
    MenuState newMenu;
    newMenu.type = type;
    newMenu.currentIndex = 0;
    
    switch (type) {
        case InputType::LETTERS:
            for (char c = 'A'; c <= 'Z'; c++) {
                newMenu.items.push_back(c);
            }
            break;
        case InputType::NUMBERS:
            for (char c = '0'; c <= '9'; c++) {
                newMenu.items.push_back(c);
            }
            break;
        case InputType::SYMBOLS:
            const char symbols[] = "!@#$%^&*()_+-=[]{}|;:,.<>?";
            for (char c : symbols) {
                newMenu.items.push_back(c);
            }
            break;
    }
    
    state.currentMenu = newMenu;
}

void Prompt::showPreview() {
    isPreviewMode = true;
}

void Prompt::hidePreview() {
    isPreviewMode = false;
}

void Prompt::updateMenuItems() {
    // Atualiza os itens do menu com base no tipo de entrada
    switchMenu(state.currentMenu.type);
}

void Prompt::handleButtonPress() {
    // Lógica para lidar com os botões
    if (DisplayManager::confirmItem) {
        confirmSelection();
    } else if (DisplayManager::cancelItem) {
        goBack();
    }
}

// Métodos de renderização dos estilos
void Prompt::renderNormal(Adafruit_SSD1306 *display) {
    display->setTextSize(1);
    display->setTextColor(WHITE);
    display->setCursor(10, 10);
    display->print(message);
    
    // Renderiza o teclado virtual
    int startX = 10;
    int startY = 20;
    int keyWidth = 10;
    int keyHeight = 10;
    int keysPerRow = 10;
    
    // Renderiza as teclas
    for (size_t i = 0; i < state.currentMenu.items.size(); i++) {
        int row = i / keysPerRow;
        int col = i % keysPerRow;
        
        int x = startX + (col * keyWidth);
        int y = startY + (row * keyHeight);
        
        // Destaca a tecla selecionada
        if (i == state.currentMenu.currentIndex) {
            display->fillRect(x, y, keyWidth, keyHeight, WHITE);
            display->setTextColor(BLACK);
        } else {
            display->drawRect(x, y, keyWidth, keyHeight, WHITE);
            display->setTextColor(WHITE);
        }
        
        display->setCursor(x + 2, y + 2);
        display->print(state.currentMenu.items[i]);
    }
    
    // Renderiza o texto de entrada
    display->setTextColor(WHITE);
    display->setCursor(10, SCREEN_HEIGHT - 30);
    display->print("Input: ");
    display->print(state.input.c_str());
}

void Prompt::renderBordered(Adafruit_SSD1306 *display) {
    // Desenha a borda
    display->drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, borderColor);
    
    // Renderiza o conteúdo
    renderNormal(display);
}

void Prompt::renderRounded(Adafruit_SSD1306 *display) {
    // Desenha cantos arredondados
    display->drawRoundRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 10, borderColor);
    
    // Renderiza o conteúdo
    renderNormal(display);
}

void Prompt::renderShadow(Adafruit_SSD1306 *display) {
    // Desenha a sombra
    display->fillRect(shadowOffset, shadowOffset, SCREEN_WIDTH, SCREEN_HEIGHT, borderColor);
    
    // Desenha o conteúdo principal
    display->fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BLACK);
    
    // Renderiza o conteúdo
    renderNormal(display);
}

void Prompt::renderFrame(Adafruit_SSD1306 *display) {
    // Desenha a moldura
    display->drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, borderColor);
    display->drawRect(2, 2, SCREEN_WIDTH - 4, SCREEN_HEIGHT - 4, borderColor);
    
    // Renderiza o conteúdo
    renderNormal(display);
}