#ifndef PLAYERS_H
#define PLAYERS_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "rect.h"
#include "sound.h"

// player class
class player {
    public:
        std::string             id;
        std::string             filepath;
        std::string             shadowfilepath;
        int                     score;
        bool                    isMoving;
        bool                    isPlaying;
        float                   speed;
        float                   velY;
        float                   accY;
        float                   fric;
    public:
        player                  (std::string,
                                 std::string,
                                 std::string,
                                 sf::Vector2f,
                                 soundManager*);
        void init               (void);
        void movement           (void);
        void collision          (void);
        void restartPos         (void);
        void update             (void);
    private:
        void setSides           (void);
    public:
        sf::Vector2f            initPos;
        sf::Vector2f            currPos;
        sf::Sprite              sprite;
        sf::Sprite              shadow;
        sf::Texture             texture;
        sf::Texture		shadowTex;
        Dir                     dir;
        Side			side;
    private:
        sf::Clock               clock;
        soundManager*           sManager;
};

// players class
class players {
    public:
        std::vector<player>     playersVec;
    public:
        players                 (sf::RenderWindow*,
                                 soundManager*);
        ~players                (void);
        void init               (void);
        void setScore           (std::string,
                                 int);
        void resetScore         (void);
        void move               (std::string,
                                 std::string);
        void stop               (std::string);
        void pause              (void);
        void resume             (void);
        void restart            (void);
        void events             (void);
        void updates            (void);
        void renders            (void);
    private:
        sf::RenderWindow*       renderWin;
        soundManager*           sManager;
};

#endif
