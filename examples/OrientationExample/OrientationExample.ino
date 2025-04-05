#include <EasySSD1306.h>

// Criar instância do display com diferentes configurações
DisplayManager display(RESOLUTION_128x64, ORIENTATION_NORMAL); // 128x64 em orientação normal

// Criar componentes para demonstração
TextView* titleText;
TextView* infoText;
ImageView* logo;
Navigation* menu;

// Definir alguns itens de menu
const char* menuItems[] = {
  "Item 1",
  "Item 2",
  "Item 3",
  "Mudar Orientacao",
  "Voltar"
};

// Definir uma imagem pequena para teste
const uint8_t logoImage[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00,
  0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
  0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00
};

void setup() {
  Serial.begin(115200);
  
  // Inicializar o display
  if (!display.begin()) {
    Serial.println("Falha ao inicializar o display SSD1306!");
    while (1);
  }
  
  // Configurar os botões
  display.setButtonPins(2, 3); // Pinos para os botões de navegação
  
  // Criar componentes
  titleText = new TextView("EasySSD1306 Demo");
  titleText->setPosition(0, 0);
  
  infoText = new TextView("Orientacao: Normal");
  infoText->setPosition(0, 12);
  
  logo = new ImageView(logoImage, 16, 16);
  logo->setPosition(100, 0);
  logo->setAutoCenter(true);
  
  menu = new Navigation(menuItems, 5);
  
  // Adicionar componentes ao display
  display.addComponent(titleText);
  display.addComponent(infoText);
  display.addComponent(logo);
  display.addComponent(menu);
}

// Variável para rastrear orientação atual
DisplayOrientation currentOrientation = ORIENTATION_NORMAL;

void loop() {
  // Verificar os botões
  if (display.wasButton1Pressed()) {
    menu->previous();
  }
  
  if (display.wasButton2Pressed()) {
    // Verificar se o item selecionado é "Mudar Orientacao"
    if (menu->getSelectedIndex() == 3) {
      // Mudar para a próxima orientação
      switch (currentOrientation) {
        case ORIENTATION_NORMAL:
          currentOrientation = ORIENTATION_RIGHT;
          infoText->setText("Orientacao: 90°");
          break;
        case ORIENTATION_RIGHT:
          currentOrientation = ORIENTATION_INVERTED;
          infoText->setText("Orientacao: 180°");
          break;
        case ORIENTATION_INVERTED:
          currentOrientation = ORIENTATION_LEFT;
          infoText->setText("Orientacao: 270°");
          break;
        case ORIENTATION_LEFT:
          currentOrientation = ORIENTATION_NORMAL;
          infoText->setText("Orientacao: Normal");
          break;
      }
      display.setOrientation(currentOrientation);
    } else {
      menu->next();
    }
  }
  
  // Atualizar o display
  display.update();
  
  delay(50);
} 