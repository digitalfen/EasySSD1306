#include "display/DisplayManager.h"

#include "display/components/TextAnimation.h"
#include "display/components/Navigation.h"
#include "display/components/LoadAnimation.h"
#include "display/components/TextView.h"
#include "display/components/Prompt.h"
#include "display/components/Alert.h"
#include "display/components/ImageView.h"

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
    {70, "TextView styles"},
    {60, "LoadAnimation styles"},
    {50, "Prompt styles"},
    {40, "Alert styles"},
    {30, "ImageView styles"}};

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

std::map<int, String> optionsTextViewStyles = {
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

std::map<int, String> optionsPromptStyles = {
    {1, "Return to Main Navigation"},
    {51, "Simple prompt"},
    {52, "Prompt with bordes"}};

std::map<int, String> optionsAlertStyles = {
    {1, "Return to Main Navigation"},
    {41, "Simple alert"},
    {42, "Alert with bordes"}};

std::map<int, String> optionsImgViewStyles = {
    {1, "Return to Main Navigation"},
    {31, "32x32"},
    {32, "64x64"}};

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

const uint8_t image32x32[] = {
    0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
    0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
    0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
    0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
    0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
    0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
    0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
    0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
    0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
    0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
    0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
    0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
    0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
    0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
    0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
    0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF};

const uint8_t image64x64[] = {
    0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
    0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
    0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
    0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
    0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
    0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
    0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
    0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
    0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
    0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
    0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
    0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
    0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
    0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
    0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
    0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
    0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
    0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
    0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
    0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
    0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
    0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
    0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
    0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
    0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
    0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
    0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
    0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
    0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
    0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
    0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
    0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF};

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
Navigation *mainTextViews;
Navigation *mainLoadAnimations;
Navigation *mainPrompts;
Navigation *mainAlert;
Navigation *mainImgView;

Navigation *navigation1;
Navigation *navigation2;
Navigation *navigation3;
Navigation *navigation4;

LoadAnimation *loadAnimation1;
LoadAnimation *loadAnimation2;
LoadAnimation *loadAnimation3;

TextView *textView1;
TextView *textView2;
TextView *textView3;
TextView *textView4;
TextView *textView5;
TextView *textView6;
TextView *textView7;
TextView *textView8;
TextView *textView9;

Prompt *prompt1;
Prompt *prompt2;

Alert *alert1;
Alert *alert2;
Alert *alert3;

ImageView *imageView1;
ImageView *imageView2;

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

  mainIntro = new TextAnimation(0, TXT_ANIM_REVEAL_FROM_CENTER, "Easy SSD1306");
  mainIntro->nextComponent(1);
  intro1 = new TextAnimation(91, TXT_ANIM_REVEAL_FROM_CENTER, "Easy SSD1306");
  intro1->nextComponent(90);
  intro2 = new TextAnimation(92, TXT_ANIM_SLIDE_FROM_LEFT, "Easy SSD1306");
  intro2->nextComponent(90);
  intro3 = new TextAnimation(93, TXT_ANIM_SLIDE_FROM_RIGHT, "Easy SSD1306");
  intro3->nextComponent(90);
  intro4 = new TextAnimation(94, TXT_ANIM_RISE_AND_FALL, "Easy SSD1306");
  intro4->nextComponent(90);
  intro5 = new TextAnimation(95, TXT_ANIM_FALL_AND_WRAP, "Easy SSD1306");
  intro5->nextComponent(90);
  intro7 = new TextAnimation(97, TXT_ANIM_FALL_BLOCK, "Easy SSD1306");
  intro7->nextComponent(90);
  intro8 = new TextAnimation(98, TXT_ANIM_FALL_IN_SEQUENCE, "Easy SSD1306");
  intro8->nextComponent(90);

  mainNavigation = new Navigation(1, NAV_CURSOR_LIST, optionsMain);
  mainTextAnimation = new Navigation(90, NAV_CURSOR_LIST, optionsTextAnimations);
  mainNavigations = new Navigation(80, NAV_CURSOR_LIST, optionsNavigationStyles);
  mainTextViews = new Navigation(70, NAV_CURSOR_LIST, optionsTextViewStyles);
  mainLoadAnimations = new Navigation(60, NAV_CURSOR_LIST, optionsLoadAnimationStyles);
  mainPrompts = new Navigation(50, NAV_CURSOR_LIST, optionsPromptStyles);
  mainAlert = new Navigation(40, NAV_CURSOR_LIST, optionsAlertStyles);
  mainImgView = new Navigation(30, NAV_CURSOR_LIST, optionsImgViewStyles);

  navigation1 = new Navigation(81, NAV_CURSOR_LIST, optionsGeneric);
  navigation2 = new Navigation(82, NAV_HIGHLIGHT_LIST, optionsGeneric);
  navigation3 = new Navigation(83, NAV_VERTICAL_SELECTOR, optionsGeneric);
  navigation4 = new Navigation(84, NAV_HORIZONTAL_SELECTOR, optionsGeneric);

  loadAnimation1 = new LoadAnimation(61, LOAD_ANIM_PROGRESS_BAR);
  loadAnimation1->execute(progressBarFunction);
  loadAnimation2 = new LoadAnimation(62, LOAD_ANIM_CIRCLE_SWEEP);
  loadAnimation2->execute(circleSweepFunction);
  loadAnimation3 = new LoadAnimation(63, LOAD_ANIM_DOT_SEQUENCE);
  loadAnimation3->execute(dotSequenceFunction);

  textView1 = new TextView(71, TXT_VIEW_BORDERLESS_LEFT, loremIpsum);
  textView1->nextComponent(1);
  textView2 = new TextView(72, TXT_VIEW_BORDERLESS_CENTER, loremIpsum);
  textView2->nextComponent(1);
  textView3 = new TextView(73, TXT_VIEW_BORDERLESS_RIGHT, loremIpsum);
  textView3->nextComponent(1);
  textView4 = new TextView(74, TXT_VIEW_SOLID_BORDER_LEFT, loremIpsum);
  textView4->nextComponent(1);
  textView5 = new TextView(75, TXT_VIEW_SOLID_BORDER_CENTER, loremIpsum);
  textView5->nextComponent(1);
  textView6 = new TextView(76, TXT_VIEW_SOLID_BORDER_RIGHT, loremIpsum);
  textView6->nextComponent(1);
  textView7 = new TextView(77, TXT_VIEW_ROUNDED_BORDER_LEFT, loremIpsum);
  textView7->nextComponent(1);
  textView8 = new TextView(78, TXT_VIEW_ROUNDED_BORDER_CENTER, loremIpsum);
  textView8->nextComponent(1);
  textView9 = new TextView(79, TXT_VIEW_ROUNDED_BORDER_RIGHT, loremIpsum);
  textView9->nextComponent(1);

  prompt1 = new Prompt(51, PROMPT_DEFAULT, 0, "Reset?");
  prompt2 = new Prompt(52, PROMPT_WITH_BORDERS, 0, "Reset?");

  alert1 = new Alert(41, ALERT_DEFAULT, 0, "Warning!");
  alert2 = new Alert(42, ALERT_WITH_BORDERS, 0, "Warning!");

  imageView1 = new ImageView(31, IMG_VIEW_DEFAULT, image32x32, 32, 32);
  imageView1->nextComponent(1);

  imageView2 = new ImageView(32, IMG_VIEW_DEFAULT, image64x64, 64, 64);
  imageView2->nextComponent(1);

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
  dsp.addComponent(mainTextViews);
  dsp.addComponent(mainLoadAnimations);
  dsp.addComponent(mainPrompts);
  dsp.addComponent(mainAlert);
  dsp.addComponent(mainImgView);

  dsp.addComponent(navigation1);
  dsp.addComponent(navigation2);
  dsp.addComponent(navigation3);
  dsp.addComponent(navigation4);

  dsp.addComponent(loadAnimation1);
  dsp.addComponent(loadAnimation2);
  dsp.addComponent(loadAnimation3);

  dsp.addComponent(textView1);
  dsp.addComponent(textView2);
  dsp.addComponent(textView3);
  dsp.addComponent(textView4);
  dsp.addComponent(textView5);
  dsp.addComponent(textView6);
  dsp.addComponent(textView7);
  dsp.addComponent(textView8);
  dsp.addComponent(textView9);

  dsp.addComponent(prompt1);
  dsp.addComponent(prompt2);

  dsp.addComponent(alert1);
  dsp.addComponent(alert2);

  dsp.addComponent(imageView1);
  dsp.addComponent(imageView2);
}

void loop()
{
  dsp.render();
}