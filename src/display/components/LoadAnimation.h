#ifndef LoadAnimation_h
#define LoadAnimation_h

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <map>
#include <string>

#include "display/IDisplayComponent.h"

enum LoadAnimationPresets
{
    LOAD_ANIM_PROGRESS_BAR,
    LOAD_ANIM_CIRCLE_SWEEP,
    LOAD_ANIM_DOT_SEQUENCE
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
    unsigned int next;

    LoadAnimationPresets preset;

    void presetLoadAnimation1(Adafruit_SSD1306 *display);
    void presetLoadAnimation2(Adafruit_SSD1306 *display);
    void presetLoadAnimation3(Adafruit_SSD1306 *display);
};

#endif
