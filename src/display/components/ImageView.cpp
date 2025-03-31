#include "display/components/ImageView.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

unsigned int ImageView::render(Adafruit_SSD1306 *display)
{
    unsigned int nextView = 0;

    if (exec)
    {
        next = exec();
    }

    display->clearDisplay();

    if (preset == IMG_VIEW_DEFAULT)
    {
        nextView = preset1(display);
    }
    else
    {
        display->clearDisplay();
        display->setTextSize(1);
        display->setCursor(0, SCREEN_HEIGHT / 2 - 4);
        display->print("Unknown ImageView request.");
        display->display();
        delay(3000);
    }
    display->display();

    return next;
}

void ImageView::execute(std::function<unsigned int()> execute)
{
    this->exec = execute;
}

void ImageView::nextComponent(unsigned int nextComponent)
{
    this->next = nextComponent;
}

unsigned int ImageView::preset1(Adafruit_SSD1306 *display)
{
    int startX = (SCREEN_WIDTH - imageWidth) / 2;
    int startY = (SCREEN_HEIGHT - imageHeight) / 2;
    display->drawBitmap(startX, startY, imageData, imageWidth, imageHeight, SSD1306_WHITE);

    if (DisplayManager::confirmItem)
    {
        return next;
    }

    return id;
}