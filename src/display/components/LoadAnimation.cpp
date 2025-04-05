#include "display/components/LoadAnimation.h"
#include "display/DisplayManager.h"

unsigned int LoadAnimation::render(Adafruit_SSD1306 *display)
{
    // Initialize start time if not set
    if (startTime == 0) {
        startTime = millis();
    }

    // Start execution if not already executing
    if (exec && !isExecuting) {
        isExecuting = true;
        next = exec();
    }

    // Run animation based on preset
    if (preset == LOAD_ANIM_PROGRESS_BAR)
    {
        presetLoadAnimation1(display);
    }
    else if (preset == LOAD_ANIM_CIRCLE_SWEEP)
    {
        presetLoadAnimation2(display);
    }
    else if (preset == LOAD_ANIM_DOT_SEQUENCE)
    {
        presetLoadAnimation3(display);
    }
    else
    {
        display->clearDisplay();
        display->setTextSize(1);
        display->setCursor(0, display->height() / 2 - 4);
        display->print("Unknown LoadAnimation preset.");
        display->display();
        delay(2000);
        return 0;
    }

    // Calculate elapsed time
    unsigned long elapsedTime = millis() - startTime;

    // Wait for minimum duration if needed
    if (elapsedTime < minDuration) {
        delay(minDuration - elapsedTime);
    }

    return next;
}

void LoadAnimation::execute(std::function<unsigned int()> execute)
{
    this->exec = execute;
    this->isExecuting = false;
    this->startTime = 0;
}

void LoadAnimation::nextComponent(unsigned int nextComponent)
{
    this->next = nextComponent;
}

void LoadAnimation::presetLoadAnimation1(Adafruit_SSD1306 *display)
{
    display->clearDisplay();
    for (int i = 0; i <= 100; i++)
    {
        display->fillRect(10, 30, i, 10, SSD1306_WHITE);
        display->display();
        delay(10);
    }
    display->clearDisplay();
    display->display();
}

void LoadAnimation::presetLoadAnimation2(Adafruit_SSD1306 *display)
{
    int x = display->width() / 2;
    int y = display->height() / 2;
    int radius = 10;
    display->clearDisplay();

    for (int angle = 0; angle < 360; angle += 30)
    {
        display->drawCircle(x + radius * cos(angle * PI / 180),
                          y + radius * sin(angle * PI / 180),
                          2, SSD1306_WHITE);
        display->display();
        delay(250);
        display->clearDisplay();
    }
}

void LoadAnimation::presetLoadAnimation3(Adafruit_SSD1306 *display)
{
    display->clearDisplay();
    int xStart = display->width() / 2 - 20;
    int y = display->height() / 2;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            int x = xStart + (j * 20);
            display->fillCircle(x, y, (i % 3 == j) ? 5 : 0, SSD1306_WHITE);
        }

        display->display();
        delay(300);
        display->clearDisplay();
    }

    display->display();
}

// Implementações de presetLoadAnimation2, presetLoadAnimation3, presetLoadAnimation4, presetLoadAnimation5
// Seguem a mesma lógica, mas podem variar o layout ou o comportamento dependendo do preset.
