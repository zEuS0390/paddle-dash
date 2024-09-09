#include "constants.hpp"
#include "window.hpp"

/*
 --------------------------------------------------------
 * CREATED BY: zEuS0390
 * DATE CREATED: MAY 05, 2020; TUESDAY
 * DESCRIPTION: This is the main code for the pong game.
 --------------------------------------------------------
*/

using constants::WINDOW_TITLE;
using constants::WINDOW_SIZEX;
using constants::WINDOW_SIZEY;
using constants::GAME_VERSION;

// Main entry point of the program
int main()
{
    window win(WINDOW_SIZEX, WINDOW_SIZEY, WINDOW_TITLE + " " + GAME_VERSION);
    return 0;
}

