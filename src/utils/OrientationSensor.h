#ifndef ORIENTATION_SENSOR_H
#define ORIENTATION_SENSOR_H

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPU6050.h>
#include "../EasySSD1306.h"

// Classe para gerenciar orientação automática usando o sensor MPU6050
class OrientationSensor {
public:
    // Construtor
    OrientationSensor(DisplayManager* display, unsigned long updateInterval = 500) {
        this->display = display;
        this->updateInterval = updateInterval;
        this->currentRotation = 0;
    }
    
    // Inicializa o sensor
    bool begin() {
        return mpu.begin();
    }
    
    // Define se a rotação automática está ativa
    void setAutoRotationEnabled(bool enabled) {
        autoRotationEnabled = enabled;
    }
    
    // Define a sensibilidade (quanto maior, mais resistente a mudar de orientação)
    void setSensitivity(float sensitivity) {
        this->sensitivity = sensitivity;
    }
    
    // Atualiza a orientação - deve ser chamado no loop
    void update() {
        if (!autoRotationEnabled) return;
        
        unsigned long currentMillis = millis();
        if (currentMillis - lastUpdateTime < updateInterval) return;
        
        lastUpdateTime = currentMillis;
        
        // Ler os dados do acelerômetro
        sensors_event_t a, g, temp;
        if (mpu.getEvent(&a, &g, &temp)) {
            // Aplicar filtro de suavização
            xFiltered = (xFiltered * (sensitivity - 1) + a.acceleration.x) / sensitivity;
            yFiltered = (yFiltered * (sensitivity - 1) + a.acceleration.y) / sensitivity;
            
            // Determinar orientação suavizada
            uint8_t newRotation = determineOrientation(xFiltered, yFiltered);
            
            // Só atualiza se a orientação realmente mudou e está estável
            if (newRotation != currentRotation) {
                // Verificar estabilidade por algumas leituras consecutivas
                if (newRotation == lastDetectedRotation) {
                    stabilityCounter++;
                    if (stabilityCounter >= requiredStability) {
                        // Orientação estável - atualizar o display
                        currentRotation = newRotation;
                        display->setDisplayRotation(currentRotation);
                        stabilityCounter = 0;
                        
                        // Chamar o callback se estiver definido
                        if (orientationChangedCallback) {
                            orientationChangedCallback(currentRotation);
                        }
                    }
                } else {
                    // Redefinir contador se a orientação não for estável
                    stabilityCounter = 0;
                    lastDetectedRotation = newRotation;
                }
            }
        }
    }
    
    // Retorna a rotação atual (0-3)
    uint8_t getRotation() const {
        return currentRotation;
    }
    
    // Retorna os valores x e y filtrados do acelerômetro
    float getXFiltered() const {
        return xFiltered;
    }
    
    float getYFiltered() const {
        return yFiltered;
    }
    
    // Define uma função de callback para ser chamada quando a orientação mudar
    void setOrientationChangedCallback(void (*callback)(uint8_t)) {
        orientationChangedCallback = callback;
    }
    
    // Define o número de leituras estáveis necessárias para confirmar mudança
    void setRequiredStability(uint8_t count) {
        requiredStability = count;
    }
    
private:
    Adafruit_MPU6050 mpu;
    DisplayManager* display;
    
    bool autoRotationEnabled = true;
    unsigned long updateInterval = 500; // ms
    unsigned long lastUpdateTime = 0;
    
    float xFiltered = 0.0f;
    float yFiltered = 0.0f;
    float sensitivity = 5.0f; // Fator de suavização
    
    uint8_t currentRotation = 0;
    uint8_t lastDetectedRotation = 0;
    uint8_t stabilityCounter = 0;
    uint8_t requiredStability = 3; // Leituras consecutivas para confirmar
    
    void (*orientationChangedCallback)(uint8_t) = nullptr;
    
    // Função para determinar a orientação com base nos valores do acelerômetro
    uint8_t determineOrientation(float x, float y) {
        float absX = abs(x);
        float absY = abs(y);
        
        // Adicionar uma zona "morta" para evitar mudanças acidentais
        const float THRESHOLD = 0.5f;
        
        // Se ambos os valores são muito pequenos, manter a orientação atual
        if (absX < THRESHOLD && absY < THRESHOLD) {
            return currentRotation;
        }
        
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
};

#endif // ORIENTATION_SENSOR_H 