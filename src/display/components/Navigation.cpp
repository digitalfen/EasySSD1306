#include "display/components/Navigation.h"
#include "display/DisplayManager.h"

unsigned int Navigation::render(Adafruit_SSD1306 *display)
{
    if (preset == CURSOR_LIST)
    {
        return presetNavigation1(display);
    }
    else if (preset == HIGHLIGHT_LIST)
    {
        return presetNavigation2(display);
    }
    else if (preset == VERTICAL_SELECTOR)
    {
        return presetNavigation3(display);
    }
    else if (preset == HORIZONTAL_SELECTOR)
    {
        return presetNavigation4(display);
    }

    else
    {
        display->clearDisplay();
        display->setTextSize(1);
        display->setCursor(0, display->height() / 2 - 4);
        display->print("Unknown Navigation preset.");
        display->display();
        delay(2000);
        return 0; // Retorna 0 para indicar erro
    }
}

unsigned int Navigation::presetNavigation1(Adafruit_SSD1306 *display)
{
    if (DisplayManager::selectedItem < 0)
    {
        DisplayManager::selectedItem = options.size() - 1; // Vai para o último item
    }
    else if (DisplayManager::selectedItem >= options.size())
    {
        DisplayManager::selectedItem = 0; // Vai para o primeiro item
    }

    display->clearDisplay();

    int maxItemsOnScreen = 5;
    int spacing = 10;
    int startY = (display->height() - (maxItemsOnScreen * spacing)) / 2;

    int startIndex = DisplayManager::selectedItem - (maxItemsOnScreen / 2);
    if (startIndex + maxItemsOnScreen > options.size())
    {
        startIndex = options.size() - maxItemsOnScreen;
    }
    startIndex = max(0, startIndex);

    int endIndex = min((int)options.size(), startIndex + maxItemsOnScreen);

    int index = 0;
    auto it = options.begin();
    std::advance(it, startIndex);
    for (int i = startIndex; i < endIndex; ++i, ++it)
    {
        String name = it->second;

        // Verifica se o nome ultrapassa o limite da tela
        if (name.length() > 19) // 10 caracteres é o limite (ajuste conforme a necessidade)
        {
            name = name.substring(0, 17) + ".."; // Mantém 7 caracteres e adiciona '...'
        }

        if (i == DisplayManager::selectedItem)
        {
            display->setCursor(0, startY + index * spacing);
            display->print(">"); // ">" à esquerda
        }
        else
        {
            display->setTextColor(SSD1306_WHITE); // Cor normal
        }

        display->setCursor(10, startY + index * spacing);
        display->print(name.c_str());

        index++;
    }

    display->display();
    delay(50);

    auto itt = options.begin();
    std::advance(itt, DisplayManager::selectedItem);
    int optionState = itt->first;

    unsigned int nextState = id;

    if (DisplayManager::confirmItem)
    {
        Serial.println(optionState);
        nextState = optionState;
    }

    return nextState;
}

unsigned int Navigation::presetNavigation2(Adafruit_SSD1306 *display)
{
    if (DisplayManager::selectedItem < 0)
    {
        DisplayManager::selectedItem = options.size() - 1;
    }
    else if (DisplayManager::selectedItem >= options.size())
    {
        DisplayManager::selectedItem = 0;
    }

    display->clearDisplay();

    int maxItemsOnScreen = 5;
    int spacing = 10;
    int startY = (display->height() - (maxItemsOnScreen * spacing)) / 2;

    int startIndex = DisplayManager::selectedItem - (maxItemsOnScreen / 2);
    if (startIndex + maxItemsOnScreen > options.size())
    {
        startIndex = options.size() - maxItemsOnScreen;
    }
    startIndex = max(0, startIndex);

    int endIndex = min((int)options.size(), startIndex + maxItemsOnScreen);

    int index = 0;
    auto it = options.begin();
    std::advance(it, startIndex);
    for (int i = startIndex; i < endIndex; ++i, ++it)
    {
        String name = it->second;

        // Verifica se o nome ultrapassa o limite da tela
        if (name.length() > 19) // 10 caracteres é o limite (ajuste conforme a necessidade)
        {
            name = name.substring(0, 17) + "..."; // Mantém 7 caracteres e adiciona '...'
        }

        if (i == DisplayManager::selectedItem)
        {
            display->setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Cor invertida
            display->setCursor(0, startY + index * spacing);
            display->print(" "); // ">" à esquerda
        }
        else
        {
            display->setTextColor(SSD1306_WHITE); // Cor normal
        }

        display->setCursor(10, startY + index * spacing);
        display->print(name.c_str());

        index++;
    }

    display->display();
    delay(50);

    auto itt = options.begin();
    std::advance(itt, DisplayManager::selectedItem);
    int optionState = itt->first;

    unsigned int nextState = id;

    if (DisplayManager::confirmItem)
    {
        Serial.println(optionState);
        nextState = optionState;
    }

    return nextState;
}

