#include "display/components/View.h"
#include "display/DisplayManager.h"

unsigned int View::render(Adafruit_SSD1306 *display)
{

    // Renderiza o conteúdo da página conforme o preset
    unsigned int nextView = 0;

    std::vector<String> newText; // Nova lista de linhas

    // Itera sobre cada linha na lista original 'text'
    for (const auto &line : text)
    {
        // Cria uma cópia da linha e aplica trim nela
        String trimmedLine = line; // Cria uma cópia da linha
        trimmedLine.trim();        // Aplica trim na cópia

        // Verifica se a linha está vazia ou contém apenas espaços em branco
        if (trimmedLine.length() == 0)
        {
            newText.push_back(line); // Adiciona a linha vazia diretamente à nova lista
            continue;                // Continua para a próxima linha
        }

        String currentLine = ""; // Linha temporária para acumular as palavras
        String word = "";        // Para armazenar cada palavra individualmente
        int lineLength = 0;

        // Itera sobre cada caractere na linha para pegar as palavras
        for (int i = 0; i < line.length(); ++i)
        {
            char c = line[i];

            // Se encontrar um espaço ou fim da linha, finalize a palavra
            if (c == ' ' || i == line.length() - 1)
            {
                if (i == line.length() - 1 && c != ' ') // Adiciona a última letra se não for espaço
                {
                    word += c;
                }

                // Se a palavra não couber na linha (com o espaço necessário)
                if (currentLine.length() + word.length() + 1 > 18)
                {
                    if (currentLine.length() > 0)
                    {
                        newText.push_back(currentLine); // Adiciona a linha atual
                    }
                    currentLine = word; // Começa uma nova linha com a palavra atual
                }
                else
                {
                    if (currentLine.length() > 0)
                    {
                        currentLine += " "; // Adiciona um espaço antes de adicionar a palavra
                    }
                    currentLine += word; // Adiciona a palavra à linha
                }

                // Limpa a palavra para a próxima iteração
                word = "";
            }
            else
            {
                word += c; // Acumula a palavra enquanto não for espaço
            }
        }

        // Adiciona a última linha ao vetor, se houver texto remanescente
        if (currentLine.length() > 0)
        {
            newText.push_back(currentLine);
        }
    }

    // Substitui a lista original pela nova lista
    text = newText;

    if (preset == BORDERLESS_LEFT)
    {
        nextView = presetView1(display);
    }
    else if (preset == BORDERLESS_CENTER)
    {
        nextView = presetView2(display);
    }
    else if (preset == BORDERLESS_RIGHT)
    {
        nextView = presetView3(display);
    }
    else if (preset == SOLID_BORDER_LEFT)
    {
        nextView = presetView4(display);
    }
    else if (preset == SOLID_BORDER_CENTER)
    {
        nextView = presetView5(display);
    }
    else if (preset == SOLID_BORDER_RIGHT)
    {
        nextView = presetView6(display);
    }
    else if (preset == ROUNDED_BORDER_LEFT)
    {
        nextView = presetView7(display);
    }
    else if (preset == ROUNDED_BORDER_CENTER)
    {
        nextView = presetView8(display);
    }
    else if (preset == ROUNDED_BORDER_RIGHT)
    {
        nextView = presetView9(display);
    }
    else
    {
        display->clearDisplay();
        display->setTextSize(1);
        display->setCursor(0, display->height() / 2 - 4);
        display->print("Unknown View preset.");
        display->display();
        delay(2000);
        return 0; // Retorna 0 para indicar erro
    }

    display->display();

    return nextView;
}

void View::execute(std::function<unsigned int()> execute)
{
    this->exec = execute;
}

void View::nextComponent(unsigned int nextComponent)
{
    this->next = nextComponent;
}

// Preset sem borda, alinhado à esquerda
unsigned int View::presetView1(Adafruit_SSD1306 *display)
{
    display->clearDisplay();
    int startIndex = DisplayManager::selectedItem;
    startIndex = constrain(startIndex, 0, text.size() - maxVisibleLines);

    int spacing = 10;
    int yOffset = 8;                         // Posição inicial para a primeira linha
    int maxLineWidth = display->width() - 8; // Largura máxima para o texto (considerando margens)

    for (int i = 0; i < maxVisibleLines && (startIndex + i) < text.size(); ++i)
    {
        String line = text[startIndex + i];
        int16_t x1, y1;
        uint16_t textWidth, textHeight;

        // Checa a largura do texto
        display->getTextBounds(line.c_str(), 0, 0, &x1, &y1, &textWidth, &textHeight);

        // Enquanto o texto for maior que a largura da tela, divide
        while (textWidth > maxLineWidth)
        {
            // Encontra o ponto de quebra aproximado
            int breakPoint = line.length() / 2;
            while (textWidth > maxLineWidth && breakPoint > 0)
            {
                breakPoint--;
                line = text[startIndex + i].substring(0, breakPoint);
                display->getTextBounds(line.c_str(), 0, 0, &x1, &y1, &textWidth, &textHeight);
            }

            // Exibe a parte quebrada da linha
            display->setTextColor(SSD1306_WHITE);
            display->setCursor(8, yOffset); // Posição inicial de impressão
            display->print(line.c_str());

            // Atualiza o deslocamento para a próxima linha
            yOffset += spacing;

            // A nova linha será o restante do texto
            line = text[startIndex + i].substring(breakPoint);
            display->getTextBounds(line.c_str(), 0, 0, &x1, &y1, &textWidth, &textHeight);
        }

        // Exibe o texto que já coube na tela (se sobrou algo após a divisão)
        if (!line.isEmpty())
        {
            display->setTextColor(SSD1306_WHITE);
            display->setCursor(8, yOffset);
            display->print(line.c_str());
            yOffset += spacing;
        }
    }

    display->display();
    delay(200);

    if (DisplayManager::confirmItem)
    {
        return next;
    }

    return id;
}

