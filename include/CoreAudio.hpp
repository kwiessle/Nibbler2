#ifndef CoreAudio_HPP
# define CoreAudio_HPP

# include <SDL2/SDL_mixer.h>
# include <iostream>
# include "ICoreAudio.hpp"


class CoreAudio : public ICoreAudio {
    public:
        CoreAudio(void);
        CoreAudio(CoreAudio const &src);
        ~CoreAudio(void);

        void        play(eSound sound) const;

    private:
        Mix_Chunk              *soundCroc;
        Mix_Chunk              *soundTheme;
        Mix_Chunk              *soundDamage;
};

extern "C" {
    CoreAudio            *newCoreAudio(void);
    void                 deleteCoreAudio(CoreAudio *coreCoreAudio);
}

#endif
