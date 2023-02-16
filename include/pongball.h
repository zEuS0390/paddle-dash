#ifndef PONGBALL_H
#define PONGBALL_H
#include <SFML/Graphics.hpp>
#include <random>
#include "players.h"
#include "rect.h"
#include "sound.h"

// pongball class
class Pongball {
    public:
        bool                effectActive;
        bool                isCounting;
        bool                isMoving;
        float               constSpeed;
        float               maxSpeed;
        float               speed;
        float               acc;
        float               ballAngle;
        float               counterVar;
    public:
        Pongball            (sf::RenderWindow*,
                             players*,
                             soundManager*);
        ~Pongball           (void);
    public:
        void init           (void);
        void hitExplode     (void);
        void nextPos        (void);
        void movement       (void);
        void collision      (void);
        void paddleCollide  (void);
        void restart        (void);
        void randomAngle    (float,
                             float);
        void randomPos      (void);
        void updateScore    (void);
        void update         (void);
        void render         (void);
    private:
        void setSides       (void);
    public:
        sf::Clock           clock;
        sf::Clock           effectClock;
        sf::Clock           counter;
        sf::Sprite          sprite;
        sf::Texture         texture;
        Side                side;
        sf::Vector2f        currPos;
        sf::Vector2f        pos;
        sf::Vector2f        effectPos;
        sf::Vertex          vertex1;
        sf::Vertex          vertex2;
    private:
        sf::IntRect         effectRect;
        sf::Sprite          effectSp;
        sf::Texture         effectTex;
        soundManager*       sManager;
        std::mt19937        eng;
        sf::RenderWindow*   renderWin;
        players*            cplayers;
};

#endif