unsigned int Navigation::presetNavigation3(Adafruit_SSD1306 *display)
{
    if (DisplayManager::selectedItem < 0)
    {
        DisplayManager::selectedItem = options.size() - 1; // Vai para o último item
    }
    else if (DisplayManager::selectedItem >= options.size())
    {
        DisplayManager::selectedItem = 0; // Vai para o primeiro item
    }

    display->clearDisplay(); // Limpa a tela antes de desenhar o Navigation

    int maxItemsOnScreen = 1; // Apenas um item será centralizado
    int spacing = 12;         // Espaçamento entre os itens
    int startY = (display->height() - (maxItemsOnScreen * spacing)) / 2;

    // Define a faixa de itens a serem exibidos
    int startIndex = DisplayManager::selectedItem;
    int endIndex = startIndex + 1;

    // Desenha as opções no centro
    auto it = options.begin();
    std::advance(it, startIndex); // Avança até o item selecionado
    String name = it->second;     // Nome do item

    // Verifica se o nome ultrapassa o limite da tela
    if (name.length() > 19) // 10 caracteres é o limite (ajuste conforme a necessidade)
    {
        name = name.substring(0, 17) + "..."; // Mantém 7 caracteres e adiciona '...'
    }

    // Exibe o item atual
    display->setTextColor(SSD1306_WHITE);
    display->setCursor(20, startY);
    display->print(name.c_str());

    // Se houver mais itens acima ou abaixo, exibe setas
    if (startIndex > 0)
    {
        display->setTextColor(SSD1306_WHITE);
        display->setCursor(0, startY - 20); // Acima
        display->print("/\\");
    }
    if (startIndex < options.size() - 1)
    {
        display->setTextColor(SSD1306_WHITE);
        display->setCursor(0, startY + 20); // Abaixo
        display->print("\\/");
    }

    display->display(); // Atualiza a tela
    delay(150);         // Delay para animação

    auto itt = options.begin();
    std::advance(itt, DisplayManager::selectedItem);
    int optionState = itt->first;

    unsigned int nextState = id;

    if (DisplayManager::confirmItem)
    {
        Serial.println(optionState);
        nextState = optionState;
    }

    return nextState;
}

unsigned int Navigation::presetNavigation4(Adafruit_SSD1306 *display)
{
    if (DisplayManager::selectedItem < 0)
    {
        DisplayManager::selectedItem = options.size() - 1; // Vai para o último item
    }
    else if (DisplayManager::selectedItem >= options.size())
    {
        DisplayManager::selectedItem = 0; // Vai para o primeiro item
    }

    display->clearDisplay(); // Limpa a tela antes de desenhar o Navigation

    // Define a faixa de itens a serem exibidos
    int startIndex = DisplayManager::selectedItem;

    // Obtém o nome do item selecionado
    auto it = options.begin();
    std::advance(it, startIndex);
    String name = it->second; // Nome do item

    // Verifica se o nome ultrapassa o limite da tela
    if (name.length() > 19) // 10 caracteres é o limite (ajuste conforme a necessidade)
    {
        name = name.substring(0, 17) + "..."; // Mantém 7 caracteres e adiciona '...'
    }

    // Calcula a largura do texto para centralização horizontal
    int16_t x1, y1;
    uint16_t textWidth, textHeight;
    display->getTextBounds(name.c_str(), 0, 0, &x1, &y1, &textWidth, &textHeight);

    // Centraliza o texto horizontalmente
    int centerX = (display->width() - textWidth) / 2;

    // Exibe o item atual
    display->setTextColor(SSD1306_WHITE);
    display->setCursor(centerX, 20);
    display->print(name.c_str());

    // Se houver mais itens à esquerda ou direita, exibe setas
    if (startIndex > 0)
    {
        display->setTextColor(SSD1306_WHITE);
        display->setCursor(10, 20); // Esquerda
        display->print("<");
    }
    if (startIndex < options.size() - 1)
    {
        display->setTextColor(SSD1306_WHITE);
        display->setCursor(display->width() - 10, 20); // Direita
        display->print(">");
    }

    display->display(); // Atualiza a tela
    delay(150);         // Delay para animação

    auto itt = options.begin();
    std::advance(itt, DisplayManager::selectedItem);
    int optionState = itt->first;

    unsigned int nextState = id;

    if (DisplayManager::confirmItem)
    {
        Serial.println(optionState);
        nextState = optionState;
    }
    return nextState;
}
