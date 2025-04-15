#pragma once

#include "resource.h"

#include <SFML/Audio.hpp>

class AudioFile : public Resource {
public:
    AudioFile(const std::string &path);
    sf::Sound &get_sf_sound() const;
    void play_immediate();
private:
    sf::SoundBuffer _sf_sound_buffer;
};
