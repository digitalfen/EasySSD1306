#include "display/DisplayManager.h"

#include "display/components/TextAnimation.h"
#include "display/components/Navigation.h"
#include "display/components/LoadAnimation.h"
#include "display/components/View.h"
#include "display/components/ActionPrompt.h"

#define BUTTON_UP 4
#define BUTTON_DOWN 5

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SSD1306_I2C_ADDRESS 0x3C
#define SSD1306_WHITE 1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

DisplayManager dsp;

std::map<int, String> optionsMain = {
    {90, "TextAnimations styles"},
    {80, "Navigation styles"},
    {70, "View styles"},
    {60, "LoadAnimation styles"},
    {50, "PromptAction styles"}};

std::map<int, String> optionsTextAnimations = {
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

std::map<int, String> optionsLoadAnimationStyles = {
    {1, "Return to Main Navigation"},
    {61, "Progress bar"},
    {62, "Circle sweep"},
    {63, "Dot sequence"}};

std::map<int, String> optionsActionPromptStyles = {
    {1, "Return to Main Navigation"},
    {51, "Simple prompt"},
    {52, "Prompt with bordes"},
    {53, "Prompt with icon"}};

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

TextAnimation *mainIntro;
TextAnimation *intro1;
TextAnimation *intro2;
TextAnimation *intro3;
TextAnimation *intro4;
TextAnimation *intro5;
TextAnimation *intro7;
TextAnimation *intro8;

Navigation *mainNavigation;
Navigation *mainTextAnimation;
Navigation *mainNavigations;
Navigation *mainViews;
Navigation *mainLoadAnimations;
Navigation *mainActionPrompts;

Navigation *navigation1;
Navigation *navigation2;
Navigation *navigation3;
Navigation *navigation4;

LoadAnimation *loadAnimation1;
LoadAnimation *loadAnimation2;
LoadAnimation *loadAnimation3;

View *view1;
View *view2;
View *view3;
View *view4;
View *view5;
View *view6;
View *view7;
View *view8;
View *view9;

ActionPrompt *actionPrompt1;
ActionPrompt *actionPrompt2;
ActionPrompt *actionPrompt3;

void setup()
{
  Serial.begin(115200);

  if (!display.begin(SSD1306_I2C_ADDRESS, SSD1306_I2C_ADDRESS))
  {
    Serial.println(F("Falha ao inicializar o display SSD1306!"));
    for (;;)
      ;
  }

  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);

  dsp.setDisplay(&display);
  dsp.setButtons(BUTTON_UP, BUTTON_DOWN);

  mainIntro = new TextAnimation(0, REVEAL_FROM_CENTER, "Easy SSD1306");
  mainIntro->nextComponent(1);
  intro1 = new TextAnimation(91, REVEAL_FROM_CENTER, "Easy SSD1306");
  intro1->nextComponent(90);
  intro2 = new TextAnimation(92, SLIDE_FROM_LEFT, "Easy SSD1306");
  intro2->nextComponent(90);
  intro3 = new TextAnimation(93, SLIDE_FROM_RIGHT, "Easy SSD1306");
  intro3->nextComponent(90);
  intro4 = new TextAnimation(94, RISE_AND_FALL, "Easy SSD1306");
  intro4->nextComponent(90);
  intro5 = new TextAnimation(95, FALL_AND_WRAP, "Easy SSD1306");
  intro5->nextComponent(90);
  intro7 = new TextAnimation(97, FALL_BLOCK, "Easy SSD1306");
  intro7->nextComponent(90);
  intro8 = new TextAnimation(98, FALL_IN_SEQUENCE, "Easy SSD1306");
  intro8->nextComponent(90);

  mainNavigation = new Navigation(1, CURSOR_LIST, optionsMain);
  mainTextAnimation = new Navigation(90, CURSOR_LIST, optionsTextAnimations);
  mainNavigations = new Navigation(80, CURSOR_LIST, optionsNavigationStyles);
  mainViews = new Navigation(70, CURSOR_LIST, optionsViewStyles);
  mainLoadAnimations = new Navigation(60, CURSOR_LIST, optionsLoadAnimationStyles);
  mainActionPrompts = new Navigation(50, CURSOR_LIST, optionsActionPromptStyles);

  navigation1 = new Navigation(81, CURSOR_LIST, optionsGeneric);
  navigation2 = new Navigation(82, HIGHLIGHT_LIST, optionsGeneric);
  navigation3 = new Navigation(83, VERTICAL_SELECTOR, optionsGeneric);
  navigation4 = new Navigation(84, HORIZONTAL_SELECTOR, optionsGeneric);

  loadAnimation1 = new LoadAnimation(61, PROGRESS_BAR);
  loadAnimation1->execute(progressBarFunction);
  loadAnimation2 = new LoadAnimation(62, CIRCLE_SWEEP);
  loadAnimation2->execute(circleSweepFunction);
  loadAnimation3 = new LoadAnimation(63, DOT_SEQUENCE);
  loadAnimation3->execute(dotSequenceFunction);

  view1 = new View(71, BORDERLESS_LEFT, loremIpsum);
  view1->nextComponent(1);
  view2 = new View(72, BORDERLESS_CENTER, loremIpsum);
  view2->nextComponent(1);
  view3 = new View(73, BORDERLESS_RIGHT, loremIpsum);
  view3->nextComponent(1);
  view4 = new View(74, SOLID_BORDER_LEFT, loremIpsum);
  view4->nextComponent(1);
  view5 = new View(75, SOLID_BORDER_CENTER, loremIpsum);
  view5->nextComponent(1);
  view6 = new View(76, SOLID_BORDER_RIGHT, loremIpsum);
  view6->nextComponent(1);
  view7 = new View(77, ROUNDED_BORDER_LEFT, loremIpsum);
  view7->nextComponent(1);
  view8 = new View(78, ROUNDED_BORDER_CENTER, loremIpsum);
  view8->nextComponent(1);
  view9 = new View(79, ROUNDED_BORDER_RIGHT, loremIpsum);
  view9->nextComponent(1);

  actionPrompt1 = new ActionPrompt(51, SIMPLE, 0, "Reset?");
  actionPrompt2 = new ActionPrompt(52, BORDER, 0, "Reset?");
  actionPrompt3 = new ActionPrompt(53, ICON, 0, "Reset?");

  // Adicionando componentes ao DisplayManager
  dsp.addComponent(mainIntro);
  dsp.addComponent(intro1);
  dsp.addComponent(intro2);
  dsp.addComponent(intro3);
  dsp.addComponent(intro4);
  dsp.addComponent(intro5);
  dsp.addComponent(intro7);
  dsp.addComponent(intro8);

  dsp.addComponent(mainNavigation);
  dsp.addComponent(mainTextAnimation);
  dsp.addComponent(mainNavigations);
  dsp.addComponent(mainViews);
  dsp.addComponent(mainLoadAnimations);
  dsp.addComponent(mainActionPrompts);

  dsp.addComponent(navigation1);
  dsp.addComponent(navigation2);
  dsp.addComponent(navigation3);
  dsp.addComponent(navigation4);

  dsp.addComponent(loadAnimation1);
  dsp.addComponent(loadAnimation2);
  dsp.addComponent(loadAnimation3);

  dsp.addComponent(view1);
  dsp.addComponent(view2);
  dsp.addComponent(view3);
  dsp.addComponent(view4);
  dsp.addComponent(view5);
  dsp.addComponent(view6);
  dsp.addComponent(view7);
  dsp.addComponent(view8);
  dsp.addComponent(view9);

  dsp.addComponent(actionPrompt1);
  dsp.addComponent(actionPrompt2);
  dsp.addComponent(actionPrompt3);
}

void loop()
{
  dsp.render();
}