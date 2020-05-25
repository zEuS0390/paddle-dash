#include <SFML/Graphics.hpp>
#include <string>
#include "menu.h"

button::button (std::string str,
                sf::Color buttonColor,
                sf::Color textColor,
                float textCharSize,
                sf::Vector2f buttonSize,
                sf::Vector2f position)
:   isHovered(false),
    isSelected(false),
    str(str),
    buttonColor(buttonColor),
    textColor(textColor),
    textCharSize(textCharSize),
    buttonSize(buttonSize),
    position(position) {
    init();
}

void button::init (void) {
    if (!fontObj.loadFromFile("gfx/font/november.ttf")) {
        return;
    }
    buttonObj.setFillColor(buttonColor);
    buttonObj.setSize(buttonSize);
    buttonObj.setOrigin(buttonObj.getSize().x/2.0f,
                        buttonObj.getSize().y/2.0f);
    buttonObj.setPosition(position);
    textObj.setString(str);
    textObj.setFont(fontObj);
    textObj.setFillColor(textColor);
    textObj.setCharacterSize(textCharSize);
    textObj.setOrigin(textObj.getGlobalBounds().width/2.0f,
                      textObj.getGlobalBounds().height/2.0f);
    textObj.setPosition(buttonObj.getPosition());
}

menu::menu (sf::RenderWindow* renderWin,
            soundManager* sManager)
:   isPlaying(false),
    isMenu(true),
    renderWin(renderWin),
    sManager(sManager) {
    init();
}

void menu::init (void) {
    if (!gameLogo.loadFromFile("gfx/game-logo.png")) {
        return;
    }
    if (!mouseTexture.loadFromFile("gfx/mouse-pointer.png")) {
        return;
    }
    if (!menuBackground.loadFromFile("gfx/menu-background.png")) {
        return;
    }
    gameLogoTexture.loadFromImage(gameLogo);
    gameLogoSprite.setTexture(gameLogoTexture);
    mouseSprite.setTexture(mouseTexture);
    mouseSprite.setOrigin(sf::Vector2f(mouseSprite.getGlobalBounds().width/2.0f,
                                       mouseSprite.getGlobalBounds().height/2.0f));
    mouseSprite.setPosition(sf::Vector2f(sf::Mouse::getPosition(*renderWin).x,
                                         sf::Mouse::getPosition(*renderWin).y));
    menuTexture.loadFromImage(menuBackground);
    menuSprite.setTexture(menuTexture);
    createButton(menuButtons,
                 "Player vs. CPU",
                 sf::Color(0, 0, 0, 80),
                 sf::Color::White,
                 40.0f,
                 sf::Vector2f(380.0f, 80.0f),
                 sf::Vector2f(320.0f, 240.0f));
    createButton(menuButtons,
                  "Player vs. Player",
                  sf::Color(0, 0, 0, 80),
                  sf::Color::White,
                  40.0f,
                  sf::Vector2f(380.0f, 80.0f),
                  sf::Vector2f(320.0f, 330.0f ));
    createButton(menuButtons,
                 "Exit",
                 sf::Color(0, 0, 0, 80),
                 sf::Color::White,
                 40.0f,
                 sf::Vector2f(380.0f, 80.0f),
                 sf::Vector2f(320.0f, 420.0f));
    return;
}

template <class T>
void menu::mouseSelect (std::list<T*> listObj,
                           sf::Color hoverButtonColor,
                           sf::Color hoverTextColor) {
    sf::Vector2i mousePos = mouse.getPosition(*renderWin);
    for (auto iter = listObj.begin();
         iter != listObj.end();
         iter++) {
        button* pButton = *iter;
        if (mousePos.x > pButton->buttonObj.getGlobalBounds().left &&
            mousePos.x < pButton->buttonObj.getGlobalBounds().left+pButton->buttonObj.getGlobalBounds().width &&
            mousePos.y > pButton->buttonObj.getGlobalBounds().top &&
            mousePos.y < pButton->buttonObj.getGlobalBounds().top+pButton->buttonObj.getGlobalBounds().height) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sManager->playAudio("select");
                pButton->isSelected = true;
            } else if (pButton->isHovered) {
                pButton->buttonObj.setFillColor(hoverButtonColor);
                pButton->textObj.setFillColor(hoverTextColor);
            } else {
                isPlaying = true;
                pButton->isHovered = true;
            }
        } else {
            pButton->buttonObj.setFillColor(pButton->buttonColor);
            pButton->textObj.setFillColor(pButton->textColor);
            pButton->isHovered = false;
            pButton->isSelected = false;
        }
    }
    if (isPlaying) {
        sManager->playAudio("blip");
        isPlaying = false;
    }
    return;
}

std::string menu::checkSelected (void) {
    for (auto iter = menuButtons.begin();
         iter != menuButtons.end();
         iter++) {
        button* pButton = *iter;
        if (pButton->isSelected) {
            pButton->isSelected = false;
            return pButton->str;
        }
    }
    return "";
}

void menu::update (void) {
    mouseSprite.setPosition(sf::Vector2f(sf::Mouse::getPosition(*renderWin).x,
                                         sf::Mouse::getPosition(*renderWin).y));
    if (isMenu)
        mouseSelect(menuButtons, sf::Color(255, 255, 255, 80), sf::Color::Black);
    return;
}

template <class T>
void menu::renderMenu (std::list<T*> listObj) {
    for (auto iter = listObj.begin();
         iter != listObj.end();
         iter++) {
        button* buttonObj = *iter;
        renderWin->draw(buttonObj->buttonObj);
        renderWin->draw(buttonObj->textObj);
    }
    return;
}

void menu::render (void) {
    if (isMenu) {
        renderWin->draw(menuSprite);
        renderWin->draw(gameLogoSprite);
        renderMenu(menuButtons);
        renderWin->draw(mouseSprite);
    }
    return;
}

template <class T>
void menu::createButton (std::list<T*>& listObj,
                         std::string str,
                         sf::Color buttonColor,
                         sf::Color textColor,
                         float textCharSize,
                         sf::Vector2f buttonSize,
                         sf::Vector2f position) {
    button* buttonObj = new button(str,
                                   buttonColor,
                                   textColor,
                                   textCharSize,
                                   buttonSize,
                                   position);
    listObj.push_back(buttonObj);
    return;
}
