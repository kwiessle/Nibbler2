#ifndef CoreAudio_HPP
# define CoreAudio_HPP

# include <SDL2/SDL_mixer.h>
# include <iostream>
# include "ICoreAudio.hpp"


class CoreAudio : public ICoreAudio {
    public:
        CoreAudio(void);
        ~CoreAudio(void);

        void        play(eSound sound) const;

    private:
        CoreAudio(CoreAudio const &src);

        CoreAudio              &operator=(CoreAudio const &rhs);

        Mix_Chunk              *soundCroc;
        Mix_Chunk              *soundTheme;
        Mix_Chunk              *soundDamage;
        Mix_Chunk              *soundFailure;
};

extern "C" {
    CoreAudio            *newCoreAudio(void);
    void                 deleteCoreAudio(CoreAudio *coreCoreAudio);
}

#endif
