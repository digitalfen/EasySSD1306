#include "display/components/TextAnimation.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

unsigned int TextAnimation::render(Adafruit_SSD1306 *display)
{

    unsigned int nextView = 0;

    if (exec)
    {
        next = exec();
    }

    if (preset == TXT_ANIM_REVEAL_FROM_CENTER)
    {
        presetIntro1(display);
    }
    else if (preset == TXT_ANIM_SLIDE_FROM_LEFT)
    {
        presetIntro2(display);
    }
    else if (preset == TXT_ANIM_SLIDE_FROM_RIGHT)
    {
        presetIntro3(display);
    }
    else if (preset == TXT_ANIM_RISE_AND_FALL)
    {
        presetIntro4(display);
    }
    else if (preset == TXT_ANIM_FALL_AND_WRAP)
    {
        presetIntro5(display);
    }
    else if (preset == TXT_ANIM_FALL_BLOCK)
    {
        presetIntro7(display);
    }
    else if (preset == TXT_ANIM_FALL_IN_SEQUENCE)
    {
        presetIntro8(display);
    }
    else
    {
        display->clearDisplay();
        display->setTextSize(1);
        display->setCursor(0, SCREEN_HEIGHT / 2 - 4);
        display->print("Unknown TextAnimation request.");
        display->display();
        delay(3000);
    }

    return next;
}

void TextAnimation::execute(std::function<unsigned int()> execute)
{
    this->exec = execute;
}

void TextAnimation::nextComponent(unsigned int nextComponent)
{
    this->next = nextComponent;
}
void TextAnimation::presetIntro1(Adafruit_SSD1306 *display)
{
    int centerX = display->width() / 2;
    int centerY = display->height() / 2;

    // ** Fase 2: Retração do quadrado branco **
    for (int size = display->width(); size >= 1; size -= 2)
    {

        // Revela a mensagem durante a retração
        display->setTextSize(1);
        display->setTextColor(WHITE);
        display->setCursor((display->width() - strlen(text) * 6) / 2, display->height() / 2 - 4);
        display->print(text);

        // Quadrado branco retraindo
        int x = centerX - size / 2;
        int y = centerY - size / 2;
        display->fillRect(x, y, size, size, BLACK); // Preenchendo o fundo para retrair
        display->display();
        delay(20);
    }

    // ** Exibe a mensagem final por um tempo **
    display->clearDisplay();
    display->setTextSize(1);
    display->setTextColor(WHITE);
    display->setCursor((display->width() - strlen(text) * 6) / 2, display->height() / 2 - 4);
    display->print(text);
    display->display();

    delay(3000); // Mantém a mensagem visível por 1 segundo
    display->clearDisplay();
}

