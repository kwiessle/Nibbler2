#ifndef IGRAPHISM_HPP
# define IGRAPHISM_HPP

# define CELL_UNITY 30

# include <list>
# include "IEntity.hpp"

class IGraphism {
  public:
    virtual ~IGraphism(void) {}

    virtual void            drawFrame(std::list <IEntity *> data, int lives, int score) const = 0;
    virtual bool            displayPause(int status)  = 0;
    virtual eHook           getHooks(void) const = 0;
    virtual eHook           getStatus(void) const = 0;
    virtual void            setStatus(eHook status)  = 0;
    virtual eEngine         getEngine(void) const = 0;
    virtual bool            engineHasChanged(void) const = 0;
    virtual void            setHooks(void) = 0;
    virtual unsigned int    getWidth(void) const = 0;
    virtual unsigned int    getHeight(void) const = 0;

};

#endif
