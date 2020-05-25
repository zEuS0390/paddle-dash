#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "players.h"
#include "sound.h"

player::player (std::string id,
                std::string filepath,
                std::string shadowfilepath,
                sf::Vector2f initPos,
                soundManager* sManager)
:   id(id),
    filepath(filepath),
    shadowfilepath(shadowfilepath),
    score(0),
    isMoving(true),
    isPlaying(false),
    speed(40.0f),
    velY(0.0f),
    accY(0.0f),
    fric(-0.9f),
    initPos(initPos),
    currPos(initPos),
    dir{false, false},
    sManager(sManager) {
    init();
}

void player::init (void) {
    if (!texture.loadFromFile(filepath)) {
        return;
    }
    if (!shadowTex.loadFromFile(shadowfilepath)) {
        return;
    }
    shadow.setTexture(shadowTex);
    shadow.setOrigin(shadowTex.getSize().x/2.0f,
                     shadowTex.getSize().y/2.0f);
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x/2.0f,
                     texture.getSize().y/2.0f);
    sprite.setPosition(currPos);
    setSides();
    return;
}

void player::movement (void) {
    float elapsedTime = clock.getElapsedTime().asSeconds();
    if (dir.up) {
        if (!isPlaying) {
            sManager->playAudio("player-move");
            isPlaying = true;
        }
        accY = -speed;
    } else if (dir.down) {
        if (!isPlaying) {
            sManager->playAudio("player-move");
            isPlaying = true;
        }
        accY = speed;
    } else {
        accY = velY * fric;
    }
    velY += accY;
    currPos.y += velY * elapsedTime + 0.5 * accY * std::pow(elapsedTime, 2);
    sprite.setPosition(currPos);
    if (id == "player1") {
        shadow.setPosition(sf::Vector2f(sprite.getPosition().x-sprite.getGlobalBounds().width/4.0f,
                                        sprite.getPosition().y));
    } else if (id == "player2") {
        shadow.setPosition(sf::Vector2f(sprite.getPosition().x+sprite.getGlobalBounds().width/4.0f,
                                        sprite.getPosition().y));
    }
    return;
}

void player::collision (void) {
    if (side.top <= 0.0f) {
        velY = 0.0f;
        currPos.y = currPos.y + 1;
        dir.up = false;
    } else if (side.bottom >= 480.0f) {
        velY = 0.0f;
        currPos.y = currPos.y - 1;
        dir.down = false;
    }
    return;
}

void player::restartPos (void) {
    currPos = initPos;
    return;
}

void player::update (void) {
    shadow.setTexture(shadowTex);
    sprite.setTexture(texture);
    setSides();
    if (isMoving) {
        collision();
        movement();
    }
    clock.restart();
    return;
}

void player::setSides (void) {
    side = {sprite.getGlobalBounds().top,
            sprite.getGlobalBounds().top+texture.getSize().y,
            sprite.getGlobalBounds().left,
            sprite.getGlobalBounds().left+texture.getSize().x};
    return;
}

players::players (sf::RenderWindow* renderWin,
                  soundManager* sManager)
:   renderWin(renderWin),
    sManager(sManager) {
    init();
}

players::~players (void) {
    playersVec.clear();
}

void players::init (void) {
    playersVec.push_back(player("player1",
                                "gfx/player1.png",
                                "gfx/player-shadow.png",
                                sf::Vector2f(50.0f, 240.0f),
                                sManager));
    playersVec.push_back(player("player2",
                                "gfx/player2.png",
                                "gfx/player-shadow.png",
                                sf::Vector2f(590.0f, 240.0f),
                                sManager));
    return;
}

void players::setScore (std::string id, int score) {
    for (unsigned int i = 0; i < playersVec.size(); i++) {
        if (id == playersVec.at(i).id) {
            playersVec.at(i).score += score;
        }
    }
    return;
}

void players::resetScore (void) {
    for (unsigned int i = 0; i < playersVec.size(); i++) {
        playersVec.at(i).score = 0;
    }
    return;
}

void players::move (std::string id, std::string dir) {
    for (unsigned int i = 0; i < playersVec.size(); i++) {
        if (id == playersVec.at(i).id) {
            if (dir == "up") {
                playersVec.at(i).dir = {true, false};
            } else if (dir == "down"){
                playersVec.at(i).dir = {false, true};
            }
        }
    }
    return;
}

void players::stop (std::string id) {
    for (unsigned int i = 0; i < playersVec.size(); i++) {
        if (id == playersVec.at(i).id) {
            playersVec.at(i).dir = {false, false};
        }
    }
    return;
}

void players::pause (void) {
    for (unsigned int i = 0; i < playersVec.size(); i++) {
        playersVec.at(i).isMoving = false;
        stop(playersVec.at(i).id);
    }
}

void players::resume (void) {
    for (unsigned int i = 0; i < playersVec.size(); i++) {
        playersVec.at(i).isMoving = true;
    }
}

void players::restart (void) {
    resetScore();
    for (unsigned int i = 0; i < playersVec.size(); i++) {
        playersVec.at(i).restartPos();
    }
    return;
}

void players::events (void) {
    stop("player1");
    stop("player2");
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        move("player1", "up");
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        move("player1", "down");
    } else {
        playersVec.at(0).isPlaying = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        move("player2", "up");
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        move("player2", "down");
    } else {
        playersVec.at(1).isPlaying = false;
    }
    return;
}

void players::updates (void) {
    for (unsigned int i = 0; i < playersVec.size(); i++) {
        playersVec.at(i).update();
    }
    return;
}

void players::renders (void) {
    for (unsigned int i = 0; i < playersVec.size(); i++) {
        renderWin->draw(playersVec.at(i).shadow);
        renderWin->draw(playersVec.at(i).sprite);
    }
    return;
}