void TextAnimation::presetIntro2(Adafruit_SSD1306 *display)
{
    const int textSize = 1;
    const int charWidth = 6 * textSize;                                // Largura de cada caractere
    const int charHeight = 8 * textSize;                               // Altura de cada caractere
    const int maxChars = SCREEN_WIDTH / charWidth;                     // Máximo de caracteres no display
    const int centerX = (SCREEN_WIDTH - strlen(text) * charWidth) / 2; // Posição central horizontal
    const int centerY = (SCREEN_HEIGHT - charHeight) / 2;              // Posição central vertical
    const int moveSpeed = 3;                                           // Velocidade do movimento horizontal

    // Filtrar entrada para evitar palavras muito grandes
    if (strlen(text) > maxChars)
    {
        display->clearDisplay();
        display->setTextSize(1);
        display->setCursor(0, SCREEN_HEIGHT / 2 - 4);
        display->print("Texto muito longo!");
        display->display();
        delay(3000);
        return;
    }

    display->setTextSize(textSize);
    display->setTextColor(SSD1306_WHITE);

    int charX[maxChars]; // Posições horizontais de cada letra
    int charY[maxChars]; // Posições verticais de cada letra

    // Inicializar posições das letras (todas começam fora da tela à esquerda)
    for (int i = 0; i < strlen(text); i++)
    {
        charX[i] = -charWidth; // Começam fora da tela à esquerda
        charY[i] = centerY;    // Todos começam no centro vertical
    }

    // ** Fase 1: As letras se movendo da esquerda para a direita uma por uma**
    bool lettersInPlace = false;
    while (!lettersInPlace)
    {
        lettersInPlace = true;
        display->clearDisplay();

        for (int i = 0; i < strlen(text); i++)
        {
            // A letra se move até a posição central
            if (charX[i] < centerX + i * charWidth) // Move para a posição central
            {
                charX[i] += moveSpeed;  // Faz a letra mover para a direita
                lettersInPlace = false; // Ainda há letras em movimento
            }
            display->setCursor(charX[i], charY[i]);
            display->write(text[i]);
        }

        display->display();
        delay(30); // Controle da velocidade do movimento
    }

    delay(2500);
    display->clearDisplay(); // Limpa a tela ao final
}
void TextAnimation::presetIntro3(Adafruit_SSD1306 *display)
{
    const int textSize = 1;
    const int charWidth = 6 * textSize;                                // Largura de cada caractere
    const int charHeight = 8 * textSize;                               // Altura de cada caractere
    const int maxChars = SCREEN_WIDTH / charWidth;                     // Máximo de caracteres no display
    const int centerX = (SCREEN_WIDTH - strlen(text) * charWidth) / 2; // Posição central horizontal
    const int centerY = (SCREEN_HEIGHT - charHeight) / 2;              // Posição central vertical
    const int moveSpeed = 3;                                           // Velocidade do movimento horizontal

    // Filtrar entrada para evitar palavras muito grandes
    if (strlen(text) > maxChars)
    {
        display->clearDisplay();
        display->setTextSize(1);
        display->setCursor(0, SCREEN_HEIGHT / 2 - 4);
        display->print("Texto muito longo!");
        display->display();
        delay(3000);
        return;
    }

    display->setTextSize(textSize);
    display->setTextColor(SSD1306_WHITE);

    int charX[maxChars]; // Posições horizontais de cada letra
    int charY[maxChars]; // Posições verticais de cada letra

    // Inicializar posições das letras (todas começam fora da tela à direita)
    for (int i = 0; i < strlen(text); i++)
    {
        charX[i] = SCREEN_WIDTH + charWidth; // Começam completamente fora da tela à direita
        charY[i] = centerY;                  // Todos começam no centro vertical
    }

    // ** Fase 1: As letras se movendo da direita para a esquerda uma por uma**
    bool lettersInPlace = false;
    while (!lettersInPlace)
    {
        lettersInPlace = true;
        display->clearDisplay();

        for (int i = 0; i < strlen(text); i++)
        {
            // A letra se move até a posição central
            if (charX[i] > centerX + i * charWidth) // Move para a posição central
            {
                charX[i] -= moveSpeed;  // Faz a letra mover para a esquerda
                lettersInPlace = false; // Ainda há letras em movimento
            }
            display->setCursor(charX[i], charY[i]);
            display->write(text[i]);
        }

        display->display();
        delay(30); // Controle da velocidade do movimento
    }

    delay(2500);             // Tempo que a animação fica na tela
    display->clearDisplay(); // Limpa a tela ao final
}

void TextAnimation::presetIntro4(Adafruit_SSD1306 *display)
{
    const int textSize = 1;
    const int charWidth = 6 * textSize;                                // Largura de cada caractere
    const int charHeight = 8 * textSize;                               // Altura de cada caractere
    const int maxChars = SCREEN_WIDTH / charWidth;                     // Máximo de caracteres no display
    const int centerX = (SCREEN_WIDTH - strlen(text) * charWidth) / 2; // Posição central horizontal
    const int centerY = (SCREEN_HEIGHT - charHeight) / 2;              // Posição central vertical
    const int fallSpeed = 3;                                           // Velocidade da subida/descida das letras

    // Filtrar entrada para evitar palavras muito grandes
    if (strlen(text) > maxChars)
    {
        display->clearDisplay();
        display->setTextSize(1);
        display->setCursor(0, SCREEN_HEIGHT / 2 - 4);
        display->print("Texto muito longo!");
        display->display();
        delay(3000);
        return;
    }

    display->setTextSize(textSize);
    display->setTextColor(SSD1306_WHITE);

    int charX[maxChars]; // Posições horizontais de cada letra
    int charY[maxChars]; // Posições verticais de cada letra

    // Inicializar posições das letras (todas começam abaixo da tela)
    for (int i = 0; i < strlen(text); i++)
    {
        charX[i] = centerX + i * charWidth; // Centralizado horizontalmente
        charY[i] = SCREEN_HEIGHT;           // Começam abaixo da tela
    }

    // ** Fase 1: As letras subindo, uma por uma**
    bool lettersInPlace = false;
    while (!lettersInPlace)
    {
        lettersInPlace = true;
        display->clearDisplay();

        for (int i = 0; i < strlen(text); i++)
        {
            // A letra sobe até a posição central
            if (charY[i] > centerY)
            {
                charY[i] -= fallSpeed;  // Faz a letra subir
                lettersInPlace = false; // Ainda há letras em movimento
            }
            display->setCursor(charX[i], charY[i]);
            display->write(text[i]);
        }

        display->display();
        delay(30); // Controle da velocidade da subida
    }

    delay(3000); // Aguarda um momento para fixar o texto formado

    // ** Fase 2: Letras descendo uma por uma**
    bool lettersGone = false;
    while (!lettersGone)
    {
        lettersGone = true;
        display->clearDisplay();

        for (int i = 0; i < strlen(text); i++)
        {
            // Faz a letra descer uma por uma até sair da tela
            if (charY[i] < SCREEN_HEIGHT)
            {
                charY[i] += fallSpeed; // Faz a letra descer
                lettersGone = false;   // Ainda há letras descendo
            }
            display->setCursor(charX[i], charY[i]);
            display->write(text[i]);
        }

        display->display();
        delay(30); // Controle da velocidade da descida
    }

    delay(200);              // Controle da velocidade da descida
    display->clearDisplay(); // Limpa a tela ao final
}

