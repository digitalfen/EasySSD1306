#ifndef PAGE_H
#define PAGE_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <vector>
#include <string>

#include "display/IDisplayComponent.h"

// Enum para os presets de página
enum PagePresets
{
    BORDERLESS_LEFT,
    BORDERLESS_CENTER,
    BORDERLESS_RIGHT,
    SOLID_BORDER_LEFT,
    SOLID_BORDER_CENTER,
    SOLID_BORDER_RIGHT,
    ROUNDED_BORDER_LEFT,
    ROUNDED_BORDER_CENTER,
    ROUNDED_BORDER_RIGHT
};

class Page : public IDisplayComponent
{
public:
    // Construtor da classe Page
    Page(unsigned int id, PagePresets preset, unsigned int next, const std::vector<String> &text)
        : IDisplayComponent(id), preset(preset), next(next), text(text) {}

    unsigned int render(Adafruit_SSD1306 *disp) override;

private:
    PagePresets preset;       // Preset da página
    std::vector<String> text; // Texto a ser exibido, linha por linha
    unsigned int next;

    int startIndex = 0;            // Índice da primeira linha visível
    const int maxVisibleLines = 6; // Número máximo de linhas visíve

    unsigned int presetPage1(Adafruit_SSD1306 *display);
    unsigned int presetPage2(Adafruit_SSD1306 *display);
    unsigned int presetPage3(Adafruit_SSD1306 *display);
    unsigned int presetPage4(Adafruit_SSD1306 *display);
    unsigned int presetPage5(Adafruit_SSD1306 *display);
    unsigned int presetPage6(Adafruit_SSD1306 *display);
    unsigned int presetPage7(Adafruit_SSD1306 *display);
    unsigned int presetPage8(Adafruit_SSD1306 *display);
    unsigned int presetPage9(Adafruit_SSD1306 *display);
};

#endif