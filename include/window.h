#ifndef WINDOW_H
#define WINDOW_H
#include <SFML/Graphics.hpp>
#include <string>
#include "pongball.h"
#include "players.h"
#include "sound.h"
#include "background.h"
#include "AI.h"
#include "menu.h"

// window class
class window {
    public:
        bool                    isAI;
        bool                    isGameActive;
        bool                    isRunning;
    public:
        window                  (unsigned int,
                                unsigned int,
                                std::string);
        ~window                 (void);
    private:
        void init               (void);
        template <class T>
        void textInit           (std::vector<T>*,
                                 float,
                                 sf::Color,
                                 sf::Vector2f);
        void events             (void);
        void menuSelection      (void);
        void updateScores       (void);
        void updates            (void);
        void renderScores       (void);
        void render             (void);
        void gameLoop           (void);
    public:
        sf::RenderWindow        renderWin;
    private:
        menu                    gameMenu;
        sf::Clock               gameClock;
        sf::Font                font;
        Background              background;
        players                 _2players;
        Pongball                pongball;
        soundManager            sManager;
        AI                      AIplayer;
        std::vector<sf::Text>   scoresTxt;
        std::vector<sf::Text>   AITxt;

};

#endif
