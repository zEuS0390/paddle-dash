#include "background.h"
#include <SFML/Graphics.hpp>

background::background (sf::RenderWindow* renderWin,
                        sf::Vector2f initPos)
:   pos(initPos),
    renderWin(renderWin) {
    init();
}

void background::init (void) {
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

void background::update (void) {
    sprite.setTexture(texture);
    return;
}

void background::render (void) {
    renderWin->draw(sprite);
    return;
}
