#include "display/DisplayManager.h"

#include "display/components/Animation.h"
#include "display/components/Menu.h"
#include "display/components/Load.h"
#include "display/components/Page.h"

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
    {80, "Menu styles"},
    {70, "Page styles"},
    {60, "Load styles"}};

std::map<int, String> optionsAnimations = {
    {1, "Return to Main menu"},
    {91, "Reveal from center"},
    {92, "Slide from left"},
    {93, "Slide from right"},
    {94, "Rise and fall"},
    {95, "Fall and wrap"},
    {96, "Boot progress"},
    {97, "Fall block"},
    {98, "Fall in Sequence"},
};

std::map<int, String> optionsMenuStyles = {
    {1, "Return to Main menu"},
    {81, "List w/ cursor"},
    {82, "List w/ highlight"},
    {83, "Vertical selector"},
    {84, "Horizontal selector"},
};

std::map<int, String> optionsPageStyles = {
    {1, "Return to Main menu"},
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

std::map<int, String> optionsLoadStyles = {
    {1, "Return to Main menu"},
    {61, "Progress bar"},
    {62, "Circle sweep"},
    {63, "Dot sequence"}};

std::map<int, String> optionsGeneric = {
    {1, "Return to Main menu"},
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
Menu *mainMenu = new Menu(1, CURSOR_LIST, optionsMain);
Menu *mainAnimation = new Menu(90, CURSOR_LIST, optionsAnimations);
Menu *mainMenus = new Menu(80, CURSOR_LIST, optionsMenuStyles);
Menu *mainPages = new Menu(70, CURSOR_LIST, optionsPageStyles);
Menu *mainLoads = new Menu(60, CURSOR_LIST, optionsLoadStyles);

Animation *intro1 = new Animation(91, REVEAL_FROM_CENTER, 90, "Easy SSD1306");
Animation *intro2 = new Animation(92, SLIDE_FROM_LEFT, 90, "Easy SSD1306");
Animation *intro3 = new Animation(93, SLIDE_FROM_RIGHT, 90, "Easy SSD1306");
Animation *intro4 = new Animation(94, RISE_AND_FALL, 90, "Easy SSD1306");
Animation *intro5 = new Animation(95, FALL_AND_WRAP, 90, "Easy SSD1306");
Animation *intro6 = new Animation(96, BOOT_PROGRESS, 90, "Easy SSD1306");
Animation *intro7 = new Animation(97, FALL_BLOCK, 90, "Easy SSD1306");
Animation *intro8 = new Animation(98, FALL_IN_SEQUENCE, 90, "Easy SSD1306");

Menu *menu1 = new Menu(81, CURSOR_LIST, optionsGeneric);
Menu *menu2 = new Menu(82, HIGHLIGHT_LIST, optionsGeneric);
Menu *menu3 = new Menu(83, VERTICAL_SELECTOR, optionsGeneric);
Menu *menu4 = new Menu(84, HORIZONTAL_SELECTOR, optionsGeneric);

Load *load1 = new Load(61, PROGRESS_BAR, progressBarFunction);
Load *load2 = new Load(62, CIRCLE_SWEEP, circleSweepFunction);
Load *load3 = new Load(63, DOT_SEQUENCE, dotSequenceFunction);

Page *page1 = new Page(71, BORDERLESS_LEFT, 1, loremIpsum);
Page *page2 = new Page(72, BORDERLESS_CENTER, 1, loremIpsum);
Page *page3 = new Page(73, BORDERLESS_RIGHT, 1, loremIpsum);
Page *page4 = new Page(74, SOLID_BORDER_LEFT, 1, loremIpsum);
Page *page5 = new Page(75, SOLID_BORDER_CENTER, 1, loremIpsum);
Page *page6 = new Page(76, SOLID_BORDER_RIGHT, 1, loremIpsum);
Page *page7 = new Page(77, ROUNDED_BORDER_LEFT, 1, loremIpsum);
Page *page8 = new Page(78, ROUNDED_BORDER_CENTER, 1, loremIpsum);
Page *page9 = new Page(79, ROUNDED_BORDER_RIGHT, 1, loremIpsum);

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
  dsp.addComponent(mainMenu);
  dsp.addComponent(mainAnimation);
  dsp.addComponent(mainMenus);
  dsp.addComponent(mainPages);
  dsp.addComponent(mainLoads);

  dsp.addComponent(intro1);
  dsp.addComponent(intro2);
  dsp.addComponent(intro3);
  dsp.addComponent(intro4);
  dsp.addComponent(intro5);
  dsp.addComponent(intro6);
  dsp.addComponent(intro7);
  dsp.addComponent(intro8);

  dsp.addComponent(menu1);
  dsp.addComponent(menu2);
  dsp.addComponent(menu3);
  dsp.addComponent(menu4);

  dsp.addComponent(load1);
  dsp.addComponent(load2);
  dsp.addComponent(load3);

  dsp.addComponent(page1);
  dsp.addComponent(page2);
  dsp.addComponent(page3);
  dsp.addComponent(page4);
  dsp.addComponent(page5);
  dsp.addComponent(page6);
  dsp.addComponent(page7);
  dsp.addComponent(page8);
  dsp.addComponent(page9);
}

void loop()
{
  dsp.render();
}
