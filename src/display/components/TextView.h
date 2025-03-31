#ifndef TextView_H
#define TextView_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <vector>
#include <string>

#include "display/IDisplayComponent.h"
#include "display/DisplayManager.h"

// Enum para os presets de página
enum TextViewPresets
{
    TXT_VIEW_BORDERLESS_LEFT,
    TXT_VIEW_BORDERLESS_CENTER,
    TXT_VIEW_BORDERLESS_RIGHT,
    TXT_VIEW_SOLID_BORDER_LEFT,
    TXT_VIEW_SOLID_BORDER_CENTER,
    TXT_VIEW_SOLID_BORDER_RIGHT,
    TXT_VIEW_ROUNDED_BORDER_LEFT,
    TXT_VIEW_ROUNDED_BORDER_CENTER,
    TXT_VIEW_ROUNDED_BORDER_RIGHT
};

class TextView : public IDisplayComponent
{
public:
    TextView(unsigned int id, TextViewPresets preset, const std::vector<String> &text)
        : IDisplayComponent(id), preset(preset), next(id), text(text) {}

    unsigned int render(Adafruit_SSD1306 *disp) override;
    void execute(std::function<unsigned int()> execute);
    void nextComponent(unsigned int nextComponent);

private:
    TextViewPresets preset;
    std::vector<String> text;
    unsigned int next;
    std::function<unsigned int()> exec;

    int startIndex = 0;
    const int maxVisibleLines = 6;

    unsigned int presetTextView1(Adafruit_SSD1306 *display);
    unsigned int presetTextView2(Adafruit_SSD1306 *display);
    unsigned int presetTextView3(Adafruit_SSD1306 *display);
    unsigned int presetTextView4(Adafruit_SSD1306 *display);
    unsigned int presetTextView5(Adafruit_SSD1306 *display);
    unsigned int presetTextView6(Adafruit_SSD1306 *display);
    unsigned int presetTextView7(Adafruit_SSD1306 *display);
    unsigned int presetTextView8(Adafruit_SSD1306 *display);
    unsigned int presetTextView9(Adafruit_SSD1306 *display);
};

#endif