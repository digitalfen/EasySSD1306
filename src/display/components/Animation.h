#ifndef ANIMATION_H
#define ANIMATION_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <vector> // Certifique-se de incluir este cabeçalho
#include <string>

#include "display/IDisplayComponent.h"

enum AnimationPresets
{
    REVEAL_FROM_CENTER,
    SLIDE_FROM_LEFT,
    SLIDE_FROM_RIGHT,
    RISE_AND_FALL,
    FALL_AND_WRAP,
    BOOT_PROGRESS,
    FALL_BLOCK,
    FALL_IN_SEQUENCE,

};

class Animation : public IDisplayComponent
{
public:
    Animation(unsigned int id, AnimationPresets preset, unsigned int next, const char *text)
        : IDisplayComponent(id), preset(preset), next(next), text(text) {}

    unsigned int render(Adafruit_SSD1306 *disp) override;

private:
    AnimationPresets preset;
    const char *text;
    unsigned int next;

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
