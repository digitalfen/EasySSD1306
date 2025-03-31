#include "display/components/ImageAnimation.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

unsigned int ImageAnimation::render(Adafruit_SSD1306 *display)
{

    if (exec)
    {
        next = exec();
    }

    display->clearDisplay();

    switch (preset)
    {
    case IMG_ANIM_SLIDE_FROM_LEFT:
        slideFromLeft(display);
        break;
    case IMG_ANIM_SLIDE_FROM_RIGHT:
        slideFromRight(display);
        break;
    case IMG_ANIM_SLIDE_FROM_TOP:
        slideFromTop(display);
        break;
    case IMG_ANIM_SLIDE_FROM_BOTTOM:
        slideFromBottom(display);
        break;
    case IMG_ANIM_PIXEL_BY_PIXEL:
        pixelByPixel(display);
        break;
    case IMG_ANIM_DRAW_LINES:
        drawLines(display);
        break;
    case IMG_ANIM_FADE_IN_FADE_OUT:
        fadeInFadeOut(display);
        break;
    default:
        display->clearDisplay();
        display->setTextSize(1);
        display->setCursor(0, SCREEN_HEIGHT / 2 - 4);
        display->print("Unknown ImageAnimation preset.");
        display->display();
        delay(3000);
        return 0;
    }

    display->display();

    return next;
}

void ImageAnimation::execute(std::function<unsigned int()> execute)
{
    this->exec = execute;
}

void ImageAnimation::nextComponent(unsigned int nextComponent)
{
    this->next = nextComponent;
}

void ImageAnimation::slideFromLeft(Adafruit_SSD1306 *display)
{
    int startX = -imageWidth;
    int startY = (SCREEN_HEIGHT - imageHeight) / 2;

    while (startX < (SCREEN_WIDTH - imageWidth) / 2)
    {
        display->clearDisplay();
        display->drawBitmap(startX, startY, imageData, imageWidth, imageHeight, SSD1306_WHITE);
        display->display();
        startX += 2;
        delay(20);
    }
}

void ImageAnimation::slideFromRight(Adafruit_SSD1306 *display)
{
    int startX = SCREEN_WIDTH;
    int startY = (SCREEN_HEIGHT - imageHeight) / 2;

    while (startX > (SCREEN_WIDTH - imageWidth) / 2)
    {
        display->clearDisplay();
        display->drawBitmap(startX, startY, imageData, imageWidth, imageHeight, SSD1306_WHITE);
        display->display();
        startX -= 2;
        delay(20);
    }
    delay(3000);
}

void ImageAnimation::slideFromTop(Adafruit_SSD1306 *display)
{
    int startX = (SCREEN_WIDTH - imageWidth) / 2;
    int startY = -imageHeight;

    while (startY < (SCREEN_HEIGHT - imageHeight) / 2)
    {
        display->clearDisplay();
        display->drawBitmap(startX, startY, imageData, imageWidth, imageHeight, SSD1306_WHITE);
        display->display();
        startY += 2;
        delay(20);
    }
    delay(3000);
}

void ImageAnimation::slideFromBottom(Adafruit_SSD1306 *display)
{
    int startX = (SCREEN_WIDTH - imageWidth) / 2;
    int startY = SCREEN_HEIGHT;

    while (startY > (SCREEN_HEIGHT - imageHeight) / 2)
    {
        display->clearDisplay();
        display->drawBitmap(startX, startY, imageData, imageWidth, imageHeight, SSD1306_WHITE);
        display->display();
        startY -= 2;
        delay(20);
    }
    delay(3000);
}

void ImageAnimation::pixelByPixel(Adafruit_SSD1306 *display)
{
    int startX = (SCREEN_WIDTH - imageWidth) / 2;
    int startY = (SCREEN_HEIGHT - imageHeight) / 2;

    for (int y = 0; y < imageHeight; y++)
    {
        for (int x = 0; x < imageWidth; x++)
        {
            uint8_t pixel = pgm_read_byte(&imageData[(y * imageWidth + x) / 8]);
            if (pixel & (1 << (x % 8)))
            {
                display->drawPixel(startX + x, startY + y, SSD1306_WHITE);
            }
            display->display();
            delay(1);
        }
    }
    delay(3000);
}

void ImageAnimation::drawLines(Adafruit_SSD1306 *display)
{
    int startX = (SCREEN_WIDTH - imageWidth) / 2;
    int startY = (SCREEN_HEIGHT - imageHeight) / 2;

    for (int y = 0; y < imageHeight; y++)
    {
        for (int x = 0; x < imageWidth; x++)
        {
            uint8_t pixel = pgm_read_byte(&imageData[(y * imageWidth + x) / 8]);
            if (pixel & (1 << (x % 8)))
            {
                display->drawPixel(startX + x, startY + y, SSD1306_WHITE);
            }
        }
        display->display();
        delay(50);
    }
    delay(3000);
}

void ImageAnimation::fadeInFadeOut(Adafruit_SSD1306 *display)
{
    int startX = (SCREEN_WIDTH - imageWidth) / 2;
    int startY = (SCREEN_HEIGHT - imageHeight) / 2;

    for (int alpha = 0; alpha <= 255; alpha += 5)
    {
        display->clearDisplay();
        for (int y = 0; y < imageHeight; y++)
        {
            for (int x = 0; x < imageWidth; x++)
            {
                uint8_t pixel = pgm_read_byte(&imageData[(y * imageWidth + x) / 8]);
                if (pixel & (1 << (x % 8)))
                {
                    display->drawPixel(startX + x, startY + y, SSD1306_WHITE);
                }
            }
        }
        display->dim(true);
        display->display();
        delay(20);
    }
    display->dim(false);

    delay(1000);

    for (int alpha = 255; alpha >= 0; alpha -= 5)
    {
        display->clearDisplay();
        for (int y = 0; y < imageHeight; y++)
        {
            for (int x = 0; x < imageWidth; x++)
            {
                uint8_t pixel = pgm_read_byte(&imageData[(y * imageWidth + x) / 8]);
                if (pixel & (1 << (x % 8)))
                {
                    display->drawPixel(startX + x, startY + y, SSD1306_WHITE);
                }
            }
        }
        display->dim(true);
        display->display();
        delay(20);
    }
    display->dim(false);
}