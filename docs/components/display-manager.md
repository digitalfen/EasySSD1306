# DisplayManager

O `DisplayManager` é o componente central da biblioteca EasySSD1306. Ele gerencia todos os componentes visuais e coordena a renderização do display.

## Visão Geral

O `DisplayManager` é responsável por:
- Gerenciar o display SSD1306
- Coordenar a renderização de componentes
- Controlar a navegação
- Gerenciar estados da interface

## Inicialização

```cpp
DisplayManager display;
display.setDisplay(new Adafruit_SSD1306(128, 64));
```

## Configuração de Botões

```cpp
display.setButtons(BUTTON_UP_PIN, BUTTON_DOWN_PIN);
```

## Adicionando Componentes

```cpp
TextView text(1, "Texto de exemplo");
display.addComponent(&text);
```

## Renderização

```cpp
void loop() {
    display.render();
    delay(100);
}
```

## Estados

O `DisplayManager` mantém controle de dois estados importantes:
- `currentState`: Estado atual da interface
- `lastState`: Estado anterior da interface

Para mudar o estado:
```cpp
display.setState(NOVO_ESTADO);
```

## Variáveis Estáticas

- `selectedItem`: Índice do item selecionado
- `confirmItem`: Flag de confirmação
- `cancelItem`: Flag de cancelamento

## Exemplo Completo

```cpp
#include <EasySSD1306.h>

DisplayManager display;
TextView text(1, "Menu Principal");
Navigation menu(2);

void setup() {
    display.setDisplay(new Adafruit_SSD1306(128, 64));
    display.setButtons(2, 3);  // Pinos 2 e 3 para botões
    
    display.addComponent(&text);
    display.addComponent(&menu);
}

void loop() {
    display.render();
    delay(100);
}
```

## Referência da API

### Construtores
- `DisplayManager()`
- `DisplayManager(DisplayResolution resolution)`

### Métodos Públicos
- `void setDisplay(Adafruit_SSD1306 *disp)`
- `void setButtons(uint8_t buttonUp, uint8_t buttonDown)`
- `void addComponent(IDisplayComponent *component)`
- `void render()`
- `void setState(unsigned int n)`

### Variáveis Públicas
- `unsigned int currentState`
- `unsigned int lastState`
- `static int selectedItem`
- `static bool confirmItem`
- `static bool cancelItem`

## Dicas de Uso

1. **Inicialização**
   - Sempre inicialize o display antes de adicionar componentes
   - Configure os botões se for usar navegação

2. **Renderização**
   - Chame `render()` no loop principal
   - Mantenha um delay adequado para evitar flickering

3. **Estados**
   - Use estados para gerenciar diferentes telas
   - Mantenha controle do estado anterior para navegação

4. **Componentes**
   - Adicione componentes na ordem desejada
   - Cada componente deve ter um ID único 