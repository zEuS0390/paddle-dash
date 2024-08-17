#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SFML/Graphics.hpp>

// background class
class Background 
{
public:
        Background          (sf::RenderWindow&, sf::Vector2f);
        void init           ();
        void update         ();
        void render         ();
private:
        sf::Vector2f        pos;
        sf::Image           image;
        sf::Texture         texture;
        sf::Sprite          sprite;
        sf::RenderWindow&   renderWin;
};

#endif
