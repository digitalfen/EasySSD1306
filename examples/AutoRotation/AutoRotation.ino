#include <EasySSD1306.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

// Criar instância do display
DisplayManager display(RESOLUTION_128x64);

// Criar instância do acelerômetro
Adafruit_MPU6050 mpu;

// Componentes de interface
TextView* txtTitle;
TextView* txtOrientation;
TextView* txtSensor;

// Variáveis para controle de rotação
uint8_t currentRotation = 0;
char rotationText[20];
char sensorText[20];

// Tempo da última verificação de orientação
unsigned long lastOrientationCheck = 0;
const unsigned long orientationCheckInterval = 500; // 500ms

void setup() {
  Serial.begin(115200);
  Serial.println("Exemplo de Rotação Automática");

  // Inicializar o barramento I2C
  Wire.begin();
  
  // Inicializar o display
  if (!display.begin()) {
    Serial.println("Falha ao inicializar o display SSD1306!");
    while (1);
  }
  
  // Tentar inicializar o sensor MPU6050
  if (!mpu.begin()) {
    Serial.println("Falha ao encontrar o sensor MPU6050!");
    // Continuar mesmo sem o sensor
  }
  
  // Configurar o acelerômetro
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);

  // Criar e configurar componentes
  txtTitle = new TextView("Rotacao Automatica");
  txtTitle->setPosition(0, 0);
  
  sprintf(rotationText, "Rotacao: %d graus", currentRotation * 90);
  txtOrientation = new TextView(rotationText);
  txtOrientation->setPosition(0, 12);
  
  txtSensor = new TextView("Aguardando sensor...");
  txtSensor->setPosition(0, 24);
  
  // Adicionar componentes ao display
  display.addComponent(txtTitle);
  display.addComponent(txtOrientation);
  display.addComponent(txtSensor);
  
  // Desenho inicial
  display.update();
}

void loop() {
  // Verificar a orientação a cada intervalo definido
  if (millis() - lastOrientationCheck > orientationCheckInterval) {
    lastOrientationCheck = millis();
    
    // Ler os dados do acelerômetro
    sensors_event_t a, g, temp;
    if (mpu.getEvent(&a, &g, &temp)) {
      float x = a.acceleration.x;
      float y = a.acceleration.y;
      
      // Atualizar texto do sensor
      sprintf(sensorText, "x:%.1f y:%.1f", x, y);
      txtSensor->setText(sensorText);
      
      // Determinar a orientação com base nos dados do acelerômetro
      uint8_t newRotation = determineOrientation(x, y);
      
      // Se a orientação mudou, atualizar o display
      if (newRotation != currentRotation) {
        currentRotation = newRotation;
        
        // Atualizar o texto de orientação
        sprintf(rotationText, "Rotacao: %d graus", currentRotation * 90);
        txtOrientation->setText(rotationText);
        
        // Aplicar a rotação ao display
        display.setDisplayRotation(currentRotation);
        
        Serial.print("Rotação alterada para: ");
        Serial.print(currentRotation * 90);
        Serial.println(" graus");
      }
    } else {
      txtSensor->setText("Sensor nao detectado");
    }
  }
  
  // Atualizar o display
  display.update();
  
  // Pequeno delay
  delay(10);
}

// Determina a orientação com base nos dados do acelerômetro
uint8_t determineOrientation(float x, float y) {
  // Usar os valores x e y do acelerômetro para determinar a orientação
  
  // Valores absolutos para comparação
  float absX = abs(x);
  float absY = abs(y);
  
  // Se a magnitude de Y é maior que a de X, a orientação é determinada por Y
  if (absY > absX) {
    if (y > 0) {
      return 2; // 180 graus (de cabeça para baixo)
    } else {
      return 0; // 0 graus (normal)
    }
  } 
  // Se a magnitude de X é maior, a orientação é determinada por X
  else {
    if (x > 0) {
      return 1; // 90 graus (deitado para a direita)
    } else {
      return 3; // 270 graus (deitado para a esquerda)
    }
  }
} 