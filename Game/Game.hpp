
#ifndef GAME_HPP
# define GAME_HPP

# include "main.hpp"
# include "Player.hpp"
# include "Timer.hpp"
# include <random>


class Game {
  private:
    Game(void);

    Player                        *_player;
    std::list <IEntity *>         _food;
    std::list <IEntity *>         _walls;
    std::list <IEntity *>         _fire;
    std::list <IEntity *>         _freePos;
    IGraphism                     *_engine;
    bool                           _gamePause;
    bool                           _gameQuit;

  public:
    ~Game(void);

    static Game                   &singleton(void);

    std::list <IEntity *>         mergeEntities(void) const;
    void                          initMap(unsigned int width, unsigned int height);
    IGraphism                     *getEngine(void) const;
    void                          setEngine(IGraphism  *engine);
    std::list <IEntity *>         &getFood(void);
    std::list <IEntity *>         &getFreePos(void);
    std::list <IEntity *>         &getWalls(void);
    std::list <IEntity *>         &getFire(void);
    void                          refresh(void);
    void                          start(unsigned int with, unsigned int height, int mode);
    void                          initGame(unsigned int with, unsigned int height, int mode);
    void                          pause(int status);
    void                          setPause(void);
    void                          save(void) const;
    void                          quit(void) const;
    void                          initFood(void);
    void                          initFire(void);
    void                          initMode(int mode);
    void                          switchEngine(eEngine engine, eHook hook);
    void                          listErase(std::list <IEntity *> &list, unsigned int x, unsigned int y);
    void                          listAdd(std::list <IEntity *> &list, IEntity * entity);
    bool                          listCheck(std::list <IEntity *> &list, unsigned int x, unsigned int y);

};

#endif
