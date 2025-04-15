#include "audio_file.h"

AudioFile::AudioFile(const std::string &path) 
    : Resource(path), _sf_sound_buffer()
{
    _sf_sound_buffer = sf::SoundBuffer(path);
}

sf::Sound &AudioFile::get_sf_sound() const {
    static sf::Sound sound(_sf_sound_buffer);
    return sound;
}

void AudioFile::play_immediate() {
    get_sf_sound().play();
}