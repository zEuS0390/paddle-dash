#include <SFML/Graphics.hpp>
#include <random>
#include <ctime>
#include <cmath>
#include "pongball.h"
#include "players.h"
#include "sound.h"
#include "rect.h"

// Main constructor of the pongball class
Pongball::Pongball (sf::RenderWindow* renderWin,
                    players* cplayers,
                    soundManager* sManager)
:   effectActive(false),
    isCounting(false),
    isMoving(false),
    constSpeed(500.0f),
    maxSpeed(600.0f),
    speed(constSpeed),
    acc(1.0f),
    counterVar(0.0f),
    sManager(sManager),
    eng(time(NULL)),
    renderWin(renderWin),
    cplayers(cplayers) {
    init();
}

// Main deconstructor of the pong ball class
Pongball::~Pongball (void) {
}

// Initialization of pong ball
void Pongball::init (void) {
    if (!texture.loadFromFile("gfx/pongball.png")) {
        return;
    }
    if (!effectTex.loadFromFile("gfx/explode.png")) {
        return;
    }
    effectSp.setTexture(effectTex);
    effectRect = sf::IntRect(0, 0, 32, 32);
    effectSp.setTextureRect(effectRect);
    effectSp.setOrigin(effectSp.getGlobalBounds().width/2.0f,
                       effectSp.getGlobalBounds().height/2.0f);
    effectSp.setPosition(effectPos);
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x/2.0f,
                     texture.getSize().y/2.0f);
    currPos = sf::Vector2f(320.0f, 240.0f);
    sprite.setPosition(currPos);
    randomAngle(0, 45.0f);
    randomPos();
    vertex1.color = sf::Color(255, 255, 0, 200);
    vertex2.color = sf::Color(255, 255, 0, 200);
    isMoving = false;
    return;
}

void Pongball::hitExplode (void) {
    if (effectActive) {
        if (effectClock.getElapsedTime().asSeconds() >= 0.09f) {
            if (effectRect.left == 160) {
                effectRect.left = 0;
                effectActive = false;
            } else {
                effectRect.left += 32;
            }
            effectSp.setTextureRect(effectRect);
            effectClock.restart();
        }
    } else {
        effectClock.restart();
    }
    return;
}

// Handles movemenr
void Pongball::movement (void) {
    float deltaTime = clock.getElapsedTime().asSeconds();
    if (speed <= maxSpeed && speed >= constSpeed) {
        speed += acc;
    }
    pos.x = speed * std::cos(ballAngle * M_PI/180.0f);
    pos.y = speed * std::sin(ballAngle * M_PI/180.0f);
    currPos = sprite.getPosition();
    sprite.setPosition(currPos.x + pos.x * deltaTime, currPos.y + pos.y * deltaTime);
    nextPos();
    return;
}

void Pongball::nextPos (void) {
    float player1X = currPos.x-cplayers->playersVec.at(0).side.left;
    float player1R = player1X / std::cos(ballAngle * M_PI/180);
    float player1Y = player1R * std::sin(ballAngle * M_PI/180);
    float player1BPoint = currPos.y-player1Y;
    float player2X = cplayers->playersVec.at(1).side.left-currPos.x;
    float player2R = player2X / std::cos(ballAngle * M_PI/180);
    float player2Y = player2R * std::sin(ballAngle * M_PI/180);
    float player2BPoint = currPos.y+player2Y;

    if (player1BPoint > 480 || player1BPoint < 0) {
        player1R = player1X / std::cos((360 - ballAngle) * M_PI/180);
        player1Y = player1R * std::sin((360 - ballAngle) * M_PI/180);
        if (player1BPoint > 480) {
            player1BPoint = (480-currPos.y)+(480-player1Y);
        } else {
            player1BPoint = std::abs(player1Y+currPos.y);
        }
    } else if (player2BPoint > 480 || player2BPoint < 0) {
        player2R = player2X / std::cos((360 - ballAngle) * M_PI/180);
        player2Y = player2R * std::sin((360 - ballAngle) * M_PI/180);
        if (player2BPoint > 480) {
            player2BPoint = (480+player2Y)+(480-currPos.y);
        } else if (player2BPoint < 0) {
            player2BPoint = player2Y-currPos.y;
        }
    }
    vertex1.position = sf::Vector2f(585, player2BPoint);
    vertex2.position = sf::Vector2f(55, player1BPoint);
    return;
}

// Handles screen collision
void Pongball::collision (void) {
    if (currPos.x > 640.0f) {
        isCounting = true;
        speed = -constSpeed;
        restart();
        sManager->playAudio("player1-scores");
        cplayers->setScore("player1", 1);
    } else if (currPos.x < 0.0f) {
        isCounting = true;
        speed = constSpeed;
        restart();
        sManager->playAudio("player2-scores");
        cplayers->setScore("player2", 1);
    } else if (currPos.y > 480.0f) {
        sManager->playAudio("table");
        sprite.setPosition(currPos.x, currPos.y-texture.getSize().y/2.0f);
        ballAngle = 360.0f - ballAngle;
    } else if (currPos.y < 0.0f) {
        sManager->playAudio("table");
        sprite.setPosition(currPos.x, currPos.y+texture.getSize().y/2.0f);
        ballAngle = 360.0f - ballAngle;
    }
    paddleCollide();
    return;
}

