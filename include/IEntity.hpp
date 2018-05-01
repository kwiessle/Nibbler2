#ifndef IENTITY_HPP
# define IENTITY_HPP
# include <iostream>


enum eDirection { NoDir, Up, Down, Left, Right };
enum eType { Free = 0, Snake = 1, Food = 2, Wall = 3, Fire = 4, Bonus = 5 };

enum eTexture {
  uHead = 1, uHeadMiam = 5, luCorner = 9, uQueue = 13, vBody = 17, NoImg = 21,
  dHead = 2, dHeadMiam = 6, ldCorner = 10, dQueue = 14, hBody = 18, Life = 22,
  lHead = 3, lHeadMiam = 7, ruCorner = 11, lQueue = 15, tFood = 19, tFire = 23,
  rHead = 4, rHeadMiam = 8, rdCorner = 12, rQueue = 16, tWall = 20, tBonus = 24,
  None = 25,
};

class IEntity {
  public:
    virtual ~IEntity(void) {}

    virtual unsigned int       getPosX(void) const = 0;
    virtual unsigned int       getPosY(void) const = 0;
    virtual eType              getType(void) const = 0;
    virtual eDirection         getDirection(void) const = 0;
    virtual eTexture           getTexture(void) const = 0;
    virtual void               setPosX(unsigned int x) = 0;
    virtual void               setPosY(unsigned int y) = 0;
    virtual void               setType(eType type) = 0;
    virtual void               setDirection(eDirection direction) = 0;
    virtual void               setTexture(eTexture texture) = 0;

};

#endif