// Preset sem borda, centralizado
unsigned int View::presetView2(Adafruit_SSD1306 *display)
{
    display->clearDisplay();
    int startIndex = DisplayManager::selectedItem;
    startIndex = constrain(startIndex, 0, text.size() - maxVisibleLines);

    int spacing = 10;
    int startY = (display->height() - (maxVisibleLines * spacing)) / 2; // Centraliza verticalmente
    for (int i = 0; i < maxVisibleLines && (startIndex + i) < text.size(); ++i)
    {
        display->setTextColor(SSD1306_WHITE);
        int16_t x1, y1;
        uint16_t textWidth, textHeight;
        display->getTextBounds(text[startIndex + i].c_str(), 0, 0, &x1, &y1, &textWidth, &textHeight);
        int startX = (display->width() - textWidth) / 2; // Centraliza horizontalmente
        display->setCursor(startX, startY + i * spacing);
        display->print(text[startIndex + i].c_str());
    }

    display->display();
    delay(200);

    if (DisplayManager::confirmItem)
    {
        return next;
    }

    return id;
}

// Preset sem borda, alinhado à direita
unsigned int View::presetView3(Adafruit_SSD1306 *display)
{
    display->clearDisplay();
    int startIndex = DisplayManager::selectedItem;
    startIndex = constrain(startIndex, 0, text.size() - maxVisibleLines);

    int spacing = 10;
    int startY = (display->height() - (maxVisibleLines * spacing)) / 2; // Centraliza verticalmente
    for (int i = 0; i < maxVisibleLines && (startIndex + i) < text.size(); ++i)
    {
        display->setTextColor(SSD1306_WHITE);
        int16_t x1, y1;
        uint16_t textWidth, textHeight;
        display->getTextBounds(text[startIndex + i].c_str(), 0, 0, &x1, &y1, &textWidth, &textHeight);
        int startX = display->width() - textWidth - 8; // Alinha à direita
        display->setCursor(startX, startY + i * spacing);
        display->print(text[startIndex + i].c_str());
    }

    display->display();
    delay(200);

    if (DisplayManager::confirmItem)
    {
        return next;
    }

    return id;
}

// Preset com borda, alinhado à esquerda
unsigned int View::presetView4(Adafruit_SSD1306 *display)
{
    display->clearDisplay();
    int startIndex = DisplayManager::selectedItem;
    startIndex = constrain(startIndex, 0, text.size() - maxVisibleLines);

    display->drawRect(0, 0, display->width(), display->height(), SSD1306_WHITE); // Borda simples
    int spacing = 10;
    for (int i = 0; i < maxVisibleLines && (startIndex + i) < text.size(); ++i)
    {
        display->setTextColor(SSD1306_WHITE);
        display->setCursor(8, i * spacing + 8); // Espaçamento lateral e superior
        display->print(text[startIndex + i].c_str());
    }

    display->display();
    delay(200);

    if (DisplayManager::confirmItem)
    {
        return next;
    }

    return id;
}

// Preset com borda, centralizado
unsigned int View::presetView5(Adafruit_SSD1306 *display)
{
    display->clearDisplay();
    int startIndex = DisplayManager::selectedItem;
    startIndex = constrain(startIndex, 0, text.size() - maxVisibleLines);

    display->drawRect(0, 0, display->width(), display->height(), SSD1306_WHITE); // Borda simples
    int spacing = 10;
    int startY = (display->height() - (maxVisibleLines * spacing)) / 2; // Centraliza verticalmente
    for (int i = 0; i < maxVisibleLines && (startIndex + i) < text.size(); ++i)
    {
        display->setTextColor(SSD1306_WHITE);
        int16_t x1, y1;
        uint16_t textWidth, textHeight;
        display->getTextBounds(text[startIndex + i].c_str(), 0, 0, &x1, &y1, &textWidth, &textHeight);
        int startX = (display->width() - textWidth) / 2; // Centraliza horizontalmente
        display->setCursor(startX, startY + i * spacing);
        display->print(text[startIndex + i].c_str());
    }

    display->display();
    delay(200);

    if (DisplayManager::confirmItem)
    {
        return next;
    }

    return id;
}

