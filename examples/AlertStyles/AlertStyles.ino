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
Alert* alerts[6];
const char* alertMessage = "Alerta!";

// Ícone de exemplo (8x8 pixels)
const uint8_t warningIcon[] = {
  0x18, 0x3C, 0x3C, 0x18, 0x18, 0x00, 0x18, 0x18
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
  
  // Criação dos Alerts com diferentes estilos
  alerts[0] = new Alert(alertMessage, ALERT_STYLE_SIMPLE);
  alerts[1] = new Alert(alertMessage, ALERT_STYLE_BOXED);
  alerts[2] = new Alert(alertMessage, ALERT_STYLE_ROUNDED);
  alerts[3] = new Alert(alertMessage, ALERT_STYLE_ICON);
  alerts[4] = new Alert(alertMessage, ALERT_STYLE_BLINK);
  alerts[5] = new Alert(alertMessage, ALERT_STYLE_PROGRESS);
  
  // Configuração dos Alerts
  for(int i = 0; i < 6; i++) {
    alerts[i]->setAutoAdapt(true);
    manager.addComponent(alerts[i]);
  }
  
  // Configurações específicas
  alerts[3]->setIcon(warningIcon);
  alerts[4]->setBlinkInterval(500);
  alerts[5]->setProgress(50);
  
  // Posicionamento dos Alerts
  int y = 0;
  for(int i = 0; i < 6; i++) {
    alerts[i]->setPosition(0, y);
    y += 10;
  }
}

void loop() {
  // Atualização do display
  manager.update();
  delay(1000);
  
  // Atualização do progresso
  static int progress = 0;
  progress = (progress + 10) % 110;
  alerts[5]->setProgress(progress);
} 