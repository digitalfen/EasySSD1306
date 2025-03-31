#ifndef IDISPLAYCOMPONENT_H
#define IDISPLAYCOMPONENT_H

class IDisplayComponent
{
public:
    explicit IDisplayComponent(unsigned int id) : id(id) {}

    virtual unsigned int render(Adafruit_SSD1306 *disp) = 0;

    virtual ~IDisplayComponent() {};

    unsigned int id;
};

#endif
