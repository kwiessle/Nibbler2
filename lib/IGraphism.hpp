#ifndef IGRAPHISM_HPP
# define IGRAPHISM_HPP

# define CELL_UNITY 30

# include <list>
# include "IEntity.hpp"

class IGraphism {
  public:
    virtual ~IGraphism(void) {}

    virtual void            drawFrame(std::list <IEntity *> data, int lives, int score) const = 0;
    virtual eHook           getHooks(void) const = 0;
    virtual eHook           getHooksEngine(void) const = 0;
    virtual void            setHooks(void) = 0;
    virtual unsigned int    getWidth(void) const = 0;
    virtual unsigned int    getHeight(void) const = 0;

};

#endif
