#ifndef PONGBALL_H
#define PONGBALL_H

#include <SFML/Graphics.hpp>
#include <random>
#include "players.hpp"
#include "sound.hpp"
#include "rect.hpp"

// pongball class
class Pongball 
{
public:
        bool                    effectActive;
        bool                    isCounting;
        bool                    isMoving;
        float                   constSpeed;
        float                   maxSpeed;
        float                   speed;
        float                   acc;
        float                   ballAngle;
        float                   counterVar;
        Pongball                (sf::RenderWindow*, players*, soundManager*);
        ~Pongball               ();
        void init               ();
        void hitExplode         ();
        void nextPos            ();
        void movement           ();
        void collision          ();
        void paddleCollide      ();
        void restart            ();
        void randomAngle        (float, float);
        void randomPos          ();
        void updateScore        ();
        void update             ();
        void render             ();
        sf::Clock               clock;
        sf::Clock               effectClock;
        sf::Clock               counter;
        sf::Sprite              sprite;
        sf::Texture             texture;
        Side                    side;
        sf::Vector2f            currPos;
        sf::Vector2f            pos;
        sf::Vector2f            effectPos;
        sf::Vertex              vertex1;
        sf::Vertex              vertex2;
        void setSides           ();
private:
        sf::IntRect             effectRect;
        sf::Sprite              effectSp;
        sf::Texture             effectTex;
        soundManager*           sManager;
        std::mt19937            eng;
        sf::RenderWindow*       renderWin;
        players*                cplayers;
};

#endif