// Preset com borda, alinhado à direita
unsigned int View::presetView6(Adafruit_SSD1306 *display)
{
    display->clearDisplay();
    int startIndex = DisplayManager::selectedItem;
    startIndex = constrain(startIndex, 0, text.size() - maxVisibleLines);

    display->drawRect(0, 0, display->width(), display->height(), SSD1306_WHITE); // Borda simples
    int spacing = 10;
    int startY = (display->height() - (maxVisibleLines * spacing)) / 2; // Centraliza verticalmente
    for (int i = 0; i < maxVisibleLines && (startIndex + i) < text.size(); ++i)
    {
        display->setTextColor(SSD1306_WHITE);
        int16_t x1, y1;
        uint16_t textWidth, textHeight;
        display->getTextBounds(text[startIndex + i].c_str(), 0, 0, &x1, &y1, &textWidth, &textHeight);
        int startX = display->width() - textWidth - 8; // Alinha à direita
        display->setCursor(startX, startY + i * spacing);
        display->print(text[startIndex + i].c_str());
    }

    display->display();
    delay(200);

    if (DisplayManager::confirmItem)
    {
        return next;
    }

    return id;
}

// Preset com borda arredondada, alinhado à esquerda
unsigned int View::presetView7(Adafruit_SSD1306 *display)
{
    display->clearDisplay();
    int startIndex = DisplayManager::selectedItem;
    startIndex = constrain(startIndex, 0, text.size() - maxVisibleLines);

    display->drawRoundRect(0, 0, display->width(), display->height(), 8, SSD1306_WHITE); // Borda arredondada
    int spacing = 10;
    for (int i = 0; i < maxVisibleLines && (startIndex + i) < text.size(); ++i)
    {
        display->setTextColor(SSD1306_WHITE);
        display->setCursor(8, i * spacing + 8); // Espaçamento lateral e superior
        display->print(text[startIndex + i].c_str());
    }

    display->display();
    delay(200);

    if (DisplayManager::confirmItem)
    {
        return next;
    }

    return id;
}

// Preset com borda arredondada, centralizado
unsigned int View::presetView8(Adafruit_SSD1306 *display)
{
    display->clearDisplay();
    int startIndex = DisplayManager::selectedItem;
    startIndex = constrain(startIndex, 0, text.size() - maxVisibleLines);

    display->drawRoundRect(0, 0, display->width(), display->height(), 8, SSD1306_WHITE); // Borda arredondada
    int spacing = 10;
    int startY = (display->height() - (maxVisibleLines * spacing)) / 2; // Centraliza verticalmente
    for (int i = 0; i < maxVisibleLines && (startIndex + i) < text.size(); ++i)
    {
        display->setTextColor(SSD1306_WHITE);
        int16_t x1, y1;
        uint16_t textWidth, textHeight;
        display->getTextBounds(text[startIndex + i].c_str(), 0, 0, &x1, &y1, &textWidth, &textHeight);
        int startX = (display->width() - textWidth) / 2; // Centraliza horizontalmente
        display->setCursor(startX, startY + i * spacing);
        display->print(text[startIndex + i].c_str());
    }

    display->display();
    delay(200);

    if (DisplayManager::confirmItem)
    {
        return next;
    }

    return id;
}

// Preset com borda arredondada, alinhado à direita
unsigned int View::presetView9(Adafruit_SSD1306 *display)
{
    display->clearDisplay();
    int startIndex = DisplayManager::selectedItem;
    startIndex = constrain(startIndex, 0, text.size() - maxVisibleLines);

    display->drawRoundRect(0, 0, display->width(), display->height(), 8, SSD1306_WHITE); // Borda arredondada
    int spacing = 10;
    int startY = (display->height() - (maxVisibleLines * spacing)) / 2; // Centraliza verticalmente
    for (int i = 0; i < maxVisibleLines && (startIndex + i) < text.size(); ++i)
    {
        display->setTextColor(SSD1306_WHITE);
        int16_t x1, y1;
        uint16_t textWidth, textHeight;
        display->getTextBounds(text[startIndex + i].c_str(), 0, 0, &x1, &y1, &textWidth, &textHeight);
        int startX = display->width() - textWidth - 8; // Alinha à direita
        display->setCursor(startX, startY + i * spacing);
        display->print(text[startIndex + i].c_str());
    }

    display->display();
    delay(200);

    if (DisplayManager::confirmItem)
    {
        return next;
    }

    return id;
}
