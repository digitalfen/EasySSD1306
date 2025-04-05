#ifndef TextAnimation_h
#define TextAnimation_h

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <map>
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
    TextAnimation(unsigned int id, const char *text)
        : IDisplayComponent(id), text(text) {}

    unsigned int render(Adafruit_SSD1306 *disp) override;
    void setText(const char *text);
    const char *getText();

private:
    const char *text;
};

#endif
