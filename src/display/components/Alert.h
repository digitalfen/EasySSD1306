#ifndef Alert_h
#define Alert_h

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <map>
#include <string>

#include "display/IDisplayComponent.h"

class Alert : public IDisplayComponent
{
public:
    Alert(unsigned int id, const char *message, unsigned int duration)
        : IDisplayComponent(id), message(message), duration(duration) {}

    unsigned int render(Adafruit_SSD1306 *disp) override;
    void setMessage(const char *message);
    const char *getMessage();
    void setDuration(unsigned int duration);
    unsigned int getDuration();
    void show();
    void hide();

private:
    const char *message;
    unsigned int duration;
    bool visible = true;
};

#endif