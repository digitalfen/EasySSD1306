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
ImageView* imageViews[6];

// Imagem de exemplo (16x16 pixels)
const uint8_t testImage[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

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
  
  // Criação dos ImageViews com diferentes estilos
  imageViews[0] = new ImageView(testImage, 16, 16, IMG_STYLE_NORMAL);
  imageViews[1] = new ImageView(testImage, 16, 16, IMG_STYLE_BORDERED);
  imageViews[2] = new ImageView(testImage, 16, 16, IMG_STYLE_ROUNDED);
  imageViews[3] = new ImageView(testImage, 16, 16, IMG_STYLE_INVERTED);
  imageViews[4] = new ImageView(testImage, 16, 16, IMG_STYLE_SHADOW);
  imageViews[5] = new ImageView(testImage, 16, 16, IMG_STYLE_FRAME);
  
  // Configuração dos ImageViews
  for(int i = 0; i < 6; i++) {
    imageViews[i]->setScale(2);
    imageViews[i]->setAutoAdapt(true);
    imageViews[i]->setAutoCenter(true);
    manager.addComponent(imageViews[i]);
  }
  
  // Configurações específicas
  imageViews[1]->setBorderColor(SSD1306_WHITE);
  imageViews[2]->setBorderColor(SSD1306_WHITE);
  imageViews[4]->setShadowOffset(3);
  imageViews[5]->setBorderColor(SSD1306_WHITE);
  
  // Posicionamento dos ImageViews
  int x = 0;
  for(int i = 0; i < 6; i++) {
    imageViews[i]->setPosition(x, 0);
    x += 32;
  }
}

void loop() {
  // Atualização do display
  manager.update();
  delay(1000);
  
  // Alterna entre escalas
  static float scale = 1.0;
  scale = (scale == 1.0) ? 2.0 : 1.0;
  
  for(int i = 0; i < 6; i++) {
    imageViews[i]->setScale(scale);
  }
} 