void TextAnimation::presetIntro5(Adafruit_SSD1306 *display)
{
    const int textSize = 1;
    const int charWidth = 6 * textSize;                                // Largura de cada caractere
    const int charHeight = 8 * textSize;                               // Altura de cada caractere
    const int maxChars = SCREEN_WIDTH / charWidth;                     // Máximo de caracteres no display
    const int centerX = (SCREEN_WIDTH - strlen(text) * charWidth) / 2; // Posição central horizontal
    const int centerY = (SCREEN_HEIGHT - charHeight) / 2;              // Posição central vertical
    const int blinkCount = 3;                                          // Quantidade de piscadas
    const int fallSpeed = 1;                                           // Velocidade da queda (quanto menor, mais rápido)

    // Filtrar entrada para evitar palavras muito grandes
    if (strlen(text) > maxChars)
    {
        display->clearDisplay();
        display->setTextSize(1);
        display->setCursor(0, SCREEN_HEIGHT / 2 - 4);
        display->print("Texto muito longo!");
        display->display();
        delay(3000);
        return;
    }

    display->setTextSize(textSize);
    display->setTextColor(SSD1306_WHITE);

    int charX[maxChars]; // Posições horizontais de cada letra
    int charY[maxChars]; // Posições verticais de cada letra

    // Inicializar posições das letras
    for (int i = 0; i < strlen(text); i++)
    {
        charX[i] = centerX + i * charWidth; // Centralizado horizontalmente
        charY[i] = -charHeight;             // Todas começam fora da tela
    }

    // Animação de queda de todas as letras ao mesmo tempo
    bool lettersInPlace = false;
    while (!lettersInPlace)
    {
        lettersInPlace = true;
        display->clearDisplay();

        for (int i = 0; i < strlen(text); i++)
        {
            if (charY[i] < centerY)
            {
                charY[i] += fallSpeed;  // Faz a letra "cair"
                lettersInPlace = false; // Ainda há letras em movimento
            }
            display->setCursor(charX[i], charY[i]);
            display->write(text[i]);
        }

        display->display();
        delay(25); // Controle da velocidade da queda
    }

    const int lineSpeed = 2;     // Velocidade do crescimento das linhas
    int lineTopLength = 0;       // Comprimento da linha superior
    int lineBottomLength = 0;    // Comprimento da linha inferior
    const int lineDistance = 20; // Distância entre as linhas superior e inferior

    // Animação das linhas
    while (lineTopLength < SCREEN_WIDTH || lineBottomLength < SCREEN_WIDTH)
    {

        // Desenha a linha superior que cresce da esquerda para a direita
        if (lineTopLength < SCREEN_WIDTH)
        {
            display->drawLine(0, 17, lineTopLength, 17, SSD1306_WHITE);
            lineTopLength += lineSpeed; // Aumenta o comprimento da linha superior
        }

        // Desenha a linha inferior que cresce da direita para a esquerda
        if (lineBottomLength < SCREEN_WIDTH)
        {
            display->drawLine(SCREEN_WIDTH, centerY + lineDistance, SCREEN_WIDTH - lineBottomLength, centerY + lineDistance, SSD1306_WHITE);
            lineBottomLength += lineSpeed; // Aumenta o comprimento da linha inferior
        }

        display->display(); // Atualiza o display
        delay(10);          // Controla a velocidade do crescimento
    }

    delay(3000); // Mantém a mensagem visível por 1 segundo
    display->clearDisplay();
}

