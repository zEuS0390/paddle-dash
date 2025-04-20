#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <vector>
#include <string>
#include <memory>
#include "constants.hpp"
#include "menu.hpp"
#include "funcs.hpp"

button::button (const std::string& str, const sf::Color& buttonColor, const sf::Color& textColor, float textCharSize, const sf::Vector2f& buttonSize, const sf::Vector2f& position)
:   isHovered(false),
    isSelected(false),
    str(str),
    buttonColor(buttonColor),
    textColor(textColor),
    textCharSize(textCharSize),
    buttonSize(buttonSize),
    position(position)
{
    init();
}

void button::init ()
{
    if (!fontObj.loadFromFile(funcs::joinPath(funcs::getExecutableDir(), constants::FONT_FAMILY)))
        throw std::runtime_error(constants::FAILED_TO_LOAD_FILE_ERR + ": '" + constants::FONT_FAMILY + "'");
    buttonObj.setFillColor(buttonColor);
    buttonObj.setSize(buttonSize);
    buttonObj.setOrigin(buttonObj.getSize().x/2.0f, buttonObj.getSize().y/2.0f);
    buttonObj.setPosition(position);
    textObj.setString(str);
    textObj.setFont(fontObj);
    textObj.setFillColor(textColor);
    textObj.setCharacterSize(textCharSize);
    textObj.setOrigin(textObj.getGlobalBounds().width/2.0f, textObj.getGlobalBounds().height/2.0f);
    textObj.setPosition(buttonObj.getPosition());
}

menu::menu (sf::RenderWindow& renderWin, soundManager& sManager)
:   isPlaying(false),
    isMenu(true),
    renderWin(renderWin),
    sManager(sManager)
{
    init();
}

void menu::init ()
{
    if (!gameLogo.loadFromFile(funcs::joinPath(funcs::getExecutableDir(), constants::IMAGE_GAME_LOGO)))
        throw std::runtime_error(constants::FAILED_TO_LOAD_FILE_ERR + ": '" + constants::IMAGE_GAME_LOGO + "'");
    if (!mouseTexture.loadFromFile(funcs::joinPath(funcs::getExecutableDir(), constants::IMAGE_MOUSE_POINTER)))
        throw std::runtime_error(constants::FAILED_TO_LOAD_FILE_ERR + ": '" + constants::IMAGE_MOUSE_POINTER + "'");
    if (!menuBackground.loadFromFile(funcs::joinPath(funcs::getExecutableDir(), constants::IMAGE_MENU_BACKGROUND)))
        throw std::runtime_error(constants::FAILED_TO_LOAD_FILE_ERR + ": '" + constants::IMAGE_MENU_BACKGROUND + "'");
    gameLogoTexture.loadFromImage(gameLogo);
    gameLogoSprite.setTexture(gameLogoTexture);
    mouseSprite.setTexture(mouseTexture);
    mouseSprite.setOrigin(sf::Vector2f(mouseSprite.getGlobalBounds().width/2.0f, mouseSprite.getGlobalBounds().height/2.0f));
    mouseSprite.setPosition(sf::Vector2f(sf::Mouse::getPosition(renderWin).x, sf::Mouse::getPosition(renderWin).y));
    menuTexture.loadFromImage(menuBackground);
    menuSprite.setTexture(menuTexture);
    createButton(menuButtons, "Player vs. CPU", sf::Color(0, 0, 0, 80), sf::Color::White, 40.0f, sf::Vector2f(380.0f, 80.0f), sf::Vector2f(320.0f, 240.0f));
    createButton(menuButtons, "Player vs. Player", sf::Color(0, 0, 0, 80), sf::Color::White, 40.0f, sf::Vector2f(380.0f, 80.0f), sf::Vector2f(320.0f, 330.0f ));
    createButton(menuButtons, "Exit", sf::Color(0, 0, 0, 80), sf::Color::White, 40.0f, sf::Vector2f(380.0f, 80.0f), sf::Vector2f(320.0f, 420.0f));
}

void menu::mouseSelect (std::vector<std::unique_ptr<button>>& listObj, const sf::Color& hoverButtonColor, const sf::Color& hoverTextColor)
{
    sf::Vector2i mousePos = mouse.getPosition(renderWin);
    for (auto iter = listObj.begin(); iter != listObj.end(); iter++)
    {
        button* pButton = iter->get();
        if (mousePos.x > pButton->buttonObj.getGlobalBounds().left &&
            mousePos.x < pButton->buttonObj.getGlobalBounds().left+pButton->buttonObj.getGlobalBounds().width &&
            mousePos.y > pButton->buttonObj.getGlobalBounds().top &&
            mousePos.y < pButton->buttonObj.getGlobalBounds().top+pButton->buttonObj.getGlobalBounds().height)
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                sManager.playAudio("select");
                pButton->isSelected = true;
            }
            else if (pButton->isHovered)
            {
                pButton->buttonObj.setFillColor(hoverButtonColor);
                pButton->textObj.setFillColor(hoverTextColor);
            }
            else
            {
                isPlaying = true;
                pButton->isHovered = true;
            }
        }
        else
        {
            pButton->buttonObj.setFillColor(pButton->buttonColor);
            pButton->textObj.setFillColor(pButton->textColor);
            pButton->isHovered = false;
            pButton->isSelected = false;
        }
    }
    if (isPlaying)
    {
        sManager.playAudio("blip");
        isPlaying = false;
    }
}

std::string menu::checkSelected ()
{
    for (auto iter = menuButtons.begin(); iter != menuButtons.end(); iter++)
    {
        button* pButton = iter->get();
        if (pButton->isSelected)
        {
            pButton->isSelected = false;
            return pButton->str;
        }
    }
    return "";
}

void menu::update ()
{
    mouseSprite.setPosition(sf::Vector2f(sf::Mouse::getPosition(renderWin).x,
                                         sf::Mouse::getPosition(renderWin).y));
    if (isMenu)
        mouseSelect(menuButtons, sf::Color(255, 255, 255, 80), sf::Color::Black);
}

void menu::renderMenu (std::vector<std::unique_ptr<button>>& listObj)
{
    for (auto iter = listObj.begin(); iter != listObj.end(); iter++)
    {
        button* btn = iter->get();
        renderWin.draw(btn->buttonObj);
        renderWin.draw(btn->textObj);
    }
}

void menu::render ()
{
    if (isMenu)
    {
        renderWin.draw(menuSprite);
        renderWin.draw(gameLogoSprite);
        renderMenu(menuButtons);
        renderWin.draw(mouseSprite);
    }
}

void menu::createButton (std::vector<std::unique_ptr<button>>& listObj,
                         const std::string& str,
                         const sf::Color& buttonColor,
                         const sf::Color& textColor,
                         float textCharSize,
                         const sf::Vector2f& buttonSize,
                         const sf::Vector2f& position)
{
    listObj.push_back(std::make_unique<button>(
        str,
        buttonColor,
        textColor,
        textCharSize,
        buttonSize,
        position
    ));
}

