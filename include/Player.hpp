#ifndef PLAYER_HPP
# define PLAYER_HPP

# include "main.hpp"
# include "IEntity.hpp"
# include <math.h>

class Player {
  private:
    Player(Player const &src);

    Player  &operator=(Player const &rhs);

    std::list <IEntity *>                   _snake;
    int                                     _life;
    int                                     _score;
    int                                     _speed;
    bool                                    _dead;
    bool                                    _scoreChange;
    void                                    _grow(void);
    void                                    _updateSnake(eDirection direction);
    void                                    _detectCollision(eDirection direction);
    void                                    _fillNeck(eDirection headDirection);
    void                                    _fillQueue(void);
    void                                    _fillHead(void);
    IEntity *                               _createHead(eDirection direction);
    Player(void);

  public:
    Player(int life, int score); //Use this constructor for default game.
    Player(std::list <IEntity *> snake, int life, int score, int speed);         //Use this constructor for load a saved game.
    ~Player(void);
    void                         initSnake(void);
    void                         move(eDirection direction);
    std::list <IEntity *>        getSnake(void) const;
    int                          getLife(void) const;
    int                          getScore(void) const;
    bool                         getScoreChange(void) const;
    void                         setScoreChange(bool status);
    int                          getSpeed(void) const;
    bool                         checkDeath(void) const;


};

#endif
