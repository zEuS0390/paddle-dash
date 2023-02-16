#ifndef AI_H
#define AI_H
#include <string>
#include "players.h"
#include "pongball.h"

class AI {
    public:
        std::string         status;
    public:
        AI                  (player*,
                            Pongball*);
    public:
        void init           (void);
        void sense          (void);
        void update         (void);
    private:
        player*             pPlayer;
        Pongball*           pBall;
};

#endif
