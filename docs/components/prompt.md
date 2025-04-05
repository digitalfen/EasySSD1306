# Prompt Component

O componente Prompt permite criar interfaces interativas com teclado virtual para entrada de texto no display OLED.

## Visão Geral

O Prompt é um componente especializado que implementa um teclado virtual completo no display OLED, permitindo que os usuários insiram texto mesmo sem um teclado físico. É ideal para:

- Configurações do dispositivo
- Entrada de nomes ou identificadores
- Formulários simples
- Menus de configuração
- Qualquer interface que necessite entrada de texto

## Funcionalidades

- **Teclado Virtual**: Interface de teclado completa que aparece no display
- **Múltiplos Layouts**: Suporte para diferentes tipos de teclado:
  - Alfabético (maiúsculas/minúsculas)
  - Numérico
  - Caracteres especiais
- **Validação de Entrada**: Regras personalizáveis para validar o texto inserido
- **Limite de Caracteres**: Restrição do tamanho máximo da entrada
- **Callbacks**: Funções de retorno para processar a entrada concluída
- **Feedback Visual**: Indicadores visuais durante a digitação
- **Modos de Entrada**: Suporte para diferentes tipos de entrada (texto, números, senhas)

## Uso Básico

```cpp
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "display/DisplayManager.h"
#include "display/components/Prompt.h"

DisplayManager display(RESOLUTION_128x64);
Prompt* prompt;

void setup() {
    display.begin();
    
    // Criar um prompt para entrada de nome
    prompt = new Prompt("Digite seu nome:", "");
    prompt->setMaxLength(20);
    prompt->setKeyboardType(KEYBOARD_ALPHA);
    
    // Adicionar callback para quando a entrada for concluída
    prompt->setOnComplete([](const char* value) {
        Serial.print("Nome inserido: ");
        Serial.println(value);
    });
    
    display.addComponent(prompt);
}

void loop() {
    display.render();
}
```

## Configurações Avançadas

### Tipos de Teclado

```cpp
// Teclado alfabético (padrão)
prompt->setKeyboardType(KEYBOARD_ALPHA);

// Teclado numérico
prompt->setKeyboardType(KEYBOARD_NUMERIC);

// Teclado com caracteres especiais
prompt->setKeyboardType(KEYBOARD_SPECIAL);
```

### Validação de Entrada

```cpp
// Definir uma função de validação personalizada
prompt->setValidator([](const char* input) -> bool {
    // Verificar se a entrada contém apenas letras
    for(int i = 0; input[i] != '\0'; i++) {
        if(!isalpha(input[i])) return false;
    }
    return true;
});
```

### Modo de Senha

```cpp
// Configurar para entrada de senha (caracteres ocultos)
prompt->setPasswordMode(true);
```

## Dicas de Uso

1. **Posicionamento**: O teclado virtual ocupa uma parte significativa do display. Considere o espaço disponível ao posicionar outros elementos.

2. **Feedback Visual**: O componente fornece feedback visual durante a digitação. Use isso para melhorar a experiência do usuário.

3. **Navegação**: O teclado virtual é navegável usando os botões configurados no DisplayManager.

4. **Personalização**: Você pode personalizar a aparência do teclado virtual para combinar com o estilo da sua interface.

## Exemplos

### Configuração de WiFi

```cpp
Prompt* ssidPrompt = new Prompt("SSID:", "");
Prompt* passPrompt = new Prompt("Senha:", "");

// Configurar o prompt de senha para ocultar caracteres
passPrompt->setPasswordMode(true);

// Adicionar callbacks
ssidPrompt->setOnComplete([](const char* ssid) {
    // Salvar SSID
});

passPrompt->setOnComplete([](const char* password) {
    // Salvar senha e conectar
});
```

### Menu de Configurações

```cpp
Prompt* namePrompt = new Prompt("Nome do Dispositivo:", "ESP32");
namePrompt->setMaxLength(16);

namePrompt->setOnComplete([](const char* name) {
    // Salvar nome do dispositivo
});
``` 