#ifndef IENTITY_HPP
# define IENTITY_HPP

enum eHook { NoDir, Up, Down, Left, Right, Exit };

enum eType { Snake, Food, Wall };

enum eTexture {
  uHead = 1, uHeadMiam = 5, luCorner = 9, uQueue = 13, vBody = 17, NoImg = 21,
  dHead = 2, dHeadMiam = 6, ldCorner = 10, dQueue = 14, hBody = 18, Life = 22,
  lHead = 3, lHeadMiam = 7, ruCorner = 11, lQueue = 15, tFood = 19,
  rHead = 4, rHeadMiam = 8, rdCorner = 12, rQueue = 16, tWall = 20, END
};

class IEntity {
  public:
    virtual ~IEntity(void) {}

    virtual void                  randomizePosition(void) = 0;
    virtual unsigned int          getPosX(void) const = 0;
    virtual unsigned int          getPosY(void) const = 0;
    virtual eType                 getType(void) const = 0;
    virtual eHook            getDirection(void) const = 0;
    virtual eTexture              getTexture(void) const = 0;
    virtual void                  setPosX(unsigned int x) = 0;
    virtual void                  setPosY(unsigned int y) = 0;
    virtual void                  setType(eType type) = 0;
    virtual void                  setDirection(eHook direction) = 0;
    virtual void                  setTexture(eTexture texture) = 0;

};

#endif
