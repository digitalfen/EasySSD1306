#ifndef ImageView_h
#define ImageView_h

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <map>
#include <string>

#include "display/IDisplayComponent.h"

class ImageView : public IDisplayComponent
{
public:
    ImageView(unsigned int id)
        : IDisplayComponent(id) {}

    unsigned int render(Adafruit_SSD1306 *disp) override;
    void setImage(const uint8_t *image);
    const uint8_t *getImage();
    void setScale(float scale);
    float getScale();

private:
    const uint8_t *image;
    float scale = 1.0;
};

#endif