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
TextView* textViews[12];
const char* sampleText = "EasySSD1306";

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
  
  // Criação dos TextViews com diferentes estilos
  textViews[0] = new TextView("Borda Esq", TXT_VIEW_BORDERLESS_LEFT);
  textViews[1] = new TextView("Borda Centro", TXT_VIEW_BORDERLESS_CENTER);
  textViews[2] = new TextView("Borda Dir", TXT_VIEW_BORDERLESS_RIGHT);
  
  textViews[3] = new TextView("Sólida Esq", TXT_VIEW_SOLID_BORDER_LEFT);
  textViews[4] = new TextView("Sólida Centro", TXT_VIEW_SOLID_BORDER_CENTER);
  textViews[5] = new TextView("Sólida Dir", TXT_VIEW_SOLID_BORDER_RIGHT);
  
  textViews[6] = new TextView("Arred Esq", TXT_VIEW_ROUNDED_BORDER_LEFT);
  textViews[7] = new TextView("Arred Centro", TXT_VIEW_ROUNDED_BORDER_CENTER);
  textViews[8] = new TextView("Arred Dir", TXT_VIEW_ROUNDED_BORDER_RIGHT);
  
  textViews[9] = new TextView("Invert Esq", TXT_VIEW_INVERTED_LEFT);
  textViews[10] = new TextView("Invert Centro", TXT_VIEW_INVERTED_CENTER);
  textViews[11] = new TextView("Invert Dir", TXT_VIEW_INVERTED_RIGHT);
  
  // Configuração dos TextViews
  for(int i = 0; i < 12; i++) {
    textViews[i]->setTextSize(1);
    textViews[i]->setAutoAdapt(true);
    manager.addComponent(textViews[i]);
  }
  
  // Posicionamento dos TextViews
  int y = 0;
  for(int i = 0; i < 12; i++) {
    textViews[i]->setPosition(0, y);
    y += 5;
  }
}

void loop() {
  // Atualização do display
  manager.update();
  delay(1000);
  
  // Alterna entre tamanhos de texto
  static int textSize = 1;
  textSize = (textSize % 3) + 1;
  
  for(int i = 0; i < 12; i++) {
    textViews[i]->setTextSize(textSize);
  }
} 