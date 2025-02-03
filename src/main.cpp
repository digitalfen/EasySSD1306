#include "display/DisplayManager.h"

#include "display/components/Animation.h"
#include "display/components/Navigation.h"
#include "display/components/Event.h"
#include "display/components/View.h"

#define BUTTON_UP 4
#define BUTTON_DOWN 5

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SSD1306_I2C_ADDRESS 0x3C
#define SSD1306_WHITE 1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

DisplayManager dsp;

std::map<int, String> optionsMain = {
    {90, "Animations styles"},
    {80, "Navigation styles"},
    {70, "View styles"},
    {60, "Event styles"}};

std::map<int, String> optionsAnimations = {
    {1, "Return to Main Navigation"},
    {91, "Reveal from center"},
    {92, "Slide from left"},
    {93, "Slide from right"},
    {94, "Rise and fall"},
    {95, "Fall and wrap"},
    {96, "Boot progress"},
    {97, "Fall block"},
    {98, "Fall in Sequence"},
};

std::map<int, String> optionsNavigationStyles = {
    {1, "Return to Main Navigation"},
    {81, "List w/ cursor"},
    {82, "List w/ highlight"},
    {83, "Vertical selector"},
    {84, "Horizontal selector"},
};

std::map<int, String> optionsViewStyles = {
    {1, "Return to Main Navigation"},
    {71, "Borderless, left"},
    {72, "Borderless, center"},
    {73, "Borderless, right"},
    {74, "Solid border, left"},
    {75, "Solid border, center"},
    {76, "Solid border, right"},
    {77, "Rounded border, left"},
    {78, "Rounded border, center"},
    {79, "Rounded border, right"},
};

std::map<int, String> optionsEventStyles = {
    {1, "Return to Main Navigation"},
    {61, "Progress bar"},
    {62, "Circle sweep"},
    {63, "Dot sequence"}};

std::map<int, String> optionsGeneric = {
    {1, "Return to Main Navigation"},
    {80, "Return to Styles"},
    {91, "Lorem ipsum"},
    {92, "Lorem ipsum"},
    {93, "Lorem ipsum"},
    {94, "Lorem ipsum"},
    {95, "Lorem ipsum"},
    {96, "Lorem ipsum"},
    {97, "Lorem ipsum"},
    {98, "Lorem ipsum"},
    {99, "Lorem ipsum"},
};

unsigned int progressBarFunction()
{
  Serial.println("progressBarFunction");
  return 60;
};

unsigned int circleSweepFunction()
{
  Serial.println("circleSweepFunction");
  return 60;
};

unsigned int dotSequenceFunction()
{
  Serial.println("dotSequenceFunction");
  return 60;
};

std::vector<String> loremIpsum = {
    "LOREM IPSUM",
    " ",
    "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur ut dui vel enim cursus vestibulum.",
    "Sed pretium mi sit amet turpis facilisis, a condimentum libero venenatis. Aliquam erat volutpat.",
    "Fusce vel metus et nunc tincidunt consectetur. Integer sit amet purus metus.",
    "Mauris efficitur mi et mi tincidunt, nec blandit nunc hendrerit. Suspendisse nec ex eget magna sollicitudin lacinia.",
    "Aenean vel efficitur elit. Nulla facilisi. Donec in libero in justo pretium vestibulum.",
    "Cras volutpat tristique metus vel sodales.",
    "Quisque facilisis laoreet malesuada. Ut gravida vitae odio vel fringilla.",
    "Vivamus at justo arcu. Nulla posuere sapien vel leo faucibus, in vulputate lectus iaculis.",
    "Sed convallis metus in nisi luctus, ac efficitur erat vulputate.",
    "Fusce vehicula purus at nulla facilisis, sed luctus leo cursus.",
    "Phasellus nec ipsum mollis, egestas odio non, pharetra magna.",
    "Etiam lacinia, sapien non auctor suscipit, tortor nisi viverra neque, ac posuere tortor magna vitae risus."};

Animation *mainIntro = new Animation(0, REVEAL_FROM_CENTER, 1, "Easy SSD1306");
Navigation *mainNavigation = new Navigation(1, CURSOR_LIST, optionsMain);
Navigation *mainAnimation = new Navigation(90, CURSOR_LIST, optionsAnimations);
Navigation *mainNavigations = new Navigation(80, CURSOR_LIST, optionsNavigationStyles);
Navigation *mainViews = new Navigation(70, CURSOR_LIST, optionsViewStyles);
Navigation *mainEvents = new Navigation(60, CURSOR_LIST, optionsEventStyles);

