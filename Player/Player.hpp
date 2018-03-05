#ifndef PLAYER_HPP
# define PLAYER_HPP


class Player {
  private:
    std::list <Entity *>         _snake;
    int                          _life;
    int                          _score;
    int                          _speed;

    void                         _grow(void);
    void                         _death(void);
    void                         _updateSnake(eDirection);
    void                         _detectCollision(eDiretion);

  public:
    Player(void);                                                               //Use this constructor for default game.
    Player(std::list <Entity *> snake, int life, int score, int speed);         //Use this constructor for load a saved game.
    ~Player(void)

    void                         move(eDirection);

    std::list <Entity *>         getSnake(void) const;
    int                          getLife(void) const;
    int                          getScore(void) const;
    int                          getSpeed(void) const;


};

#endif
