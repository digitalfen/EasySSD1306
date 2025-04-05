#ifndef ImageAnimation_h
#define ImageAnimation_h

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <map>
#include <string>

#include "display/IDisplayComponent.h"

enum ImageAnimationPresets
{
    IMG_ANIM_SLIDE_FROM_LEFT,
    IMG_ANIM_SLIDE_FROM_RIGHT,
    IMG_ANIM_SLIDE_FROM_TOP,
    IMG_ANIM_SLIDE_FROM_BOTTOM,
    IMG_ANIM_PIXEL_BY_PIXEL,
    IMG_ANIM_DRAW_LINES,
    IMG_ANIM_FADE_IN_FADE_OUT
};

class ImageAnimation : public IDisplayComponent
{
public:
    ImageAnimation(unsigned int id, const uint8_t *image)
        : IDisplayComponent(id), image(image) {}

    unsigned int render(Adafruit_SSD1306 *disp) override;
    void setImage(const uint8_t *image);
    const uint8_t *getImage();

private:
    const uint8_t *image;
};

#endif