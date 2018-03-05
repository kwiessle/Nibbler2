
#ifndef GAME_HPP
# define GAME_HPP


class Game {
  private:
    Game(void);

    Player                        **_players;
    std::list <Entity *>          _food;
    std::list <Entity *>          _walls;
    IGraphism const               *engine;

    std::list <Entity const *>    mergeEntities(void) const;

  public:
    Game(IGraphism const *engine);
    ~Game(void);

    static Game                   &singleton(void);

    void                          refresh(void) const;
    void                          play(void) const;
    void                          pause(void) const;
    void                          save(void) const;
    void                          quit(void) const;

};

#endif
