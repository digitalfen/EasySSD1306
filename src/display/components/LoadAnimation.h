#ifndef LoadAnimation_h
#define LoadAnimation_h

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <map>
#include <string>

#include "display/IDisplayComponent.h"

enum LoadAnimationPresets
{
    PROGRESS_BAR,
    CIRCLE_SWEEP,
    DOT_SEQUENCE
};

class LoadAnimation : public IDisplayComponent
{
public:
    LoadAnimation(unsigned int id, LoadAnimationPresets preset)
        : IDisplayComponent(id), preset(preset), next(id) {}

    unsigned int render(Adafruit_SSD1306 *disp) override;
    void execute(std::function<unsigned int()> execute);
    void nextComponent(unsigned int nextComponent);

private:
    std::function<unsigned int()> exec;
    const char *text;
    unsigned int next;

    LoadAnimationPresets preset; // Preset do menu

    // Métodos privados para renderizar os menus específicos
    unsigned int presetLoadAnimation1(Adafruit_SSD1306 *display);
    unsigned int presetLoadAnimation2(Adafruit_SSD1306 *display);
    unsigned int presetLoadAnimation3(Adafruit_SSD1306 *display);
};

#endif
