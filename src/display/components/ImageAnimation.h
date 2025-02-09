#ifndef ImageAnimation_h
#define ImageAnimation_h

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <vector>

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
    ImageAnimation(unsigned int id, ImageAnimationPresets preset, const uint8_t *imageData, int imageWidth, int imageHeight)
        : IDisplayComponent(id), preset(preset), imageData(imageData), imageWidth(imageWidth), imageHeight(imageHeight), next(id) {}

    unsigned int render(Adafruit_SSD1306 *display) override;

    void execute(std::function<unsigned int()> execute);
    void nextComponent(unsigned int nextComponent);

private:
    ImageAnimationPresets preset;
    const uint8_t *imageData;
    int imageWidth;
    int imageHeight;
    unsigned int next;
    std::function<unsigned int()> exec;

    void slideFromLeft(Adafruit_SSD1306 *display);
    void slideFromRight(Adafruit_SSD1306 *display);
    void slideFromTop(Adafruit_SSD1306 *display);
    void slideFromBottom(Adafruit_SSD1306 *display);
    void pixelByPixel(Adafruit_SSD1306 *display);
    void drawLines(Adafruit_SSD1306 *display);
    void fadeInFadeOut(Adafruit_SSD1306 *display);
};

#endif