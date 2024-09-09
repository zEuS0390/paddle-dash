#ifndef SOUND_H
#define SOUND_H

#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include <memory>

// sound class
class sound
{
public:
    sound                                                       (const std::string&, float);
    void playSound                                              ();
    void setPitch                                               (float);
private:
    void init                                                   (const std::string&, float);
    sf::SoundBuffer                                             buffer;
    sf::Sound                                                   soundObj;
};

// soundManager class
class soundManager
{
public:
    soundManager                                                ();
    ~soundManager                                               ();
    void audioInit                                              ();
    void playAudio                                              (const std::string&);
    void setPitch                                               (const std::string&, float);
    void terminateAudioThreads                                  ();
private:
    std::unordered_map<std::string, std::unique_ptr<sound>>     audioCont;
};

#endif

