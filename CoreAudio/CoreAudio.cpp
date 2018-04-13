#include "CoreAudio.hpp"

CoreAudio::CoreAudio(void) {
    if ( Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) {
        std::cout << Mix_GetError() << std::endl;
        exit(0);
    }
    Mix_AllocateChannels(3);
    Mix_Volume(1, MIX_MAX_VOLUME/2);
    this->soundCroc = Mix_LoadWAV("/assets/s_food.wav");
    this->soundTheme = Mix_LoadWAV("/assets/s_theme.wav");
    this->soundDamage = Mix_LoadWAV("/assets/s_damage.wav");
    Mix_VolumeChunk(this->soundCroc, MIX_MAX_VOLUME/2);
    Mix_VolumeChunk(this->soundDamage, MIX_MAX_VOLUME/2);

    return;
}

CoreAudio::~CoreAudio(void) {
    Mix_FreeChunk(this->soundCroc);
    Mix_FreeChunk(this->soundTheme);
    Mix_FreeChunk(this->soundDamage);
    Mix_CloseAudio();
    return;
}

void    CoreAudio::play(eSound sound) const {
    switch (sound) {
        case Theme : Mix_PlayChannel(1, this->soundTheme, 4); break;
        case Croc : Mix_PlayChannel(0, this->soundCroc, 0); break;
        case Damage : Mix_PlayChannel(2, this->soundDamage, 0); break;
        default: break;
    }
    return;
}


CoreAudio   *newCoreAudio(void) {
    CoreAudio *coreCoreAudio = new CoreAudio();
    return coreCoreAudio;
}
void    deleteCoreAudio(CoreAudio *coreCoreAudio) {
    delete coreCoreAudio;
    return;
}
