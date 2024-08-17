#include <SFML/Audio.hpp>
#include <string>
#include "sound.hpp"

sound::sound (const std::string& name, const std::string& filepath, float volume)
:       name(name) 
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
        if (!buffer.loadFromFile(filepath)) return;
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
        audioCont.emplace("pong", std::make_unique<sound>("pong", "sfx/pong.wav", 75.0f));
        audioCont.emplace("table", std::make_unique<sound>("table", "sfx/pong-table.wav", 75.0f));
        audioCont.emplace("outside", std::make_unique<sound>("outside", "sfx/pong-outside.wav", 75.0f));
        audioCont.emplace("player1-scores", std::make_unique<sound>("player1-scores", "sfx/player1-scores.wav", 75.0f));
        audioCont.emplace("player2-scores", std::make_unique<sound>("player2-scores", "sfx/player2-scores.wav", 75.0f));
        audioCont.emplace("blip", std::make_unique<sound>("blip", "sfx/blip.wav", 75.0f));
        audioCont.emplace("select", std::make_unique<sound>("select", "sfx/select.wav", 75.0f));
        audioCont.emplace("quit", std::make_unique<sound>("quit", "sfx/quit.wav", 75.0f));
        audioCont.emplace("player-move", std::make_unique<sound>("player-move", "sfx/player-move.wav", 75.0f));
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