void Pongball::paddleCollide (void) {
    for (unsigned int i = 0; i < cplayers->playersVec.size(); i++) {
        float top = cplayers->playersVec.at(i).side.top;
        float bottom = cplayers->playersVec.at(i).side.bottom;
        float left = cplayers->playersVec.at(i).side.left;
        float right = cplayers->playersVec.at(i).side.right;
        if (side.left > left &&
            side.right < right) {
            if (side.bottom > top &&
                side.top < top) {
                if (cplayers->playersVec.at(i).dir.up) {
                    sprite.setPosition(currPos.x, cplayers->playersVec.at(i).side.top-sprite.getGlobalBounds().height/2.0f);
                } else {
                    sprite.setPosition(currPos.x, currPos.y-sprite.getGlobalBounds().height/2.0f);
                }
                effectSp.setPosition(currPos);
                effectActive = true;
                sManager->playAudio("pong");
                randomAngle(360.0f-ballAngle-20.0f, 360.0f-ballAngle);
            } else if (side.top < bottom &&
                side.bottom > bottom) {
                if (cplayers->playersVec.at(i).dir.down) {
                    sprite.setPosition(currPos.x, cplayers->playersVec.at(i).side.bottom+sprite.getGlobalBounds().height/2.0f);
                } else {
                    sprite.setPosition(currPos.x, currPos.y+sprite.getGlobalBounds().height/2.0f);
                }
                effectSp.setPosition(currPos);
                effectActive = true;
                sManager->playAudio("pong");
                randomAngle(360.0f-ballAngle-20.0f, 360.0f-ballAngle);
            }
        } else if (side.top > top &&
                   side.bottom < bottom) {
            if (side.right > left &&
                side.left < left &&
                speed > 0) {
                sprite.setPosition(currPos.x-sprite.getGlobalBounds().width/2.0f, currPos.y);
                speed = -speed;
                effectSp.setPosition(sf::Vector2f(side.right, currPos.y));
                effectActive = true;
                sManager->playAudio("pong");
                randomAngle(360.0f-ballAngle-20.0f, 360.0f-ballAngle);
            } else if (side.left < right &&
                       side.right > right &&
                       speed < 0) {
                sprite.setPosition(currPos.x+sprite.getGlobalBounds().width/2.0f, currPos.y);
                speed = -speed;
                effectSp.setPosition(sf::Vector2f(side.left, currPos.y));
                effectActive = true;
                sManager->playAudio("pong");
                randomAngle(360.0f-ballAngle-20.0f, 360.0f-ballAngle);
            }
        } else if (side.bottom > top &&
                   side.top < top) {
            if (side.right > left &&
                side.left < left) {
                sprite.setPosition(currPos.x-sprite.getGlobalBounds().width/2.0f, currPos.y);
                speed = -speed;
                effectSp.setPosition(currPos);
                effectActive = true;
                sManager->playAudio("pong");
                randomAngle(360.0f-ballAngle-20.0f, 360.0f-ballAngle);
            } else if (side.left < right &&
                       side.right > right) {
                sprite.setPosition(currPos.x+sprite.getGlobalBounds().width/2.0f, currPos.y);
                speed = -speed;
                effectSp.setPosition(currPos);
                effectActive = true;
                sManager->playAudio("pong");
                randomAngle(360.0f-ballAngle-20.0f, 360.0f-ballAngle);
            }
        } else if (side.top < bottom &&
                   side.bottom > bottom) {
            if (side.right > left &&
                side.left < left) {
                sprite.setPosition(currPos.x-sprite.getGlobalBounds().width/2.0f, currPos.y);
                speed = -speed;
                effectSp.setPosition(currPos);
                effectActive = true;
                sManager->playAudio("pong");
                randomAngle(360.0f-ballAngle-20.0f, 360.0f-ballAngle);
            } else if (side.left < right &&
                       side.right > right) {
                sprite.setPosition(currPos.x+sprite.getGlobalBounds().width/2.0f, currPos.y);
                speed = -speed;
                effectSp.setPosition(currPos);
                effectActive = true;
                sManager->playAudio("pong");
                randomAngle(360.0f-ballAngle-20.0f, 360.0f-ballAngle);
            }
        }
    }
    return;
}

void Pongball::restart (void) {
    ballAngle = 0.0f;
    currPos = sf::Vector2f(320.0f, 240.0f);
    sprite.setPosition(currPos);
    isMoving = false;
    counter.restart();
    return;
}

void Pongball::randomAngle (float MIN, float MAX) {
    std::uniform_real_distribution<float> randAngle(MIN, MAX);
    float angle = randAngle(eng);
    ballAngle = angle;
    sprite.setRotation(ballAngle);
    return;
}

// Generates random vertical position for the ball
void Pongball::randomPos (void) {
    float xpos;
    std::uniform_real_distribution<float> randPos(50.0f, 430.0f);
    if (speed > 0) {
        xpos = 240.0f;
    } else {
        xpos = 400.0f;
    }
    currPos = sf::Vector2f(xpos, randPos(eng));
    sprite.setPosition(currPos);
    return;
}

// Handles update
void Pongball::update (void) {
    hitExplode();
    collision();
    setSides();
    if (isMoving) {
        movement();
    }
    if (isCounting) {
        counterVar = counter.getElapsedTime().asSeconds();
        if (counterVar >= 4.0f) {
            randomPos();
            randomAngle(0, 45.0f);
            isMoving = true;
            isCounting = false;
            counter.restart();
        }
    }
    sprite.setTexture(texture);
    clock.restart();

    return;
}

// Handles render
void Pongball::render (void) {
    if (isMoving) {
        renderWin->draw(sprite);
    }
    renderWin->draw(effectSp);
    return;
}

void Pongball::setSides (void) {
    side = {sprite.getGlobalBounds().top,
            sprite.getGlobalBounds().top+texture.getSize().y,
            sprite.getGlobalBounds().left,
            sprite.getGlobalBounds().left+texture.getSize().x};
    return;
}
