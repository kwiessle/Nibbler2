#include "CoreAudio.hpp"

CoreAudio::CoreAudio(void) {
    if ( Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) {
        std::cout << Mix_GetError() << std::endl;
        exit(0);
    }
    this->soundCroc = Mix_LoadMUS("/assets/s_food.wav");
    return;
}

CoreAudio::~CoreAudio(void) {
    Mix_FreeMusic(this->soundCroc);
    Mix_CloseAudio();
    return;
}

void    CoreAudio::play(eSound sound) const {
    switch (sound) {
        case Croc :  Mix_PlayMusic( this->soundCroc, 1); break;
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
