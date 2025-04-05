#ifndef Prompt_h
#define Prompt_h

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <vector>
#include <string>
#include <functional>

#include "display/IDisplayComponent.h"
#include "display/DisplayManager.h"

// Tipos de entrada disponíveis
enum class InputType {
    LETTERS,
    NUMBERS,
    SYMBOLS
};

// Estilos de prompt disponíveis
enum class PromptStyle {
    NORMAL,
    BORDERED,
    ROUNDED,
    SHADOW,
    FRAME
};

// Presets de prompt para compatibilidade
enum PromptPresets {
    PROMPT_DEFAULT,     // preset1
    PROMPT_WITH_BORDERS // preset2
};

// Estrutura para armazenar o estado do menu
struct MenuState {
    InputType type;
    int currentIndex;
    std::vector<char> items;
};

// Estrutura para armazenar o estado do prompt
struct PromptState {
    String input;
    MenuState currentMenu;
};

class Prompt : public IDisplayComponent
{
public:
    // Construtor para compatibilidade com a interface IDisplayComponent
    Prompt(unsigned int id, PromptPresets preset, const char *message)
        : IDisplayComponent(id), message(message), preset(preset), next(id), scrollOffset(0) {
        initializeMenus();
        maxLength = 20;
        isPreviewMode = false;
        currentStyle = PromptStyle::NORMAL;
        borderColor = SSD1306_WHITE;
        shadowOffset = 2;
    }
    
    // Construtor para o novo Prompt com teclado virtual
    Prompt(unsigned int id, const char *title, const char *initialValue = "")
        : IDisplayComponent(id), message(title), preset(PROMPT_DEFAULT), next(id), scrollOffset(0) {
        initializeMenus();
        maxLength = 20;
        isPreviewMode = false;
        currentStyle = PromptStyle::NORMAL;
        borderColor = SSD1306_WHITE;
        shadowOffset = 2;
        setValue(initialValue);
    }

    // Método de renderização da interface IDisplayComponent
    unsigned int render(Adafruit_SSD1306 *display) override;
    
    // Métodos de navegação
    void nextComponent(unsigned int nextComponent);
    void selectNext();
    void selectPrevious();
    void confirmSelection();
    void goBack();
    
    // Métodos de configuração
    void setMessage(const char *message);
    const char *getMessage();
    void setValue(const char *value);
    const char *getValue();
    void setMaxLength(int length);
    void setInputType(InputType type);
    void setStyle(PromptStyle style);
    void setBorderColor(uint16_t color);
    void setShadowOffset(int offset);
    
    // Métodos de visibilidade
    void show();
    void hide();
    
    // Método para executar uma função quando o prompt for confirmado
    void execute(std::function<unsigned int()> execute);

private:
    const char *message;
    PromptPresets preset;
    unsigned int next;
    int scrollOffset;
    const char *value = "";
    bool visible = true;
    std::function<unsigned int()> exec;
    
    // Novas propriedades para o teclado virtual
    PromptState state;
    int maxLength;
    bool isPreviewMode;
    PromptStyle currentStyle;
    uint16_t borderColor;
    int shadowOffset;
    
    // Métodos de renderização
    unsigned int preset1(Adafruit_SSD1306 *display); // Estilo simples
    unsigned int preset2(Adafruit_SSD1306 *display); // Estilo com borda
    void renderButtons(Adafruit_SSD1306 *display);   // Renderiza os botões
    
    // Métodos do teclado virtual
    void initializeMenus();
    void switchMenu(InputType type);
    void showPreview();
    void hidePreview();
    void updateMenuItems();
    void handleButtonPress();
    void renderNormal(Adafruit_SSD1306 *display);
    void renderBordered(Adafruit_SSD1306 *display);
    void renderRounded(Adafruit_SSD1306 *display);
    void renderShadow(Adafruit_SSD1306 *display);
    void renderFrame(Adafruit_SSD1306 *display);
};

#endif