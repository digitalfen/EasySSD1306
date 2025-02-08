#ifndef TextAnimation_h
#define TextAnimation_h

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <vector>
#include <string>

#include "display/IDisplayComponent.h"

enum TextAnimationPresets
{
    TXT_ANIM_REVEAL_FROM_CENTER,
    TXT_ANIM_SLIDE_FROM_LEFT,
    TXT_ANIM_SLIDE_FROM_RIGHT,
    TXT_ANIM_RISE_AND_FALL,
    TXT_ANIM_FALL_AND_WRAP,
    TXT_ANIM_FALL_BLOCK,
    TXT_ANIM_FALL_IN_SEQUENCE,
};

class TextAnimation : public IDisplayComponent
{
public:
    TextAnimation(unsigned int id, TextAnimationPresets preset, const char *text)
        : IDisplayComponent(id), preset(preset), next(id), text(text) {}

    unsigned int render(Adafruit_SSD1306 *disp) override;

    void execute(std::function<unsigned int()> execute);
    void nextComponent(unsigned int nextComponent);

private:
    TextAnimationPresets preset;
    const char *text;
    unsigned int next;
    std::function<unsigned int()> exec;

    void presetIntro1(Adafruit_SSD1306 *display);
    void presetIntro2(Adafruit_SSD1306 *display);
    void presetIntro3(Adafruit_SSD1306 *display);
    void presetIntro4(Adafruit_SSD1306 *display);
    void presetIntro5(Adafruit_SSD1306 *display);
    void presetIntro6(Adafruit_SSD1306 *display);
    void presetIntro7(Adafruit_SSD1306 *display);
    void presetIntro8(Adafruit_SSD1306 *display);
};

#endif
