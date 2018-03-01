#ifndef ENTITY_HPP
# define ENTITY_HPP

class Entity {
  private:
    Entity(void);

    unsigned int          _posX;
    unsigned int          _posY;
    eType                 _type;
    eDirection            _direction;
    eTexture              _texture;

  public:
    Entity(unsigned int x, unsigned int y, eType type, eDirection direction, eTexture texture);  //Use this to init a snake piece or a wall
    ~Entity(void);

    void                  randomize(void) // Use this to set an random _X : _Y position to a food piece.
    unsigned int          getPosX(void) const;
    unsigned int          getPosY(void) const;
    eType                 getType(void) const;
    eDirection            getDirection(void) const;
    eTexture              getTexture(void) const;
};

#endif