void TextAnimation::presetIntro6(Adafruit_SSD1306 *display)
{

    // Coordenadas centrais
    int centerX = display->width() / 2;
    int centerY = display->height() / 2;

    // ** Fase 1: Cursor piscando antes de começar a exibir as mensagens de boot **
    int cursorY = 10;                // Posição Y onde o cursor ficará piscando, no topo da tela
    const int cursorBlinkTime = 500; // Tempo de blink do cursor (500ms)
    unsigned long cursorStartTime = millis();
    bool cursorState = false; // Controle do estado do cursor (ligado/desligado)

    // Enquanto o cursor estiver piscando, antes de começar a exibir as mensagens
    while (millis() - cursorStartTime < 3000) // O cursor vai piscar por 3 segundos
    {
        display->clearDisplay();

        // Exibe o cursor piscando
        if (cursorState)
        {
            display->setCursor(0, cursorY); // Posição do cursor
            display->write('_');            // Caractere do cursor
        }

        display->display();
        delay(cursorBlinkTime); // Intervalo de piscada

        cursorState = !cursorState; // Alterna entre ligado/desligado
    }
    // ** Fase 1: Texto estilo cyberpunk (Aleatório, com símbolos e ilegível) **
    const char *boottexts[] = {"System Init... OK",
                               "Connecting... Done",
                               "Loading... Complete",
                               "Network... Active",
                               "Boot... Success",
                               "Acquiring Data...",
                               "Data Stream Active",
                               "Run... Initialization",
                               "System Ready > OK",
                               "Rebooting... Done",
                               "Connection Stable",
                               "Data Stream Online",
                               "Boot Complete...",
                               "Locating... OK",
                               "Startup Complete",
                               "Running Diagnostics",
                               "Initialization Done",
                               "Access Granted",
                               "Darknet Link Ready",
                               "System Online",
                               "Root Access Enabled"};

    // ** Fase 2: Barra de Progresso na Parte Inferior da Tela **
    int progressBarWidth = display->width() - 10; // Largura da barra
    int progressBarHeight = 10;                   // Altura da barra
    int progress = 0;

    unsigned long startTime = millis(); // Captura o tempo inicial
    unsigned long elapsedTime = 0;

    // Começa o processo de exibição simultânea
    while (progress <= progressBarWidth)
    {
        elapsedTime = millis() - startTime;

        // Exibe as mensagens de boot de forma rápida e aleatória
        if (elapsedTime > random(100, 300))
        {
            display->clearDisplay();
            display->setTextSize(1);
            display->setTextColor(WHITE);
            display->setCursor(0, 0);
            display->print(boottexts[random(0, 20)]); // Escolhe uma mensagem aleatória
            display->display();
            startTime = millis(); // Reseta o tempo para o próximo delay aleatório
        }

        // Exibe a barra de progresso na parte inferior
        display->fillRect(5, display->height() - progressBarHeight - 5, progress, progressBarHeight, WHITE);

        // Atualiza a tela
        display->display();
        delay(5); // Delay para a animação da barra

        // Aumenta o progresso da barra
        progress += 1;
    }

    // ** Fase 3: Animação de Digitação da Mensagem Final **
    display->clearDisplay();
    display->setTextSize(1);                                                                  // Tamanho do texto
    display->setTextColor(WHITE);                                                             // Cor do texto
    display->setCursor((display->width() - strlen(text) * 6) / 2, display->height() / 2 - 4); // Centraliza o texto

    for (int i = 0; text[i] != '\0'; i++)
    {
        display->print(text[i]); // Mostra uma letra de cada vez
        display->display();
        delay(100); // Atraso entre as letras
    }

    delay(3000); // Mantém a mensagem visível por 1 segundo
    display->clearDisplay();
}

