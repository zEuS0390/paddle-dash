#ifndef AI_H
#define AI_H

#include <string>
#include "players.hpp"
#include "pongball.hpp"

class AI 
{
public:
        std::string         status;
        AI                  (player&, Pongball&);
        void init           ();
        void sense          ();
        void update         ();
private:
        player&             pPlayer;
        Pongball&           pBall;
};

#endif
