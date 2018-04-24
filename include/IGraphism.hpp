#ifndef IGRAPHISM_HPP
# define IGRAPHISM_HPP

# define CELL_UNITY 30

# include <list>
# include <map>
# include <iostream>
# include "IEntity.hpp"

class IGraphism {
  public:
    virtual ~IGraphism(void) {}

    virtual void            drawFrame(std::list <IEntity *> data, int lives, int score) const = 0;
    virtual bool            displayPause(int score, int bestScore) = 0;
    virtual void            handleEvent(int milliseconds) = 0;
    virtual eDirection      getDirection(void) const = 0;
    virtual void            updateDirection(eDirection status) = 0;
    virtual bool            directionHasChanged(void) const = 0;
    virtual void            reverseDirectionChecker(void) = 0;

    virtual eStatus         getStatus(void) const = 0;
    virtual void            updateStatus(eStatus status) = 0;

    virtual eEngine         getEngine(void) const = 0;
    virtual bool            engineHasChanged(void) const = 0;

    virtual unsigned int    getWidth(void) const = 0;
    virtual unsigned int    getHeight(void) const = 0;

};

#endif
