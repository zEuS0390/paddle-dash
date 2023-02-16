#include "background.h"
#include <SFML/Graphics.hpp>

Background::Background (sf::RenderWindow* renderWin,
                        sf::Vector2f initPos)
:   pos(initPos),
    renderWin(renderWin) {
    init();
}

void Background::init (void) {
    if (!image.loadFromFile("gfx/background.png")) {
        return;
    }
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x/2.0f,
                     texture.getSize().y/2.0f);
    sprite.setPosition(pos);
    return;
}

void Background::update (void) {
    sprite.setTexture(texture);
    return;
}

void Background::render (void) {
    renderWin->draw(sprite);
    return;
}
