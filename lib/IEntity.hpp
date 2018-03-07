#ifndef IENTITY_HPP
# define IENTITY_HPP

enum eHook { NoDir, Up, Down, Left, Right, Exit };

enum eType { Snake, Food, Wall };

enum eTexture {
  uHead, uHeadMiam, luCorner, uQueue, vBody, NoImg,
  dHead, dHeadMiam, ldCorner, dQueue, hBody,
  lHead, lHeadMiam, ruCorner, lQueue, tFood,
  rHead, rHeadMiam, rdCorner, rQueue, tWall
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
