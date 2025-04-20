#include <SFML/Audio.hpp>
#include <stdexcept>
#include <string>
#include "sound.hpp"
#include "constants.hpp"
#include "funcs.hpp"

sound::sound (const std::string& filepath, float volume)
{
    init(filepath, volume);
}

void sound::playSound ()
{
    soundObj.play();
}

void sound::setPitch (float pitch)
{
    soundObj.setPitch(pitch);
}

void sound::init (const std::string& filepath, float volume)
{
    if (!buffer.loadFromFile(filepath))
        throw std::runtime_error(constants::FAILED_TO_LOAD_FILE_ERR + ": '" + filepath + "'") ;
    soundObj.setBuffer(buffer);
    soundObj.setVolume(volume);
}

soundManager::soundManager ()
{
    audioInit();
}

soundManager::~soundManager ()
{
    terminateAudioThreads();
}

void soundManager::audioInit ()
{
    audioCont.emplace("pong", std::make_unique<sound>(funcs::joinPath(funcs::getExecutableDir(), constants::SOUND_PONG), 75.0f));
    audioCont.emplace("table", std::make_unique<sound>(funcs::joinPath(funcs::getExecutableDir(), constants::SOUND_TABLE), 75.0f));
    audioCont.emplace("outside", std::make_unique<sound>(funcs::joinPath(funcs::getExecutableDir(), constants::SOUND_OUTSIDE), 75.0f));
    audioCont.emplace("player1-scores", std::make_unique<sound>(funcs::joinPath(funcs::getExecutableDir(), constants::SOUND_PLAYER1_SCORES), 75.0f));
    audioCont.emplace("player2-scores", std::make_unique<sound>(funcs::joinPath(funcs::getExecutableDir(), constants::SOUND_PLAYER2_SCORES), 75.0f));
    audioCont.emplace("blip", std::make_unique<sound>(funcs::joinPath(funcs::getExecutableDir(), constants::SOUND_BLIP), 75.0f));
    audioCont.emplace("select", std::make_unique<sound>(funcs::joinPath(funcs::getExecutableDir(), constants::SOUND_SELECT), 75.0f));
    audioCont.emplace("quit", std::make_unique<sound>(funcs::joinPath(funcs::getExecutableDir(), constants::SOUND_QUIT), 75.0f));
    audioCont.emplace("player-move", std::make_unique<sound>(funcs::joinPath(funcs::getExecutableDir(), constants::SOUND_PLAYER_MOVE), 75.0f));
}

void soundManager::playAudio (const std::string& name)
{
    if (audioCont.find(name) != audioCont.end())
        audioCont.at(name)->playSound();
}

void soundManager::setPitch (const std::string& name, float pitch)
{
    if (audioCont.find(name) != audioCont.end())
        audioCont.at(name)->setPitch(pitch);
}

void soundManager::terminateAudioThreads ()
{
    audioCont.clear();
}

