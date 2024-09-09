#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <memory>
#include "sound.hpp"

class button
{
public:
    bool                isHovered;
    bool                isSelected;
    std::string         str;
    sf::Color           buttonColor;
    sf::Color           textColor;
    float               textCharSize;
    sf::Vector2f        buttonSize;
    sf::Vector2f        position;
    button              (const std::string&, const sf::Color&, const sf::Color&, float, const sf::Vector2f&, const sf::Vector2f&);
    void init           ();
public:
    sf::RectangleShape  buttonObj;
    sf::Text            textObj;
    sf::Font            fontObj;
};

// menu class
class menu
{
public:
    bool                                    isPlaying;
    bool                                    isMenu;
    menu                                    (sf::RenderWindow&, soundManager&);
    void init                               ();
    void mouseSelect                        (std::vector<std::unique_ptr<button>>&, const sf::Color&, const sf::Color&);
    std::string checkSelected               ();
    void update                             ();
    void renderMenu                         (std::vector<std::unique_ptr<button>>&);
    void render                             ();
    std::vector<std::unique_ptr<button>>    menuButtons;
private:
    void createButton                       (std::vector<std::unique_ptr<button>>&, const std::string&, const sf::Color&, const sf::Color&, float, const sf::Vector2f&, const sf::Vector2f&);
    sf::Image                               gameLogo;
    sf::Image                               menuBackground;
    sf::Texture                             gameLogoTexture;
    sf::Texture                             menuTexture;
    sf::Texture                             mouseTexture;
    sf::Sprite                              gameLogoSprite;
    sf::Sprite                              menuSprite;
    sf::Sprite                              mouseSprite;
    sf::RenderWindow&                       renderWin;
    soundManager&                           sManager;
    sf::Mouse                               mouse;
};

#endif

