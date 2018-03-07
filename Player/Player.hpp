#ifndef PLAYER_HPP
# define PLAYER_HPP

# include "main.hpp"
# include "IEntity.hpp"
# include <math.h>

class Player {
  private:
    std::list <IEntity *>        _snake;
    int                          _life;
    int                          _score;
    int                          _speed;

    void                         _grow(void);
    void                         _death(void);
    void                         _updateSnake(eHook direction);
    void                         _detectCollision(eHook direction);
    void                         _fillBody(eHook headDirection);
    void                         _fillQueue(void);
    void                         _fillHead(void);

  public:
    Player(void);                                                               //Use this constructor for default game.
    Player(std::list <IEntity *> snake, int life, int score, int speed);         //Use this constructor for load a saved game.
    ~Player(void);

    void                         move(eHook direction);

    std::list <IEntity *>        getSnake(void) const;
    int                          getLife(void) const;
    int                          getScore(void) const;
    int                          getSpeed(void) const;
    void                         initSnake(void);


};

#endif