void TextAnimation::presetIntro7(Adafruit_SSD1306 *display)
{
    const int textSize = 1;
    const int charWidth = 6 * textSize;                                // Largura de cada caractere
    const int charHeight = 8 * textSize;                               // Altura de cada caractere
    const int maxChars = SCREEN_WIDTH / charWidth;                     // Máximo de caracteres no display
    const int centerX = (SCREEN_WIDTH - strlen(text) * charWidth) / 2; // Posição central horizontal
    const int centerY = (SCREEN_HEIGHT - charHeight) / 2;              // Posição central vertical
    const int moveSpeed = 2;                                           // Velocidade do movimento vertical
    const int delayTime = 30;                                          // Tempo de delay

    // Filtrar entrada para evitar palavras muito grandes
    if (strlen(text) > maxChars)
    {
        display->clearDisplay();
        display->setTextSize(1);
        display->setCursor(0, SCREEN_HEIGHT / 2 - 4);
        display->print("Texto muito longo!");
        display->display();
        delay(3000);
        return;
    }

    display->setTextSize(textSize);
    display->setTextColor(SSD1306_WHITE);

    int charX[maxChars]; // Posições horizontais de cada letra
    int charY[maxChars]; // Posições verticais de cada letra

    // Inicializar posições das letras (todas começam acima da tela)
    for (int i = 0; i < strlen(text); i++)
    {
        charX[i] = centerX + i * charWidth; // Começam centralizadas horizontalmente
        charY[i] = -charHeight;             // Começam fora da tela, acima
    }

    // ** Fase 1: As letras caindo uma por uma**
    bool lettersInPlace = false;
    while (!lettersInPlace)
    {
        lettersInPlace = true;
        display->clearDisplay();

        for (int i = 0; i < strlen(text); i++)
        {
            // A letra cai até a posição central
            if (charY[i] < centerY)
            {
                charY[i] += moveSpeed;  // Faz a letra cair
                lettersInPlace = false; // Ainda há letras em movimento
            }

            display->setCursor(charX[i], charY[i]);
            display->write(text[i]);
        }

        display->display();
        delay(delayTime); // Controle da velocidade do movimento
    }

    delay(2500);             // Tempo que a animação fica na tela
    display->clearDisplay(); // Limpa a tela ao final
}
void TextAnimation::presetIntro8(Adafruit_SSD1306 *display)
{
    const int textSize = 1;
    const int charWidth = 6 * textSize;                                // Largura de cada caractere
    const int charHeight = 8 * textSize;                               // Altura de cada caractere
    const int maxChars = SCREEN_WIDTH / charWidth;                     // Máximo de caracteres no display
    const int centerX = (SCREEN_WIDTH - strlen(text) * charWidth) / 2; // Posição central horizontal
    const int centerY = (SCREEN_HEIGHT - charHeight) / 2;              // Posição central vertical
    const int fallSpeed = 10;                                          // Velocidade da queda

    // Filtrar entrada para evitar palavras muito grandes
    if (strlen(text) > maxChars)
    {
        display->clearDisplay();
        display->setTextSize(1);
        display->setCursor(0, SCREEN_HEIGHT / 2 - 4);
        display->print("Texto muito longo!");
        display->display();
        delay(3000);
        return;
    }

    display->setTextSize(textSize);
    display->setTextColor(SSD1306_WHITE);

    int charX[maxChars]; // Posições horizontais de cada letra
    int charY[maxChars]; // Posições verticais de cada letra

    // Inicializar as posições das letras (começam acima da tela)
    for (int i = 0; i < strlen(text); i++)
    {
        charX[i] = centerX + i * charWidth; // Posicionar no centro horizontalmente
        charY[i] = -charHeight;             // Começam fora da tela, acima
    }

    // ** Fase 1: As letras caem uma por uma**
    for (int i = 0; i < strlen(text); i++)
    {
        // Se o caractere for um espaço, pula o loop
        if (text[i] == ' ')
        {
            continue;
        }

        bool letterFalling = true;

        while (letterFalling)
        {
            display->clearDisplay();

            // A letra cai até o centro vertical
            if (charY[i] < centerY)
            {
                charY[i] += fallSpeed; // Move para baixo
            }
            else
            {
                charY[i] = centerY;    // Posição final no centro
                letterFalling = false; // A letra já parou de cair
            }

            // Desenhar as letras, pulando espaços
            for (int j = 0; j < strlen(text); j++)
            {
                // Verifica se o caractere é um espaço e pula
                if (text[j] != ' ')
                {
                    display->setCursor(charX[j], charY[j]);
                    display->write(text[j]);
                }
            }

            display->display();
            delay(30); // Controle da velocidade da queda
        }
    }

    delay(2500);             // Tempo que a animação fica na tela
    display->clearDisplay(); // Limpa a tela ao final
}
