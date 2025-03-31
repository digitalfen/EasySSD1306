#ifndef ImageView_h
#define ImageView_h

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "display/IDisplayComponent.h"
#include "display/DisplayManager.h"

enum ImageViewPreset
{
    IMG_VIEW_DEFAULT
};

class ImageView : public IDisplayComponent
{
public:
    ImageView(unsigned int id, ImageViewPreset preset, const uint8_t *imageData, int imageWidth, int imageHeight)
        : IDisplayComponent(id), imageData(imageData), imageWidth(imageWidth), imageHeight(imageHeight), preset(preset), next(id) {}

    unsigned int render(Adafruit_SSD1306 *display) override;

    void execute(std::function<unsigned int()> execute);
    void nextComponent(unsigned int nextComponent);

private:
    const uint8_t *imageData;
    int imageWidth;
    int imageHeight;
    ImageViewPreset preset;
    unsigned int next;
    std::function<unsigned int()> exec;

    unsigned int preset1(Adafruit_SSD1306 *display);
};

#endif