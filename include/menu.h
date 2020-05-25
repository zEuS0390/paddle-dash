#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics.hpp>
#include <string>
#include <list>
#include "sound.h"

class button {
    public:
        bool                                isHovered;
        bool                                isSelected;
        std::string                         str;
        sf::Color                           buttonColor;
        sf::Color                           textColor;
        float                               textCharSize;
        sf::Vector2f                        buttonSize;
        sf::Vector2f                        position;
    public:
        button                              (std::string,
                                             sf::Color,
                                             sf::Color,
                                             float,
                                             sf::Vector2f,
                                             sf::Vector2f);
    private:
        void init                           (void);
    public:
        sf::RectangleShape                  buttonObj;
        sf::Text                            textObj;
        sf::Font                            fontObj;
};

// menu class
class menu {
    public:
        bool                                isPlaying;
        bool                                isMenu;
    public:
        menu                                (sf::RenderWindow*,
                                             soundManager*);
    public:
        void init                           (void);
        template <class T>
        void mouseSelect                    (std::list<T*>,
                                             sf::Color,
                                             sf::Color);
        std::string checkSelected           (void);
        void update                         (void);
        template <class T>
        void renderMenu                     (std::list<T*>);
        void render                         (void);
    public:
        std::list<button*>                  menuButtons;
    private:
        template <class T>
        void createButton                   (std::list<T*>&,
                                             std::string,
                                             sf::Color,
                                             sf::Color,
                                             float,
                                             sf::Vector2f,
                                             sf::Vector2f);
    private:
        sf::Image                           gameLogo;
        sf::Image                           menuBackground;
        sf::Texture                         gameLogoTexture;
        sf::Texture                         menuTexture;
        sf::Texture                         mouseTexture;
        sf::Sprite                          gameLogoSprite;
        sf::Sprite                          menuSprite;
        sf::Sprite                          mouseSprite;
\
    private:
        sf::RenderWindow*                   renderWin;
        soundManager*                       sManager;
        sf::Mouse                           mouse;
};

#endif