Animation *intro1 = new Animation(91, REVEAL_FROM_CENTER, 90, "Easy SSD1306");
Animation *intro2 = new Animation(92, SLIDE_FROM_LEFT, 90, "Easy SSD1306");
Animation *intro3 = new Animation(93, SLIDE_FROM_RIGHT, 90, "Easy SSD1306");
Animation *intro4 = new Animation(94, RISE_AND_FALL, 90, "Easy SSD1306");
Animation *intro5 = new Animation(95, FALL_AND_WRAP, 90, "Easy SSD1306");
Animation *intro6 = new Animation(96, BOOT_PROGRESS, 90, "Easy SSD1306");
Animation *intro7 = new Animation(97, FALL_BLOCK, 90, "Easy SSD1306");
Animation *intro8 = new Animation(98, FALL_IN_SEQUENCE, 90, "Easy SSD1306");

Navigation *Navigation1 = new Navigation(81, CURSOR_LIST, optionsGeneric);
Navigation *Navigation2 = new Navigation(82, HIGHLIGHT_LIST, optionsGeneric);
Navigation *Navigation3 = new Navigation(83, VERTICAL_SELECTOR, optionsGeneric);
Navigation *Navigation4 = new Navigation(84, HORIZONTAL_SELECTOR, optionsGeneric);

Event *Event1 = new Event(61, PROGRESS_BAR, progressBarFunction);
Event *Event2 = new Event(62, CIRCLE_SWEEP, circleSweepFunction);
Event *Event3 = new Event(63, DOT_SEQUENCE, dotSequenceFunction);

View *View1 = new View(71, BORDERLESS_LEFT, 1, loremIpsum);
View *View2 = new View(72, BORDERLESS_CENTER, 1, loremIpsum);
View *View3 = new View(73, BORDERLESS_RIGHT, 1, loremIpsum);
View *View4 = new View(74, SOLID_BORDER_LEFT, 1, loremIpsum);
View *View5 = new View(75, SOLID_BORDER_CENTER, 1, loremIpsum);
View *View6 = new View(76, SOLID_BORDER_RIGHT, 1, loremIpsum);
View *View7 = new View(77, ROUNDED_BORDER_LEFT, 1, loremIpsum);
View *View8 = new View(78, ROUNDED_BORDER_CENTER, 1, loremIpsum);
View *View9 = new View(79, ROUNDED_BORDER_RIGHT, 1, loremIpsum);

void setup()
{
  Serial.begin(115200);

  if (!display.begin(0x2, 0x3C))
  {
    Serial.println(F("Falha ao inicializar o display SSD1306!"));
    for (;;)
      ;
  }

  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);

  dsp.setDisplay(&display);
  dsp.setButtons(BUTTON_UP, BUTTON_DOWN);

  dsp.addComponent(mainIntro);
  dsp.addComponent(mainNavigation);
  dsp.addComponent(mainAnimation);
  dsp.addComponent(mainNavigations);
  dsp.addComponent(mainViews);
  dsp.addComponent(mainEvents);

  dsp.addComponent(intro1);
  dsp.addComponent(intro2);
  dsp.addComponent(intro3);
  dsp.addComponent(intro4);
  dsp.addComponent(intro5);
  dsp.addComponent(intro6);
  dsp.addComponent(intro7);
  dsp.addComponent(intro8);

  dsp.addComponent(Navigation1);
  dsp.addComponent(Navigation2);
  dsp.addComponent(Navigation3);
  dsp.addComponent(Navigation4);

  dsp.addComponent(Event1);
  dsp.addComponent(Event2);
  dsp.addComponent(Event3);

  dsp.addComponent(View1);
  dsp.addComponent(View2);
  dsp.addComponent(View3);
  dsp.addComponent(View4);
  dsp.addComponent(View5);
  dsp.addComponent(View6);
  dsp.addComponent(View7);
  dsp.addComponent(View8);
  dsp.addComponent(View9);
}

void loop()
{
  dsp.render();
}
