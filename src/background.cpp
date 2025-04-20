#include <SFML/Graphics.hpp>
#include <stdexcept>
#include "background.hpp"
#include "constants.hpp"
#include "funcs.hpp"

Background::Background (sf::RenderWindow& renderWin, sf::Vector2f initPos)
:   pos(initPos),
    renderWin(renderWin)
{
    init();
}

void Background::init ()
{
    if (!image.loadFromFile(funcs::joinPath(funcs::getExecutableDir(), constants::IMAGE_GAMEPLAY_BACKGROUND)))
        throw std::runtime_error(constants::FAILED_TO_LOAD_FILE_ERR + ": '" + constants::IMAGE_GAMEPLAY_BACKGROUND + "'") ;
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

