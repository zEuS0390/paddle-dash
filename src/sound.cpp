#include <SFML/Audio.hpp>
#include <string>
#include "sound.h"

sound::sound (std::string name,
              std::string filepath,
              float volume)
:   name(name) {
        init(filepath, volume);
}

void sound::playSound (void) {
    soundObj.play();
    return;
}

void sound::setPitch (float pitch) {
    soundObj.setPitch(pitch);
    return;
}

void sound::init (std::string filepath,
                  float volume) {
    if (!buffer.loadFromFile(filepath)) {
        return;
    }
    soundObj.setBuffer(buffer);
    soundObj.setVolume(volume);
    return;
}

soundManager::soundManager (void) {
    audioInit();
}

soundManager::~soundManager (void) {
    terminateAudioThreads();
}

void soundManager::audioInit (void) {
    audioCont.push_back(new sound("pong", "sfx/pong.wav", 75.0f));
    audioCont.push_back(new sound("table", "sfx/pong-table.wav", 75.0f));
    audioCont.push_back(new sound("outside", "sfx/pong-outside.wav", 75.0f));
    audioCont.push_back(new sound("player1-scores", "sfx/player1-scores.wav", 75.0f));
    audioCont.push_back(new sound("player2-scores", "sfx/player2-scores.wav", 75.0f));
    audioCont.push_back(new sound("blip", "sfx/blip.wav", 75.0f));
    audioCont.push_back(new sound("select", "sfx/select.wav", 75.0f));
    audioCont.push_back(new sound("quit", "sfx/quit.wav", 75.0f));
    audioCont.push_back(new sound("player-move", "sfx/player-move.wav", 75.0f));
    return;
}

void soundManager::playAudio (std::string name) {
    for (unsigned int index = 0; index < audioCont.size(); index++) {
        if (name == audioCont[index]->name) {
            audioCont[index]->playSound();
        }
    }
    return;
}

void soundManager::setPitch (std::string name, float pitch) {
    for (unsigned int index = 0; index < audioCont.size(); index++) {
        if (name == audioCont[index]->name) {
            audioCont[index]->setPitch(pitch);
        }
    }
}

void soundManager::terminateAudioThreads (void) {
    while (!audioCont.empty()) {
        delete audioCont.back();
        audioCont.pop_back();
    }
    return;
}
