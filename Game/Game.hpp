
#ifndef GAME_HPP
# define GAME_HPP

# include "main.hpp"
# include "Player.hpp"
# include "Timer.hpp"

class Game {
  private:
    Game(void);

    Player                        *_player;
    std::list <IEntity *>          _food;
    std::list <IEntity *>          _walls;
    IGraphism                     *_engine;

    std::list <IEntity *>         mergeEntities(void) const;

  public:
    ~Game(void);

    static Game                   &singleton(void);

    void                          *getBinaryLib(void) const;
    IGraphism                     *getEngine(void) const;
    void                          setEngine(IGraphism  *engine);



    void                          refresh(void);
    void                          start(unsigned int with, unsigned int height);
    void                          pause(void) const;
    void                          save(void) const;
    void                          quit(void) const;
    void                          initFood(void);
};

#endif
