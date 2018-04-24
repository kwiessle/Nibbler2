
#ifndef GAME_HPP
# define GAME_HPP

# include "main.hpp"
# include "Player.hpp"
# include "Timer.hpp"
# include <random>
#include <unistd.h>



class Game {
  private:
    Game(void);
    Game(Game const &src);

    Game    &operator=(Game const &rhs);

    Player                        *_player;
    std::list <IEntity *>         _food;
    std::list <IEntity *>         _walls;
    std::list <IEntity *>         _fire;
    std::list <IEntity *>         _freePos;
    std::list <IEntity *>         _bonus;
    int                           _bestScore;
    IGraphism                     *_engine;


  public:
    ~Game(void);
    static Game                   &singleton(void);
    ICoreAudio                    *coreAudio;

    IGraphism                     *getEngine(void) const;
    std::list <IEntity *>         &getFood(void);
    std::list <IEntity *>         &getFreePos(void);
    std::list <IEntity *>         &getWalls(void);
    std::list <IEntity *>         &getFire(void);
    std::list <IEntity *>         &getBonus(void);
    void                          initGame(unsigned int with, unsigned int height, int mode);
    void                          initFood(void);
    void                          initFire(void);
    void                          initBonus(void);
    void                          initMode(int mode);
    void                          initMap(unsigned int width, unsigned int height);
    void                          start(unsigned int with, unsigned int height, int mode);
    void                          switchEngine(eEngine engine, eDirection direction);
    void                          setEngine(IGraphism  *engine);
    void                          setBestScore(int score);

    std::list <IEntity *>         mergeEntities(void) const;

    void                          listErase(std::list <IEntity *> &list, unsigned int x, unsigned int y);
    void                          listAdd(std::list <IEntity *> &list, IEntity * entity);
    bool                          listCheck(std::list <IEntity *> &list, unsigned int x, unsigned int y);

};

#endif
