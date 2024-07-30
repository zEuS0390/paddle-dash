#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>
#include <string>
#include "pongball.hpp"
#include "players.hpp"
#include "sound.hpp"
#include "background.hpp"
#include "AI.hpp"
#include "menu.hpp"

// window class
class window 
{
public:
        bool                    isAI;
        bool                    isGameActive;
        bool                    isRunning;
        window                  (unsigned int, unsigned int, std::string);
        ~window                 ();
        sf::RenderWindow        renderWin;
private:
        void init               ();
        template <class T>
        void textInit           (std::vector<T>*, float, sf::Color, sf::Vector2f);
        void events             ();
        void menuSelection      ();
        void updateScores       ();
        void updates            ();
        void renderScores       ();
        void render             ();
        void gameLoop           ();
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
