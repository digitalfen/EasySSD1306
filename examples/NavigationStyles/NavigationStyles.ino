#include <EasySSD1306.h>

// Configuração do display
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

// Instância do display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
DisplayManager manager(&display);

// Componentes
Navigation* navigations[6];
const char* menuItems[] = {
  "Item 1",
  "Item 2",
  "Item 3",
  "Item 4",
  "Item 5"
};
const int itemCount = 5;

void setup() {
  Serial.begin(115200);
  
  // Inicialização do display
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("Falha na inicialização do SSD1306"));
    for(;;);
  }
  
  // Configuração do display
  manager.setResolution(SCREEN_WIDTH, SCREEN_HEIGHT);
  manager.setOrientation(NORMAL);
  
  // Criação dos Navigations com diferentes estilos
  navigations[0] = new Navigation(menuItems, itemCount, NAV_STYLE_SIMPLE);
  navigations[1] = new Navigation(menuItems, itemCount, NAV_STYLE_BOXED);
  navigations[2] = new Navigation(menuItems, itemCount, NAV_STYLE_UNDERLINE);
  navigations[3] = new Navigation(menuItems, itemCount, NAV_STYLE_HIGHLIGHT);
  navigations[4] = new Navigation(menuItems, itemCount, NAV_STYLE_DOTS);
  navigations[5] = new Navigation(menuItems, itemCount, NAV_STYLE_NUMBERS);
  
  // Configuração dos Navigations
  for(int i = 0; i < 6; i++) {
    navigations[i]->setItemHeight(12);
    navigations[i]->setSpacing(4);
    navigations[i]->setAutoAdapt(true);
    manager.addComponent(navigations[i]);
  }
  
  // Posicionamento dos Navigations
  int x = 0;
  for(int i = 0; i < 6; i++) {
    navigations[i]->setPosition(x, 0);
    x += 21;
  }
}

void loop() {
  // Atualização do display
  manager.update();
  delay(1000);
  
  // Navegação automática
  static int selectedIndex = 0;
  selectedIndex = (selectedIndex + 1) % itemCount;
  
  for(int i = 0; i < 6; i++) {
    navigations[i]->setSelectedIndex(selectedIndex);
  }
} 