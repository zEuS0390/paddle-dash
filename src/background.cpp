#include <SFML/Graphics.hpp>
#include "background.hpp"
#include "constants.hpp"

Background::Background (sf::RenderWindow& renderWin, sf::Vector2f initPos)
:       pos(initPos), 
        renderWin(renderWin) 
{
        init();
}

void Background::init () 
{
        if (!image.loadFromFile(constants::IMAGE_GAMEPLAY_BACKGROUND)) return;
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setOrigin(texture.getSize().x/2.0f, texture.getSize().y/2.0f);
        sprite.setPosition(pos);
}

void Background::update () 
{
        sprite.setTexture(texture);
}

void Background::render () 
{
        renderWin.draw(sprite);
}
