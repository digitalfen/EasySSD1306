#ifndef TextView_h
#define TextView_h

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <map>
#include <string>

#include "display/IDisplayComponent.h"

class TextView : public IDisplayComponent
{
public:
    TextView(unsigned int id, const char *text)
        : IDisplayComponent(id), text(text) {}

    unsigned int render(Adafruit_SSD1306 *disp) override;
    void setText(const char *text);
    const char *getText();

private:
    const char *text;
};

#endif