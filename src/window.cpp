#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <string>
#include <memory>
#include "constants.hpp"
#include "window.hpp"
#include "players.hpp"
#include "funcs.hpp"

// Main constructor of the window class
window::window (unsigned int x, unsigned int y, const std::string& titleName)
:   isAI(false),
    isGameActive(false),
    isRunning(true),
    renderWin(sf::VideoMode(x, y), titleName, sf::Style::Titlebar),
    gameMenu(renderWin, sManager),
    background(renderWin, sf::Vector2f(x/2.0f, y/2.0f)),
    _2players(renderWin, sManager),
    pongball(renderWin, _2players, sManager),
    AIplayer(_2players.playersVec.at(1), pongball)
{
        init();
}

// Main destructor of the window class
window::~window ()
{
    scoresTxt.clear();
}

// Initialization of objects in the game
void window::init ()
{
    renderWin.setFramerateLimit(120);
    renderWin.setMouseCursorVisible(false);
    if (!font.loadFromFile(funcs::joinPath(funcs::getExecutableDir(), constants::FONT_FAMILY)))
        throw std::runtime_error(constants::FAILED_TO_LOAD_FILE_ERR + ": '" + constants::FONT_FAMILY + "'") ;
    textInit(scoresTxt, 60.0f, sf::Color::White, sf::Vector2f(160.0f, 50.0f));
    textInit(scoresTxt, 60.0f, sf::Color::White, sf::Vector2f(480.0f, 50.0f));
    textInit(AITxt, 20.0f, sf::Color::Yellow, sf::Vector2f(350.0f, 440.0f));
    gameLoop();
}

void window::textInit (std::vector<std::unique_ptr<sf::Text>>& textVec, float characterSize, sf::Color color, sf::Vector2f pos)
{
    std::unique_ptr<sf::Text> ptext = std::make_unique<sf::Text>();
    ptext->setFont(font);
    ptext->setCharacterSize(characterSize);
    ptext->setFillColor(color);
    ptext->setPosition(pos);
    textVec.push_back(std::move(ptext));
}

// Handles events
void window::events ()
{
    sf::Event event;
    while (renderWin.pollEvent(event))
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (isGameActive)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
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
}

void window::menuSelection ()
{
    const std::string& selected = gameMenu.checkSelected();
    if (selected == "Player vs. CPU")
    {
        isAI = true;
        gameMenu.isMenu = false;
        isGameActive = true;
        pongball.isMoving = false;
        pongball.isCounting = true;
        pongball.restart();
    }
    else if (selected == "Player vs. Player")
    {
        isAI = false;
        gameMenu.isMenu = false;
        isGameActive = true;
        pongball.isMoving = false;
        pongball.isCounting = true;
        pongball.restart();
    }
    else if (selected == "Exit")
    {
        isRunning = false;
    }
}

void window::updateScores ()
{
    for (unsigned int i = 0; i < _2players.playersVec.size(); i++)
    {
        sf::Text* txt = scoresTxt.at(i).get();
        txt->setString(funcs::intToStr(_2players.playersVec.at(i).score));
        txt->setOrigin(txt->getGlobalBounds().width/2.0f, txt->getGlobalBounds().height/2.0f);
    }
}

// Handles updates
void window::updates ()
{
    menuSelection();
    if (isGameActive)
    {
        updateScores();
        pongball.update();
        _2players.updates();
        if (isAI)
        {
            AITxt.back()->setString(AIplayer.status);
            AIplayer.update();
        }
        background.update();
    }
    gameMenu.update();
}

void window::renderScores ()
{
    for (unsigned int i = 0; i < _2players.playersVec.size(); i++)
    {
        sf::Text* txt = scoresTxt.at(i).get();
        renderWin.draw(*txt);
    }
}

// Handles render
void window::render ()
{
    renderWin.clear();
    gameMenu.render();
    if (isGameActive)
    {
        sf::Text* txt = AITxt.back().get();
        background.render();
        renderWin.draw(*txt);
        renderScores();
        _2players.renders();
        pongball.render();
    }
    renderWin.display();
}

// Handles game loop
void window::gameLoop ()
{
    while (isRunning)
    {
        events();
        updates();
        render();
    }
}

