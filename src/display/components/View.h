#ifndef View_H
#define View_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <vector>
#include <string>

#include "display/IDisplayComponent.h"

// Enum para os presets de página
enum ViewPresets
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

class View : public IDisplayComponent
{
public:
    View(unsigned int id, ViewPresets preset, const std::vector<String> &text)
        : IDisplayComponent(id), preset(preset), next(id), text(text) {}

    unsigned int render(Adafruit_SSD1306 *disp) override;
    void execute(std::function<unsigned int()> execute);
    void nextComponent(unsigned int nextComponent);

private:
    ViewPresets preset;
    std::vector<String> text;
    unsigned int next;
    std::function<unsigned int()> exec;

    int startIndex = 0;
    const int maxVisibleLines = 6;

    unsigned int presetView1(Adafruit_SSD1306 *display);
    unsigned int presetView2(Adafruit_SSD1306 *display);
    unsigned int presetView3(Adafruit_SSD1306 *display);
    unsigned int presetView4(Adafruit_SSD1306 *display);
    unsigned int presetView5(Adafruit_SSD1306 *display);
    unsigned int presetView6(Adafruit_SSD1306 *display);
    unsigned int presetView7(Adafruit_SSD1306 *display);
    unsigned int presetView8(Adafruit_SSD1306 *display);
    unsigned int presetView9(Adafruit_SSD1306 *display);
};

#endif