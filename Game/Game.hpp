
#ifndef GAME_HPP
# define GAME_HPP

# include "main.hpp"
# include "Player.hpp"

class Game {
  private:
    Game(void);

    Player                        *_player;
    std::list <IEntity *>          _food;
    std::list <IEntity *>          _walls;
    IGraphism const               *_engine;
    void                          *_binaryLib;

    std::list <IEntity *>         mergeEntities(void) const;

  public:
    Game(IGraphism const *engine, void *binaryLib);
    ~Game(void);

    static Game                   &singleton(void);

    void                          *getBinaryLib(void) const;
    IGraphism const               *getEngine(void) const;
    void                          setBinaryLib(void *binaryLib);
    void                          setEngine(IGraphism const *engine);



    void                          refresh(void) const;
    void                          play(void) const;
    void                          pause(void) const;
    void                          save(void) const;
    void                          quit(void) const;
    void                          initFood(void);

    Game                          &operator=(Game const &rhs);


};

#endif
