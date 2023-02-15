#include <SFML/Graphics.hpp>
#include <string>
#include "window.h"
#include "players.h"
#include "funcs.h"

// Main constructor of the window class
window::window (unsigned int x,
                unsigned int y,
                std::string titleName)
:   isAI(false),
    isGameActive(false),
    isRunning(true),
    renderWin(sf::VideoMode(x, y),
              titleName,
              sf::Style::Titlebar),
    gameMenu(&renderWin,
             &sManager),
    background(&renderWin,
               sf::Vector2f(x/2.0f, y/2.0f)),
    _2players(&renderWin, &sManager),
    pongball(&renderWin,
             &_2players,
             &sManager),
    AIplayer(&_2players.playersVec.at(1),
             &pongball) {
    init();
}

// Main destructor of the window class
window::~window (void) {
    scoresTxt.clear();
}

// Initialization of objects in the game
void window::init (void) {
    renderWin.setFramerateLimit(120);
    renderWin.setMouseCursorVisible(false);
    if (!font.loadFromFile("gfx/font/november.ttf")) {
        return;
    }
    textInit(&scoresTxt, 60.0f, sf::Color::White, sf::Vector2f(160.0f, 50.0f));
    textInit(&scoresTxt, 60.0f, sf::Color::White, sf::Vector2f(480.0f, 50.0f));
    textInit(&AITxt, 20.0f, sf::Color::Yellow, sf::Vector2f(350.0f, 440.0f));
    gameLoop();
    return;
}

template <class T>
void window::textInit (std::vector<T>* textVec,
                       float characterSize,
                       sf::Color color,
                       sf::Vector2f pos) {
    sf::Text* ptext = new sf::Text;
    ptext->setFont(font);
    ptext->setCharacterSize(characterSize);
    ptext->setFillColor(color);
    ptext->setPosition(pos);
    textVec->push_back(*ptext);
    delete ptext;
    return;
}

// Handles events
void window::events (void) {
    sf::Event event;
    while (renderWin.pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed) {
            if (isGameActive) {
                if (event.key.code == sf::Keyboard::Escape) {
                    sManager.playAudio("quit");
                    gameMenu.isMenu = true;
                    isGameActive = false;
                    pongball.restart();
                    _2players.restart();
                }
            }
        }
        _2players.events();
    }
    return;
}

void window::menuSelection (void) {
    std::string selected = gameMenu.checkSelected();
    if (selected == "Player vs. CPU") {
        isAI = true;
        gameMenu.isMenu = false;
        isGameActive = true;
        pongball.isMoving = false;
        pongball.isCounting = true;
        pongball.restart();
    } else if (selected == "Player vs. Player") {
        isAI = false;
        gameMenu.isMenu = false;
        isGameActive = true;
        pongball.isMoving = false;
        pongball.isCounting = true;
        pongball.restart();
    } else if (selected == "Exit") {
        isRunning = false;
    }
    return;
}

void window::updateScores (void) {
    for (unsigned int i = 0; i < _2players.playersVec.size(); i++) {
        scoresTxt.at(i).setString(funcs::intToStr(_2players.playersVec.at(i).score));
        scoresTxt.at(i).setOrigin(scoresTxt.at(i).getGlobalBounds().width/2.0f,
                                   scoresTxt.at(i).getGlobalBounds().height/2.0f);
    }
    return;
}

// Handles updates
void window::updates (void) {
    menuSelection();
    if (isGameActive){
        updateScores();
        pongball.update();
        _2players.updates();
        if (isAI) {
            AITxt.back().setString(AIplayer.status);
            AIplayer.update();
        }
        background.update();
    }
    gameMenu.update();
    return;
}

void window::renderScores (void) {
    for (unsigned int i = 0; i < _2players.playersVec.size(); i++) {
        renderWin.draw(scoresTxt.at(i));
    }
    return;
}

// Handles render
void window::render (void) {
    renderWin.clear();
    gameMenu.render();
    if (isGameActive) {
        background.render();
        renderWin.draw(AITxt.back());
        renderScores();
        _2players.renders();
        pongball.render();
    }
    renderWin.display();
    return;
}

// Handles game loop
void window::gameLoop (void) {
    while (isRunning) {
        events();
        updates();
        render();
    }
    return;
}
