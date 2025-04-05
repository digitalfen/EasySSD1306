#include <EasySSD1306.h>

// Definições de pinos para botões
#define BTN_ROTATION 2   // Botão para alternar rotação
#define BTN_ACTION   3   // Botão para ação secundária

// Criar instância do display
DisplayManager display(RESOLUTION_128x64);

// Componentes de interface
TextView* txtTitle;
TextView* txtOrientation;
TextView* txtInstrucao;
ImageView* imgLogo;

// Imagem de teste (seta apontando para cima)
const uint8_t arrowImg[] PROGMEM = {
  0x00, 0x80, 0x00, 0x00,
  0x00, 0xC0, 0x00, 0x00,
  0x00, 0xE0, 0x00, 0x00,
  0x00, 0xF0, 0x00, 0x00,
  0x00, 0xF8, 0x00, 0x00,
  0x00, 0xFC, 0x00, 0x00,
  0x00, 0xFE, 0x00, 0x00,
  0x00, 0xFF, 0x00, 0x00,
  0x80, 0xFF, 0x00, 0x00,
  0xC0, 0xFF, 0x00, 0x00,
  0xE0, 0xFF, 0x00, 0x00,
  0xF0, 0xFF, 0x00, 0x00,
  0xF8, 0xFF, 0x00, 0x00,
  0xFC, 0xFF, 0x00, 0x00,
  0x7F, 0xFF, 0x7F, 0x00,
  0x3E, 0xFF, 0x3E, 0x00,
  0x1C, 0xFF, 0x1C, 0x00,
  0x08, 0xFF, 0x08, 0x00,
  0x00, 0x7E, 0x00, 0x00,
  0x00, 0x3C, 0x00, 0x00,
  0x00, 0x18, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00
};

// Variáveis para controle de rotação
uint8_t currentRotation = 0;
char rotationText[20];

void setup() {
  Serial.begin(115200);
  Serial.println("Exemplo de Rotação em Tempo Real");
  
  // Configurar pinos como entrada com pull-up
  pinMode(BTN_ROTATION, INPUT_PULLUP);
  pinMode(BTN_ACTION, INPUT_PULLUP);
  
  // Inicializar o display
  if (!display.begin()) {
    Serial.println("Falha ao inicializar o display SSD1306!");
    while (1);
  }
  
  // Configurar os botões no display
  display.setButtonPins(BTN_ROTATION, BTN_ACTION);

  // Criar e configurar componentes
  txtTitle = new TextView("Rotacao em Tempo Real");
  txtTitle->setPosition(0, 0);
  
  sprintf(rotationText, "Rotacao: %d graus", currentRotation * 90);
  txtOrientation = new TextView(rotationText);
  txtOrientation->setPosition(0, 12);
  
  txtInstrucao = new TextView("Pressione BTN1 p/ girar");
  txtInstrucao->setPosition(0, 24);
  
  imgLogo = new ImageView(arrowImg, 32, 24);
  imgLogo->setPosition(48, 32); // Centro da tela
  
  // Adicionar componentes ao display
  display.addComponent(txtTitle);
  display.addComponent(txtOrientation);
  display.addComponent(txtInstrucao);
  display.addComponent(imgLogo);
  
  // Desenho inicial
  display.update();
}

void loop() {
  // Verifica se o botão de rotação foi pressionado
  if (display.wasButton1Pressed()) {
    // Incrementa a rotação (0->1->2->3->0)
    currentRotation = (currentRotation + 1) % 4;
    
    // Atualiza o texto de orientação
    sprintf(rotationText, "Rotacao: %d graus", currentRotation * 90);
    txtOrientation->setText(rotationText);
    
    // Aplica a rotação diretamente ao display
    display.setDisplayRotation(currentRotation);
    
    Serial.print("Rotação alterada para: ");
    Serial.print(currentRotation * 90);
    Serial.println(" graus");
  }
  
  // Verifica se o botão de ação foi pressionado
  if (display.wasButton2Pressed()) {
    Serial.println("Botão de ação pressionado");
    // Pode adicionar outras funcionalidades aqui
  }
  
  // Atualiza o display
  display.update();
  
  // Pequeno delay para evitar debounce
  delay(50);
} 