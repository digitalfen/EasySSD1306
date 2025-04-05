#include <EasySSD1306.h>
#include <Wire.h>
#include "utils/OrientationSensor.h"

// Definição de pinos
#define BTN_TOGGLE  2   // Botão para ativar/desativar rotação automática

// Criar instância do display
DisplayManager display(RESOLUTION_128x64);

// Criar o sensor de orientação
OrientationSensor* orientationSensor;

// Componentes de interface
TextView* txtTitle;
TextView* txtStatus;
TextView* txtOrientation;
TextView* txtInfo;
ImageView* imgLogo;

// Estado da rotação automática
bool autoRotationEnabled = true;
char statusText[30] = "Auto-rotacao: ATIVADA";
char orientationText[30] = "Rotacao: 0 graus";

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

// Função de callback para quando a orientação mudar
void onOrientationChanged(uint8_t rotation) {
  // Atualizar texto de orientação
  sprintf(orientationText, "Rotacao: %d graus", rotation * 90);
  txtOrientation->setText(orientationText);
  
  Serial.print("Orientação alterada para: ");
  Serial.print(rotation * 90);
  Serial.println(" graus");
}

void setup() {
  Serial.begin(115200);
  Serial.println("Auto-Rotação Aprimorada");
  
  // Configurar pino do botão
  pinMode(BTN_TOGGLE, INPUT_PULLUP);
  
  // Inicializar o display
  if (!display.begin()) {
    Serial.println("Falha ao inicializar o display SSD1306!");
    while (1);
  }
  
  // Configurar os botões no display
  display.setButtonPins(BTN_TOGGLE, -1);
  
  // Criar o sensor de orientação
  orientationSensor = new OrientationSensor(&display);
  
  // Configurar o sensor
  if (!orientationSensor->begin()) {
    Serial.println("Falha ao inicializar o sensor MPU6050!");
    // Continuar mesmo sem sensor
  }
  
  // Configurar o sensor
  orientationSensor->setSensitivity(3.0f);            // Menor suavização para resposta mais rápida
  orientationSensor->setRequiredStability(2);         // Requer 2 leituras consistentes antes de mudar
  orientationSensor->setOrientationChangedCallback(onOrientationChanged);
  
  // Criar e configurar componentes
  txtTitle = new TextView("Auto-Rotacao");
  txtTitle->setPosition(0, 0);
  
  txtStatus = new TextView(statusText);
  txtStatus->setPosition(0, 12);
  
  txtOrientation = new TextView(orientationText);
  txtOrientation->setPosition(0, 24);
  
  txtInfo = new TextView("BTN1: Ativar/Desativar");
  txtInfo->setPosition(0, 36);
  
  imgLogo = new ImageView(arrowImg, 32, 24);
  imgLogo->setPosition(80, 32);
  
  // Adicionar componentes ao display
  display.addComponent(txtTitle);
  display.addComponent(txtStatus);
  display.addComponent(txtOrientation);
  display.addComponent(txtInfo);
  display.addComponent(imgLogo);
  
  // Desenho inicial
  display.update();
}

void loop() {
  // Verificar se o botão foi pressionado
  if (display.wasButton1Pressed()) {
    // Alternar estado da rotação automática
    autoRotationEnabled = !autoRotationEnabled;
    
    // Atualizar texto de status
    sprintf(statusText, "Auto-rotacao: %s", autoRotationEnabled ? "ATIVADA" : "DESATIVADA");
    txtStatus->setText(statusText);
    
    // Configurar o sensor
    orientationSensor->setAutoRotationEnabled(autoRotationEnabled);
    
    Serial.print("Auto-rotação: ");
    Serial.println(autoRotationEnabled ? "ATIVADA" : "DESATIVADA");
  }
  
  // Atualizar o sensor de orientação
  orientationSensor->update();
  
  // Atualizar o display
  display.update();
  
  // Pequeno delay
  delay(10);
} 