#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>
#include "version.hpp"

namespace constants
{
	const std::string       WINDOW_TITLE =                  "Pong Game";
        const std::string       GAME_VERSION =                  constants::PROJECT_VERSION;
	constexpr unsigned int  WINDOW_SIZEX =                  640;
	constexpr unsigned int  WINDOW_SIZEY =                  480;
        const std::string       SOUND_PONG =                    "sfx/pong.wav";
        const std::string       SOUND_TABLE =                   "sfx/pong-table.wav";
        const std::string       SOUND_OUTSIDE =                 "sfx/pong-outside.wav";
        const std::string       SOUND_PLAYER1_SCORES =          "sfx/player1-scores.wav";
        const std::string       SOUND_PLAYER2_SCORES =          "sfx/player2-scores.wav";
        const std::string       SOUND_BLIP =                    "sfx/blip.wav";
        const std::string       SOUND_SELECT =                  "sfx/select.wav";
        const std::string       SOUND_QUIT =                    "sfx/quit.wav";
        const std::string       SOUND_PLAYER_MOVE =             "sfx/player-move.wav";
        const std::string       IMAGE_GAMEPLAY_BACKGROUND =     "gfx/background.png";
        const std::string       IMAGE_GAME_LOGO =               "gfx/game-logo.png";
        const std::string       IMAGE_MOUSE_POINTER =           "gfx/mouse-pointer.png";
        const std::string       IMAGE_MENU_BACKGROUND =         "gfx/menu-background.png";
        const std::string       IMAGE_PONG_BALL =               "gfx/pongball.png";
        const std::string       IMAGE_EXPLODE =                 "gfx/explode.png";
        const std::string       FONT_FAMILY =                   "gfx/font/november.ttf";
}


#endif
