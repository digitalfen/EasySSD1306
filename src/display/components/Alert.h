#ifndef Alert_h
#define Alert_h

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <vector>
#include <string>

#include "display/IDisplayComponent.h"
#include "display/DisplayManager.h"

enum AlertPresets
{
    ALERT_DEFAULT,
    ALERT_WITH_BORDERS
};

class Alert : public IDisplayComponent
{
public:
    Alert(unsigned int id, AlertPresets preset, unsigned int next, const char *message)
        : IDisplayComponent(id), message(message), next(next), preset(preset) {}

    unsigned int render(Adafruit_SSD1306 *display) override;

    void execute(std::function<unsigned int()> execute);
    void nextComponent(unsigned int nextComponent);

private:
    const char *message;
    AlertPresets preset;
    unsigned int next;
    std::function<unsigned int()> exec;

    unsigned int preset1(Adafruit_SSD1306 *display);
    unsigned int preset2(Adafruit_SSD1306 *display);
    void renderOkButton(Adafruit_SSD1306 *display);
};

#endif